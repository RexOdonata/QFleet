#include "shipview.h"
#include "ui_shipview.h"

#define NAME 0
#define LOCK 1
#define ATTACKS 2
#define DAMAGE 3
#define ARC 5
#define SPECIAL 6

#define LAUNCH 1
#define LIMITED 2


shipView::shipView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::shipView)
{
    ui->setupUi(this);

    ui->weaponTableWidget->setColumnCount(6);

    ui->launchTableWidget->setColumnCount(3);
}

shipView::~shipView()
{
    delete ui;

}

void shipView::loadShip(const QFleet_Ship_Fleet& ship)
{

    // populate the statline

    ui->scanLabel->setText(QString(ship.scan));

    ui->sigLabel->setText(ship.getArmorString());

    ui->thrustLabel->setText(QString(ship.thrust));

    ui->hullLabel->setText(QString(ship.hull));

    ui->armorLabel->setText(ship.getArmorString());

    ui->pdLabel->setText(QString(ship.PD));

    ui->groupLabel->setText(ship.getGroupString());

    ui->tonnageLabel->setText(QString(ship.tonnage.toString()));


    for (auto& element : ship.weapons)
    {

    }


}
