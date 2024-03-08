#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "initlistdialog.h"

#include "../common/fileTypes.h"
#include "qmessagebox.h"
#include <iostream>

#include "../ListParts/qfleet_list.h"

#include <QFileDialog>
#include <QJsonParseError>
#include <QClipboard>

#include "../ListPrinter/qfp_strategycard.h"

#include "../ListPrinter/listprinter.h"

#include "confirmdialog.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    if (!listWidget.isNull())
        delete listWidget;

    if (!shipSelectDialog.isNull())
        delete shipSelectDialog;

    delete ui;
}



void MainWindow::on_actionNew_triggered()
{

    // if a list is already loaded, delete it
    if (listWidget)
    {
        delete listWidget;
    }

    listInit data;
    initListDialog * newListData = new initListDialog(this,&data);

    newListData->setAttribute(Qt::WA_DeleteOnClose);

    int r = newListData->exec();

    if (r==QDialog::Accepted)
    {
        faction = data.listFaction;

        // load ship Data for the faction of the new list
        if (loadMapFromJsonFile(this, allShipData))
        {
            listWidget = new QFLW_List(this);

            listWidget->setFaction(data.listFaction);
            listWidget->setPointsLimit(data.listPoints);

            pointsLimit = data.listPoints;

            ui->fleetBox->addWidget(listWidget);
        }
        else
        {
            QMessageBox msg(this);
            msg.setText("Couldn't ship data");
            msg.setWindowTitle("Error");
            msg.exec();
        }


    }

}


// loads ships from a file into the shipdata map and filters out ships from other factions
bool MainWindow::loadMapFromJsonFile(QWidget * parentWindow, QMap<QString, QFleet_Ship_Shipyard>& data)
{
    allShipData.clear();

    QString filename = QFileDialog::getOpenFileName(parentWindow, "Select Ship Data", QDir::currentPath());

    QFile file(filename);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray bytes = file.readAll();

        file.close();

        QJsonParseError err;

        QJsonDocument jsonData = QJsonDocument::fromJson(bytes, &err);

        QJsonObject wrapperObj = jsonData.object();

        try
        {
            if (wrapperObj.contains(fileType_shipData()))
            {
                QJsonArray objects = wrapperObj[fileType_shipData()].toArray();

                for (auto object : objects)
                {
                    QFleet_Ship_Shipyard newShip(object.toObject());

                    if (newShip.factions.contains(*faction))
                        data.insert(newShip.getName(), newShip);
                }
            }
            else
            {
                throw std::invalid_argument("Invalid File Type");
            }
        }
        catch (std::invalid_argument)
        {
            QMessageBox msg(this);
            msg.setText("File read Error! file was wrong type or malformed");
            msg.setWindowTitle("Load Error");
            msg.exec();
            return false;
        }


        return true;
    }

    return false;
}

bool MainWindow::loadListFromFile()
{
    QString filename = QFileDialog::getOpenFileName(this, "Select QFleet List", QDir::currentPath());

    QFile file(filename);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        // if a list is already loaded, delete it
        if (listWidget)
        {
            delete listWidget;
        }

        QByteArray bytes = file.readAll();

        file.close();

        QJsonParseError err;

        QJsonDocument jsonData = QJsonDocument::fromJson(bytes, &err);

        QJsonObject wrapperObj = jsonData.object();


        try
        {
            if (wrapperObj.contains(fileType_listData()))
            {
                QFleet_List list(wrapperObj[fileType_listData()].toObject());


                drawGUIFromListPart(list);
            }
            else
            {
                throw std::invalid_argument("Invalid File Type");
            }
        }
        catch (std::invalid_argument)
        {
            QMessageBox msg(this);
            msg.setText("File read Error! file was wrong type or malformed");
            msg.setWindowTitle("Load Error");
            msg.exec();
        }


        return true;
    }
    else
        return false;
}

void MainWindow::on_actionLoad_triggered()
{
    if (loadListFromFile())
    {
        // (-:
    }
    else
    {
        QMessageBox msg(this);
        msg.setText("Couldn't open load target for reading");
        msg.exec();
    }
}

void MainWindow::drawGUIFromListPart(const QFleet_List& list)
{
    this->faction = list.getFaction();

    // Load ships for the faction matching the loaded list
    if (loadMapFromJsonFile(this, allShipData))
    {
        this->pointsLimit = list.getPointsLimit();

        this->listWidget = new QFLW_List(this, list);

        ui->fleetBox->addWidget(listWidget);
    }
    else
    {
        QMessageBox msg(this);
        msg.setText("Couldn't ship data");
        msg.setWindowTitle("Error");
        msg.exec();
    }

}


void MainWindow::on_shipMenuButton_clicked()
{
    // only open if we have actually loaded ships AND there is no open window already
    if (allShipData.size() > 0 && shipSelectDialog.isNull())
    {
        shipSelectDialog = new shipSelect(this, &allShipData);
        shipSelectDialog->setAttribute(Qt::WA_DeleteOnClose);

        shipSelectDialog->show();
    }
}

void MainWindow::slotShipPull(QFLW_Battlegroup * cardPtr)
{


    if (!shipSelectDialog.isNull() && shipSelectDialog->getSelectedShip())
    {
       QFleet_Ship_Fleet selectedShip = *shipSelectDialog->getSelectedShip();
        cardPtr->recieveSelectedShip(selectedShip);
    }
    else
    {
        QMessageBox msg(this);
        msg.setText("Select a ship to add in the Ship Menu");
        msg.exec();
    }
}


bool MainWindow::saveListToFile()
{
    QFleet_List newList = listWidget->createListPart();

    // save dialog goes here

    QString filename = QFileDialog::getSaveFileName(this, "save list", QDir::currentPath());

    QFile file(filename);

    QJsonObject json = newList.toJson();

    QJsonObject wrapperObj;

    wrapperObj.insert(fileType_listData(), json);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        QJsonDocument jsonDoc(wrapperObj);

        QByteArray bytes = jsonDoc.toJson(QJsonDocument::Indented);

        QTextStream istream(&file);

        istream << bytes;

        file.close();

        return true;
    }
    else return false;
}

void MainWindow::on_actionSave_triggered()
{

    if (!listWidget.isNull())
    {
        if (!checkListValidity())
            return;


        if (saveListToFile())
        {

        }
        else
        {
            QMessageBox msg(this);
            msg.setText("Couldn't open save target for writing");
            msg.exec();
        }
    }
    else
    {
        QMessageBox msg(this);
        msg.setText("No List Loaded to save");
        msg.exec();
    }

}

bool MainWindow::drawStrategycards()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Save strategy cards", QDir::currentPath());

    dir.append(QDir::separator());

    auto cards = listWidget->createListPart().getCards();

    auto index = 0;

    QHash<QString, bool> stringGuard;

    bool rVal = true;

    for (auto battlegroup : cards)
    {
        QString cardName = dir + battlegroup.name;

        if (stringGuard.contains(battlegroup.name))
        {
            cardName = dir + "card-" + QString::number(index);
        }

        QFP_StrategyCard card(this, battlegroup);

        card.show();

        auto cardImage = card.getImage();

        QFile file(cardName);

        bool r1 = file.open(QIODevice::WriteOnly);

        bool r2 = cardImage.save(&file, "PNG");

        file.close();

        index++;

        if ((r1 && r2) == false)
            rVal = false;
    }

    return rVal;

}


void MainWindow::on_actionStrategy_Cards_triggered()
{
    if (!listWidget.isNull())
    {
        if (!checkListValidity())
            return;

        if (drawStrategycards())
        {
            QMessageBox msg(this);
            msg.setText("Strategy Card images written to directory");
            msg.setWindowTitle("Success");
            msg.exec();
        }
        else
        {
            QMessageBox msg(this);
            msg.setText("One or more cards files could not be opened for writing");
            msg.setWindowTitle("Error");
            msg.exec();
        }
    }
    else
    {
        QMessageBox msg(this);
        msg.setText("No List Loaded to print");
        msg.setWindowTitle("Error");
        msg.exec();
    }
}


void MainWindow::on_actionSimple_List_triggered()
{    

    if (!listWidget.isNull())
    {
        if (!checkListValidity())
            return;

        auto listPart = listWidget->createListPart();
        QString listStr = listPart.getListString();

        QClipboard * clipboard = QGuiApplication::clipboard();

        clipboard->setText(listStr);

        QMessageBox msg(this);
        msg.setText("List copied to clipboard");
        msg.setWindowTitle("Success");
        msg.exec();

    }
    else
    {
        QMessageBox msg(this);
        msg.setText("No List Loaded to print");
        msg.setWindowTitle("Error");
        msg.exec();
    }
}

bool MainWindow::writeHTML()
{
    QString filename = QFileDialog::getSaveFileName(this, "save list", QDir::currentPath());

    QFile file(filename);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        auto listObj = listWidget->createListPart();

        QString stub;

        std::string htmlString = listPrinter::getHTML(listObj);

        QByteArray bytes = htmlString.c_str();

        QTextStream istream(&file);

        istream << bytes;

        file.close();

        return true;
    }
    else return false;
}


void MainWindow::on_actionFleet_List_triggered()
{
    if (!listWidget.isNull())
    {
        if (!checkListValidity())
            return;

        if (writeHTML())
        {
            QMessageBox msg(this);
            msg.setText("Fleet written to HTML file");
            msg.setWindowTitle("Success");
            msg.exec();
        }
        else
        {
            QMessageBox msg(this);
            msg.setText("Cannot write list file");
            msg.setWindowTitle("Error");
            msg.exec();
        }

    }
    else
    {
        QMessageBox msg(this);
        msg.setText("No List Loaded to export");
        msg.setWindowTitle("Error");
        msg.exec();
    }
}

// checks is the user is okay with doing an action if their list is invalid
bool MainWindow::checkListValidity()
{
    if (listWidget->checkValid())
        return true;
    {
        confirmDialog msg(this);
        msg.setMsg("One or more list validty checks has failed, print/save anyways?");
        int r = msg.exec();

        if (r == QDialog::Accepted)
            return true;
        else
            return false;

    }
}

