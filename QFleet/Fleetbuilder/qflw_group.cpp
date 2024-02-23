#include "qflw_group.h"
#include "qcheckbox.h"
#include "qflw_list.h"
#include "ui_qflw_group.h"

#include "shipviewdialog.h"

#include "qflw_battlegroup.h"

#include "admiralselectdialog.h"

QFLW_Group::QFLW_Group(QWidget *parent, std::optional<QFleet_Ship_Fleet> setShip) :
    QWidget(parent),
    ui(new Ui::QFLW_Group),
    ship(*setShip), cost(QFleet_Cost(ship.name)), cardWidgetPtr(parent)
{
    ui->setupUi(this);

    ui->shipnameLabel->setText(ship.name);

    ui->numSpin->setMinimum(ship.groupL);
    ui->numSpin->setMaximum(ship.groupH);

    this->setAttribute(Qt::WA_DeleteOnClose);


    QFLW_List * listPtr = (QFLW_List*)((QFLW_Battlegroup*)cardWidgetPtr)->getListPtr();

    // used to send a signal to the list that an admiral has been set
    connect(this, &QFLW_Group::setAdmiral, listPtr, &QFLW_List::setAdmiral);

    // the signal that the list uses to toggle admiral buttons and wipe out set admirals
    connect(listPtr, &QFLW_List::admiralSignal, this, &QFLW_Group::admiralSlot);

    connect(this, &QFLW_Group::queryAdmiralSet, listPtr, &QFLW_List::checkAdmiralState);

    bool checkAdmiral;
    emit queryAdmiralSet(&checkAdmiral);

    if (checkAdmiral || ship.tonnage.getIntValue() < 5)
    {
        ui->setAdmiralButton->setEnabled(false);
    }


    // remember to delete any of this present in destructor
    this->admiralPresenceCheck = new QCheckBox(this);

    admiralPresenceCheck->setText("Admiral");
    admiralPresenceCheck->setEnabled(false);
    admiralPresenceCheck->setChecked(true);

    this->admiralLevelLabel = new QLabel(this);

    admiralIndicatorVisibility(false);


}

QFleet_Cost QFLW_Group::getCost() const
{
    return cost;
}

QFLW_Group::~QFLW_Group()
{
    if (admiral > 0)
        emit setAdmiral(false);


     // delete the dynamically created label widgets for admirals
    delete admiralLevelLabel;
    delete admiralPresenceCheck;

    delete ui;
}

// done when
void QFLW_Group::getAdmiralSelect(unsigned int lvl, unsigned int pointsCost)
{
    admiral = lvl;

    admiralCost =  pointsCost;

    cost = getShipGroupCost(ui->numSpin->value());

    updateCost();
}

void QFLW_Group::on_viewShipButton_clicked()
{

    shipViewDialog shipviewDialog(this, ship);

    shipviewDialog.exec();

}


void QFLW_Group::on_setAdmiralButton_clicked()
{
    admiralSelectDialog dialog(this, &ship);

    connect(&dialog, &admiralSelectDialog::sendAdmiralValue, this, &QFLW_Group::getAdmiralSelect);

    int r = dialog.exec();

    if (r == QDialog::Accepted)
    {
        // tell the list that an admiral has been set
        emit setAdmiral(true);

        // show icons
        admiralIndicatorVisibility(true);
    }
}

void QFLW_Group::admiralSlot(const bool val)
{
    // first, light ships ignore this
    if (ship.tonnage.getIntValue() < 5)
        return;

    // if the ship has an admiral present already, hide admiral indicators
    if (!val && admiral > 0)
    {
        admiralIndicatorVisibility(false);
    }

    // this ship has recieved an admiral
    if (val)
    {
        ui->setAdmiralButton->setEnabled(false);
    }
    // admiral reset signal recieved
    else
    {
        // if this ship had the admiral, reset the value and recalculate
        if (admiral > 0)
        {
            admiral = 0;
            admiralCost = 0;
            cost = getShipGroupCost(ui->numSpin->value());
            // update cost, regardless of what happened
            updateCost();
        }

        // for everyone else, re-enable buttons
        ui->setAdmiralButton->setEnabled(true);
    }


}

void QFLW_Group::admiralIndicatorVisibility(const bool val)
{
    if (val)
    {
        admiralPresenceCheck->setVisible(true);
        admiralLevelLabel->setVisible(true);
        ui->admiralLayout->addWidget(admiralPresenceCheck);
        ui->admiralLayout->addWidget(admiralLevelLabel);
        admiralLevelLabel->setText("Lvl " + QString::number(admiral));
    }
    else
    {
        if (admiralPresenceCheck->isVisible())
            ui->admiralLayout->removeWidget(admiralPresenceCheck);
        if (admiralLevelLabel->isVisible())
            ui->admiralLayout->removeWidget(admiralLevelLabel);
        admiralPresenceCheck->setVisible(false);
        admiralLevelLabel->hide();
        admiralPresenceCheck->hide();
    }
}


void QFLW_Group::on_deleteGroupButton_clicked()
{
    this->close();

    flagRemoval(this);
}

QFleet_Cost QFLW_Group::getShipGroupCost(const unsigned int num) const
{
    QFleet_Cost scaling(ship);

    QFleet_Cost scaledCost(cost.name);

    scaledCost.zero();

    for (int i = 0; i < num; i++)
    {
        scaledCost + scaling;
    }

    scaledCost.points += admiralCost;

    return scaledCost;
}



void QFLW_Group::on_numSpin_valueChanged(int arg1)
{
    QFleet_Cost newCost = getShipGroupCost(arg1);

    cost = newCost;

    updateCost();
}

void QFLW_Group::updateCost()
{
    QFLW_Battlegroup * BG = (QFLW_Battlegroup *) this->cardWidgetPtr;

    BG->updateCost();
}

void QFLW_Group::flagRemoval(QFLW_Group * thisPtr)
{
    QFLW_Battlegroup * BG = (QFLW_Battlegroup *) this->cardWidgetPtr;

    BG->removeGroup(thisPtr);
}



