#include "shipview.h"
#include "ui_shipview.h"

#define NAME 0
#define LOCK 1
#define ATTACKS 2
#define DAMAGE 3
#define ARC 4
#define SPECIAL 5

#define LAUNCH 1
#define LIMITED 2


shipView::shipView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::shipView)
{
    ui->setupUi(this);

    ui->weaponTableWidget->setColumnCount(6);


    ui->weaponTableWidget->setHorizontalHeaderItem(NAME, new QTableWidgetItem("Name"));
    ui->weaponTableWidget->setHorizontalHeaderItem(LOCK, new QTableWidgetItem("Lock"));
    ui->weaponTableWidget->setHorizontalHeaderItem(ATTACKS, new QTableWidgetItem("Attacks"));
    ui->weaponTableWidget->setHorizontalHeaderItem(DAMAGE, new QTableWidgetItem("damage"));
    ui->weaponTableWidget->setHorizontalHeaderItem(ARC, new QTableWidgetItem("Arc"));
    ui->weaponTableWidget->setHorizontalHeaderItem(SPECIAL, new QTableWidgetItem("Special"));

    ui->launchTableWidget->setColumnCount(3);

    ui->launchTableWidget->setHorizontalHeaderItem(NAME, new QTableWidgetItem("Name"));
    ui->launchTableWidget->setHorizontalHeaderItem(LAUNCH, new QTableWidgetItem("Launch"));
    ui->launchTableWidget->setHorizontalHeaderItem(LIMITED, new QTableWidgetItem("L"));
}

shipView::~shipView()
{
    delete ui;

}

void shipView::loadShip(const QFleet_Ship_Fleet& ship)
{

    // populate the statline

    ui->scanLabel->setText(QString::number(ship.scan));

    ui->sigLabel->setText(ship.getArmorString());

    ui->thrustLabel->setText(QString::number(ship.thrust));

    ui->hullLabel->setText(QString::number(ship.hull));

    ui->armorLabel->setText(ship.getArmorString());

    ui->pdLabel->setText(QString::number(ship.PD));

    ui->groupLabel->setText(ship.getGroupString());

    ui->tonnageLabel->setText(ship.tonnage.toString());

    while (ui->weaponTableWidget->rowCount() > 0)
        ui->weaponTableWidget->removeRow(0);
    for (auto& element : ship.weapons)
    {
        auto index = ui->weaponTableWidget->rowCount();
        ui->weaponTableWidget->insertRow(index);

        QTableWidgetItem * item = new QTableWidgetItem(element.name);
        item->setTextAlignment(Qt::AlignHCenter);
        ui->weaponTableWidget->setItem(index, NAME, item);

        item = new QTableWidgetItem(element.lock.toString());
        item->setTextAlignment(Qt::AlignHCenter);
        ui->weaponTableWidget->setItem(index, LOCK, item);

        item = new QTableWidgetItem(element.attacks);
        item->setTextAlignment(Qt::AlignHCenter);
        ui->weaponTableWidget->setItem(index, ATTACKS, item);

        item = new QTableWidgetItem(element.damage);
        item->setTextAlignment(Qt::AlignHCenter);
        ui->weaponTableWidget->setItem(index, DAMAGE, item);

        item = new QTableWidgetItem(element.facing.toString());
        item->setTextAlignment(Qt::AlignHCenter);
        ui->weaponTableWidget->setItem(index, ARC, item);

        item = new QTableWidgetItem(element.getSpecialString());
        item->setTextAlignment(Qt::AlignHCenter);
        ui->weaponTableWidget->setItem(index, SPECIAL, item);
    }
    // fit name column
    ui->weaponTableWidget->resizeColumnToContents(0);

    while (ui->launchTableWidget->rowCount() > 0)
        ui->launchTableWidget->removeRow(0);
    for (auto& element : ship.launch)
    {
        auto index = ui->launchTableWidget->rowCount();
        ui->launchTableWidget->insertRow(index);

        QTableWidgetItem * item = new QTableWidgetItem(element.name);
        item->setTextAlignment(Qt::AlignHCenter);
        ui->launchTableWidget->setItem(index, NAME, item);

        item = new QTableWidgetItem(element.getCount());
        item->setTextAlignment(Qt::AlignHCenter);
        ui->launchTableWidget->setItem(index, LAUNCH, item);

        item = new QTableWidgetItem(element.getLimited());
        item->setTextAlignment(Qt::AlignHCenter);
        ui->launchTableWidget->setItem(index, LIMITED, item);
    }
    // fit name column
    ui->launchTableWidget->resizeColumnToContents(0);


}
