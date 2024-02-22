#include "qflw_group.h"
#include "ui_qflw_group.h"

#include "shipviewdialog.h"

#include "qflw_battlegroup.h"

QFLW_Group::QFLW_Group(QWidget *parent, std::optional<QFleet_Ship_Fleet> setShip) :
    QWidget(parent),
    ui(new Ui::QFLW_Group),
    ship(*setShip), cost(*setShip), cardWidgetPtr(parent)
{
    ui->setupUi(this);

    ui->shipnameLabel->setText(ship.name);

    ui->numSpin->setMinimum(ship.groupL);
    ui->numSpin->setMaximum(ship.groupH);

    this->setAttribute(Qt::WA_DeleteOnClose);


}

QFleet_Cost QFLW_Group::getCost() const
{
    return cost;
}

QFLW_Group::~QFLW_Group()
{
    delete ui;
}

void QFLW_Group::on_viewShipButton_clicked()
{

    shipViewDialog shipviewDialog(this, ship);

    shipviewDialog.exec();

}


void QFLW_Group::on_setAdmiralButton_clicked()
{

}


void QFLW_Group::on_deleteGroupButton_clicked()
{
    this->close();

    flagRemoval(this);
}


void QFLW_Group::on_numSpin_valueChanged(int arg1)
{
    QFleet_Cost scaling(ship);

    cost.zero();

    for (int i = 0; i < arg1; i++)
    {
        cost + scaling;
    }

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



