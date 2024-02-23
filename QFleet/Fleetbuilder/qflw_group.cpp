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

    connect(this, &QFLW_Group::signalSetAdmiral, listPtr, &QFLW_List::slotAdmiralSet);

    connect(this, &QFLW_Group::signalAdmiralDeleted, listPtr, &QFLW_List::slotAdmiralDeleted);


    if (ship.tonnage.getIntValue() < 5)
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

void QFLW_Group::removeAdmiral()
{
    if (admiral)
    {
        admiral.reset();

        cost = getShipGroupCost(num);

        updateCost();

        admiralIndicatorVisibility(false);
    }
}

QFLW_Group::~QFLW_Group()
{
    if (admiral)
    {
        emit signalAdmiralDeleted();
    }


     // delete the dynamically created label widgets for admirals
    delete admiralLevelLabel;
    delete admiralPresenceCheck;

    delete ui;
}


void QFLW_Group::on_viewShipButton_clicked()
{

    shipViewDialog shipviewDialog(this, ship);

    shipviewDialog.exec();

}

// this gets a signal from the admiral dialog that sets the admiral cost and value
void QFLW_Group::slotAdmiralValues(admiralVals val)
{
    admiral = val;
}


void QFLW_Group::on_setAdmiralButton_clicked()
{
    admiralSelectDialog dialog(this, &ship);

    admiralVals setadmiralVals;

    connect(&dialog, &admiralSelectDialog::signalAdmiralValue, this, &QFLW_Group::slotAdmiralValues);

    int r = dialog.exec();
    // after this resolves, the admiral should be set

    if (r == QDialog::Accepted)
    {
        // tell the list that an admiral has been set
        emit signalSetAdmiral(this);

        // show icons
        admiralIndicatorVisibility(true);

        cost = getShipGroupCost(num);

        updateCost();
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
        admiralLevelLabel->setText("Lvl " + QString::number(admiral->level) + "/" + QString::number(admiral->cost) + " pts");
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

    if (admiral)
        scaledCost.points += admiral->cost;

    return scaledCost;
}



void QFLW_Group::on_numSpin_valueChanged(int arg1)
{
    QFleet_Cost newCost = getShipGroupCost(arg1);

    num = arg1;

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



