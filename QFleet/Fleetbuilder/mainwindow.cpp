#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "initlistdialog.h"

#include "../common/fileTypes.h"
#include "qmessagebox.h"
#include <iostream>

#include "../ListParts/qfleet_list.h"

#include <QFileDialog>
#include <QJsonParseError>

#include "../ListPrinter/qfp_strategycard.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete listWidget;

    delete ui;
}



void MainWindow::on_actionNew_triggered()
{

    // if a list is already loaded, delete it
    if (listWidget)
    {
        listWidget.clear();
    }

    listInit data;
    initListDialog * newListData = new initListDialog(this,&data);

    newListData->setAttribute(Qt::WA_DeleteOnClose);

    int r = newListData->exec();

    if (r==QDialog::Accepted)
    {
        listWidget = new QFLW_List(this);

        listWidget->setFaction(data.listFaction);
        listWidget->setPointsLimit(data.listPoints);

        pointsLimit = data.listPoints;
        faction = data.listFaction;


        // load ship Data for the faction of the new list
        loadMapFromJsonFile(this, allShipData);

        ui->fleetBox->addWidget(listWidget);

        listWidget->updateHeader();

        // put something here about refreshing the UI view or delete what is already there if neccessary

    }

}


void MainWindow::loadMapFromJsonFile(QWidget * parentWindow, QMap<QString, QFleet_Ship_Shipyard>& data)
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
}

void MainWindow::on_actionLoad_triggered()
{

    // if a list is already loaded, delete it
    if (listWidget)
    {
        listWidget.clear();
    }

    QString filename = QFileDialog::getOpenFileName(this, "Select QFleet List", QDir::currentPath());

    QFile file(filename);


    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray bytes = file.readAll();

        file.close();

        QJsonParseError err;

        QJsonDocument jsonData = QJsonDocument::fromJson(bytes, &err);

        QJsonObject wrapperObj = jsonData.object();        


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
    loadMapFromJsonFile(this, allShipData);

    this->pointsLimit = list.getPointsLimit();

    this->listWidget = new QFLW_List(this, list);

    ui->fleetBox->addWidget(listWidget);
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
       emit sendSelectedShip(selectedShip,cardPtr);
    }
    else
    {
        QMessageBox msg(this);
        msg.setText("Select a ship to add in the Ship Menu");
        msg.exec();
    }
}


void MainWindow::on_actionSave_triggered()
{

    if (!listWidget.isNull())
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


void MainWindow::on_actionStrategy_Cards_triggered()
{
    if (!listWidget.isNull())
    {
        QString dir = QFileDialog::getExistingDirectory(this, "Save strategy cards", QDir::currentPath());

        dir.append("/");

        auto cards = listWidget->createListPart().getCards();

        auto index = 0;

        QHash<QString, bool> stringGuard;

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

            int r = file.open(QIODevice::WriteOnly);

            r = cardImage.save(&file, "png");

            file.close();

            index++;
        }
    }
    else
    {
        QMessageBox msg(this);
        msg.setText("No List Loaded to print");
        msg.exec();
    }
}

