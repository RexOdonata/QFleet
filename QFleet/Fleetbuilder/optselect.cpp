#include "optselect.h"
#include "ui_optselect.h"

#include <QTableWidgetItem>
#include <QMessageBox>

#define NAME 0
#define BROADSIDE 1
#define ONEONLY 2
#define COST 3

optSelect::optSelect(QWidget *parent, const QFleet_Ship_Shipyard * refShip, QVector<QFleet_Option> * setOptionList) :
    QDialog(parent),
    ui(new Ui::optSelect),
    optionList(setOptionList),
    selectedOptionWidget(new dvs_Widget(parent))
{
    ui->setupUi(this);

    ui->selectOptionsLayout->addWidget(selectedOptionWidget);
    selectOptionsRoster = new dvs_Data<QFleet_Option, dvs_Widget>(selectedOptionWidget);
    selectedOptionWidget->setLabel("Selected Options");

    ui->optionTableWidget->setColumnCount(4);

    ui->optionTableWidget->setHorizontalHeaderItem(NAME, new QTableWidgetItem("Option"));
    ui->optionTableWidget->setHorizontalHeaderItem(BROADSIDE, new QTableWidgetItem("Broadside"));
    ui->optionTableWidget->setHorizontalHeaderItem(ONEONLY, new QTableWidgetItem("Singular"));
    ui->optionTableWidget->setHorizontalHeaderItem(COST, new QTableWidgetItem("Cost"));

    ui->minOptionNumLabel->setText(QString::number(refShip->minOptions));
    ui->maxOptionsNumlabel->setText(QString::number(refShip->maxOptions));

    broadsideLimit = refShip->maxBroadsides;
    broadsideCount = 0;
    minOptions = refShip->minOptions;
    maxOptions = refShip->maxOptions;


    for (auto& option : refShip->options)
    {
        optMap.insert(option.name, option);

        auto index = ui->optionTableWidget->rowCount();
        ui->optionTableWidget->insertRow(index);

        // NAME
        QTableWidgetItem * item = new QTableWidgetItem(option.name);
        item->setTextAlignment(Qt::AlignHCenter);
        ui->optionTableWidget->setItem(index,NAME,item);

        // BROADSIDE
        QString f="";
        if (option.broadside)
            f = "Y";


        item = new QTableWidgetItem(f);
        item->setTextAlignment(Qt::AlignHCenter);
        ui->optionTableWidget->setItem(index,BROADSIDE,item);

        // ONE ONLY
        if (option.oneOnly)
            f = "Y";
        else
            f="";

        item = new QTableWidgetItem(f);
        item->setTextAlignment(Qt::AlignHCenter);
        ui->optionTableWidget->setItem(index,ONEONLY,item);


        item = new QTableWidgetItem(QString::number(option.points));
        item->setTextAlignment(Qt::AlignHCenter);
        ui->optionTableWidget->setItem(index,COST,item);
    }
    ui->optionTableWidget->resizeColumnToContents(0);
}

// check how many total options are selected and update counts, do same for broadside count
void optSelect::updateCounts()
{
    unsigned int broadsides = 0;
    unsigned int cost = 0;

    for (auto& opt : selectOptionsRoster->getData())
    {
        if (opt.broadside)
            broadsides++;

        cost += opt.points;
    }

    this->broadsideCount = broadsides;

    ui->broadsideOptionsNumLabel->setText(QString::number(this->broadsideCount));
    ui->selectedOptionNumLabel->setText(QString::number(selectOptionsRoster->getSize()));

    ui->pointsLabel->setText(QString::number(cost));
}

bool optSelect::checkAdd(const QFleet_Option& opt, QString& reason)
{
    // if at max options count, can't add
    if (selectOptionsRoster->getSize() == maxOptions)
    {
        reason = "hardpoints full";
        return false;
    }

    // if at broadside limit, can't add broadside
    else if (broadsideCount == broadsideLimit && opt.broadside)
    {
        reason = "broadsides full";
        return false;
    }

    // if there is already one of this ONEONLY option
    else if (opt.oneOnly)
    {
        for (auto& selectedOption : selectOptionsRoster->getData())
        {
            if (selectedOption.name == opt.name)
            {
                reason = "already has a ";
                reason.append(opt.name);
                return false;
            }
        }
    }
    else
        return true;

    // above should handle this but whatever
    return true;
}

optSelect::~optSelect()
{
    delete selectOptionsRoster;

    delete selectedOptionWidget;

    delete ui;
}

void optSelect::on_addOptionButton_clicked()
{
    auto selectedRow = ui->optionTableWidget->selectedItems();

    // short circuit function
    if (selectedRow.size() == 0)
        return;

    auto rowIndex = ui->optionTableWidget->row(selectedRow[0]);

    QString optName = ui->optionTableWidget->item(rowIndex, NAME)->text();

    QFleet_Option opt = optMap.value(optName);

    QString reason;

    if (checkAdd(opt,reason))
    {
        selectOptionsRoster->add(opt);
        if (opt.broadside)
            broadsideCount++;

        updateCounts();
    }
    else
    {
        QMessageBox msgBox;
        QString msg = "Can't Add: ";
        msg.append(reason);
        msgBox.setText(msg);
        msgBox.exec();
    }

}


void optSelect::on_removeOptionButton_clicked()
{
    auto selectedOpt = selectOptionsRoster->getSelected();

    if (!selectedOpt.has_value())
        return;

    if (selectedOpt->broadside)
        broadsideCount--;

    selectOptionsRoster->remove();
}


void optSelect::on_saveOptionsButton_clicked()
{

    if (selectOptionsRoster->getSize() >= minOptions)
    {
        // add the selected options to the ship
        for (auto& opt : selectOptionsRoster->getData())
            optionList->push_back(opt);

        this->done(QDialog::Accepted);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Minimum hardpoints not filled");
        msgBox.exec();
    }
}

