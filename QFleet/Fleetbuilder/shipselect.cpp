#include "shipselect.h"
#include "ui_shipselect.h"

#include "optselect.h"

shipSelect::shipSelect(QWidget *parent, const QMap<QString,QFleet_Ship_Shipyard> * setShipData, shipHook * setSelectedShip) :
    QDialog(parent),
    ui(new Ui::shipSelect),
    shipData(setShipData),
    selectedShip(setSelectedShip)
{
    ui->setupUi(this);

    shipTreeModel = new QStandardItemModel(0,1);

    shipViewWidget = new shipView(this);

    ui->shipViewLayout->addWidget(shipViewWidget);

    // setup the tree view

    ui->treeView->setHeaderHidden(true);

    std::array<QStandardItem *, 5> categories;
    categories[0] = new QStandardItem(QString("Lights"));
    categories[1] = new QStandardItem(QString("Destroyers"));
    categories[2] = new QStandardItem(QString("Cruisers"));
    categories[3] = new QStandardItem(QString("Heavies"));
    categories[4] = new QStandardItem(QString("Flagships"));

    // insert ships items into the category items they belong in
    for (auto& shipName : shipData->keys())
    {
        insertShip(categories, shipName);
    }

    // insert the categories
    for (auto& item : categories)
    {
        auto index = shipTreeModel->rowCount();

        shipTreeModel->insertRow(index);

        shipTreeModel->setItem(index, item);
    }

    ui->treeView->setModel(shipTreeModel);

    ui->validCheck->setEnabled(false);
}

void shipSelect::insertShip(std::array<QStandardItem *,5> models, const QString shipName)
{

    QStandardItem * shipItem = new QStandardItem(shipName);

    auto val = shipData->value(shipName).tonnage.getIntValue();

    switch (val)
    {
        case 1:
            models[0]->appendRow(shipItem);
            break;

        case 2:
            models[1]->appendRow(shipItem);
            break;

        case 5:
            models[2]->appendRow(shipItem);
            break;

        case 10:
            models[3]->appendRow(shipItem);
            break;

        case 15:
            models[4]->appendRow(shipItem);
            break;

        case 30:
            models[4]->appendRow(shipItem);
            break;

        default:
            // this should NEVER happen, but it handles a possible memory leak
            delete shipItem;
            break;
    }
}

shipSelect::~shipSelect()
{
    selectedShip->valid = false;
    delete ui;
}

// given the selected ship, load the ship view andset that ship to be selected
void shipSelect::on_treeView_activated(const QModelIndex &index)
{
    QString shipName = shipTreeModel->itemFromIndex(index)->text();

    if (shipData->contains(shipName))
    {
        QFleet_Ship_Shipyard indexShip = shipData->value(shipName);

        QVector<QFleet_Option> blank;

        QFleet_Ship_Fleet fleetShip = createShip(indexShip,blank);

        selectedShip->ship = fleetShip;
        // check if the selected ship has mandatory options which won't have been selected at this point
        if (checkMinOpts(indexShip))
        {
            selectedShip->valid = true;
            ui->validCheck->setChecked(Qt::Checked);
        }
        else
        {
            selectedShip->valid = false;
            ui->validCheck->setChecked(Qt::Unchecked);
        }


        shipViewWidget->loadShip(fleetShip);
    }
}

QFleet_Ship_Fleet shipSelect::createShip(const QFleet_Ship_Shipyard& shipSrc, QVector<QFleet_Option>& opts)
{
    QFleet_Ship_Fleet newShip(shipSrc.name);

    newShip.points = shipSrc.points;
    newShip.scan = shipSrc.scan;
    newShip.signature = shipSrc.signature;
    newShip.altSig = shipSrc.altSig;
    newShip.thrust = shipSrc.thrust;
    newShip.hull = shipSrc.hull;
    newShip.armor = shipSrc.armor;
    newShip.passive = shipSrc.passive;
    newShip.PD = shipSrc.PD;
    newShip.groupL = shipSrc.groupL;
    newShip.groupH = shipSrc.groupH;
    newShip.tonnage = shipSrc.tonnage;
    newShip.specialRules = shipSrc.specialRules;
    newShip.weapons = shipSrc.weapons;
    newShip.launch = shipSrc.launch;
    newShip.admiralDiscount = shipSrc.admiralDiscount;

    // extract options into the ship
    for (auto& opt : opts)
    {
        newShip.points += opt.points;

            switch(opt.type.getVal())
            {
                case optType::WEAPONS:
                for (auto& weapon : *opt.weaponVecPtr)
                    {
                        newShip.weapons.push_back(weapon);
                    }
                    break;

                case optType::LAUNCH:
                    newShip.launch.push_back(*opt.launchProfilePtr);
                    break;

                case optType::STAT:
                    switch(opt.statTypePtr->getVal())
                    {

                    case statID::scan:
                        newShip.scan += *opt.statBonusPtr;
                        break;
                    case statID::sig:
                        newShip.signature += *opt.statBonusPtr;
                        break;
                    case statID::thrust:
                        newShip.thrust += *opt.statBonusPtr;
                        break;
                    case statID::hull:
                        newShip.hull += *opt.statBonusPtr;
                        break;
                    case statID::PD:
                        newShip.PD += *opt.statBonusPtr;
                        break;
                    }

                    break;

                case optType::SPECIAL:
                    newShip.specialRules.push_back(*opt.specialPtr);
                    break;
            }
    }

    return newShip;
}


void shipSelect::on_treeView_clicked(const QModelIndex &index)
{
    // this is just here to stop a compilation error, resetting moc files is annoying
}

bool shipSelect::checkMinOpts(const QFleet_Ship_Shipyard& ship)
{
    if (ship.minOptions > 0)
            return false;
    else
            return true;
}

void shipSelect::on_selectOptionsButton_clicked()
{
    auto selectionIndex = ui->treeView->selectionModel()->selectedIndexes();

    if (selectionIndex.size()>0)
    {
            auto selection = selectionIndex[0];

            QString shipName = shipTreeModel->itemFromIndex(selection)->text();

            QFleet_Ship_Shipyard indexShip = shipData->value(shipName);

            QVector<QFleet_Option> options;

            optSelect * dialog = new optSelect(this, &indexShip, &options);

            dialog->setAttribute(Qt::WA_DeleteOnClose);

            int r = dialog->exec();

            if (r == QDialog::Accepted)
            {
                QFleet_Ship_Fleet fleetShip = createShip(indexShip, options);

                selectedShip->ship = fleetShip;
                selectedShip->valid = true;
                ui->validCheck->setChecked(Qt::Checked);
            }
            else
            {
                selectedShip->valid = false;
                ui->validCheck->setChecked(Qt::Unchecked);
            }
    }
}
