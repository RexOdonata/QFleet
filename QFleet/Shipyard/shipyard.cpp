#include "shipyard.h"
#include "./ui_shipyard.h"
#include "../Components/qfu_specialrules.h"

#include "arsenal.h"
#include "scrapyard.h"
#include "../Components/qfu_xrulesub.h"
#include "../common/fileTypes.h"
#include "../common/windowUtils.h"
#include "../Components/qfleet_launchasset.h"
#include <iostream>


Shipyard::Shipyard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Shipyard)
    , weaponWidget(new dvsx_Widget<QFleet_Weapon>(parent))
    , shipWidget(new dvsx_Widget<QFleet_Ship_Shipyard>(parent))
    , optionWidget(new dvsx_Widget<QFleet_Option>(parent))
    , specialWidget(new dvs_Widget<QString>(parent))
    , launchWidget(new dvs_Widget<QFleet_launchProfile>(parent))
    , launchSelectWidget(new dvs_Widget<QFleet_LaunchAsset>(parent))
{
    ui->setupUi(this);

    ui->weaponRosterLayout->addWidget(weaponWidget);
    weaponWidget->setLabel("Weapons");

    ui->shipRosterLayout->addWidget(shipWidget);
    shipWidget->setLabel("Ships");

    ui->optionLayout->addWidget(optionWidget);
    optionWidget->setLabel("Options");

    ui->specialLayout->addWidget(specialWidget);
    specialWidget->setLabel("Special Rules");

    ui->launchProfileLayout->addWidget(launchWidget);
    launchWidget->setLabel("Launch Profiles");

    ui->launchAssetLayout->addWidget(launchSelectWidget);
    launchSelectWidget->setLabel("Selected Assets");

    {
        qfu_specialRules specialRules;

        for (auto& rule : specialRules.shipRules)
            ui->specialSelectCombo->addItem(rule);

    }

    // add armor options
    {
        // add lock options to combo
        QFleet_Armor armor;
        QVector<QString> strs = armor.getEnumStrings();

        for (auto& str : strs)
        {
            ui->armorCombo->addItem(str);
            ui->passiveCombo->addItem(str);
        }
    }

    // add tonnage options
    {
        // add tonnage options to combo
        QFleet_Tonnage tonnage;
        QVector<QString> strs = tonnage.getEnumStrings();

        for (auto& str : strs)
            ui->tonnageCombo->addItem(str);

    }

    // add Fighter/Bomber generic asset

    QFleet_LaunchAsset strike("Fighters and Bombers");
    strike.launchCap = true;
    launchSelectWidget->add(strike);

    ui->passiveCombo->setCurrentIndex(5);

}

Shipyard::~Shipyard()
{
    delete weaponWidget;

    delete shipWidget;

    delete optionWidget;

    delete specialWidget;

    delete launchWidget;

    delete launchSelectWidget;

    delete ui;
}


void Shipyard::on_newWeaponButton_clicked()
{

    std::shared_ptr<QFleet_Weapon> newWeaponPtr = std::make_shared<QFleet_Weapon>("New Weapon");

    Arsenal * arsenalWindow = new Arsenal(this, newWeaponPtr);

    arsenalWindow->setAttribute(Qt::WA_DeleteOnClose);

    int r = arsenalWindow->exec();    

    if (r == QDialog::Accepted)
        weaponWidget->add(*newWeaponPtr);

}


void Shipyard::on_copyWeaponButton_clicked()
{
    auto sel = weaponWidget->getSelected();

    if (sel)
    {
        std::shared_ptr<QFleet_Weapon> clonedWeaponPtr = std::make_shared<QFleet_Weapon>(*sel);

        Arsenal * arsenalWindow = new Arsenal(this, clonedWeaponPtr);

        arsenalWindow->setAttribute(Qt::WA_DeleteOnClose);

        int r = arsenalWindow->exec();        

        if (r == QDialog::Accepted)
            weaponWidget->add(*clonedWeaponPtr);

    }

}

// works by removing the existing weapon and adding a copy of it after modifications back
void Shipyard::on_editWeaponButton_clicked()
{
    auto sel = weaponWidget->getSelected();
    if (sel)
    {
        weaponWidget->remove();

        std::shared_ptr<QFleet_Weapon> newWeaponPtr = std::make_shared<QFleet_Weapon>(*sel);

        Arsenal * arsenalWindow = new Arsenal(this, newWeaponPtr);

        arsenalWindow->setAttribute(Qt::WA_DeleteOnClose);

        int r = arsenalWindow->exec();


        if (r == QDialog::Accepted)
            weaponWidget->add(*newWeaponPtr);
        else
            weaponWidget->add(*sel);

    }
}


void Shipyard::on_deleteWeaponButton_clicked()
{
    auto sel = weaponWidget->getSelected();

    if (sel)
        weaponWidget->remove();
}

void Shipyard::on_actionLoad_triggered()
{
    shipWidget->loadFromFile(this, fileType_shipData());
}


void Shipyard::on_actionSave_triggered()
{
    shipWidget->saveToFile(this, fileType_shipData());
}


void Shipyard::on_launchAddButton_clicked()
{
    QVector<QFleet_LaunchAsset> assets = launchSelectWidget->getMultiSelected();


    QFleet_launchProfile lp("newLP");

    lp.setCount(ui->launchQuantitySpin->value());

    lp.setLimited(ui->limitedSpin->value());

    bool isStrike = false;

    QVector<QString> names;

    for (auto& element : assets)
    {
        names.push_back(element.name);

        if (element.launchCap)
            isStrike = true;
    }

    lp.setStrike(isStrike);


    lp.setAssetNames(names);

    QString newName = lp.getAssetString();

    newName.replace(" & ", ",");

    newName.prepend(QString::number(lp.getCount()).append("x"));

    if (lp.getLimited() > 0)
        newName.append(QString(",").append(QString("L").append(QString::number(lp.getLimited()))));

    lp.name = newName;

    launchWidget->add(lp);
}


void Shipyard::on_launchDeleteButton_clicked()
{
    auto sel = launchWidget->getSelected();

    if (sel)
        launchWidget->remove();

}

void Shipyard::on_addSpecialButton_clicked()
{
    QString str = ui->specialSelectCombo->currentText();
    unsigned int num = ui->specialNumSpin->value();

    str = xrulesub(str, num);

    specialWidget->add(str);
}


void Shipyard::on_deleteSpecialCombo_clicked()
{
    specialWidget->remove();
}


void Shipyard::on_newOptionButton_clicked()
{
    std::shared_ptr<QFleet_Option> newOptionPtr = std::make_shared<QFleet_Option>("newOption");

    auto launchAssetData = launchSelectWidget->getData();
    Scrapyard * scrapyardWindow = new Scrapyard(this, newOptionPtr, &launchAssetData);

    scrapyardWindow->setAttribute(Qt::WA_DeleteOnClose);

    int r = scrapyardWindow->exec();

    scrapyardWindow->setAttribute(Qt::WA_DeleteOnClose);

    if (r == QDialog::Accepted)
        optionWidget->add(*newOptionPtr);

}


void Shipyard::on_editOptionButton_clicked()
{
    auto sel = optionWidget->getSelected();

    if (sel)
    {
        optionWidget->remove();

        std::shared_ptr<QFleet_Option> newOptionPtr = std::make_shared<QFleet_Option>(*sel);

        auto launchAssetData = launchSelectWidget->getData();
        Scrapyard * scrapyardWindow = new Scrapyard(this, newOptionPtr, &launchAssetData);

        scrapyardWindow->setAttribute(Qt::WA_DeleteOnClose);

        int r = scrapyardWindow->exec();

        if (r == QDialog::Accepted)
            optionWidget->add(*newOptionPtr);
        else
            optionWidget->add(*sel);
    }
}


void Shipyard::on_deleteOptionButton_clicked()
{
    auto sel = optionWidget->getSelected();

    if (sel)
        optionWidget->remove();
}


void Shipyard::on_saveShipButton_clicked()
{

    QFleet_Ship_Shipyard newShip(ui->nameEdit->text());

    newShip.points = ui->pointsSpin->value();

    newShip.scan = ui->scanSpin->value();

    newShip.signature = ui->sigSpin->value();

    newShip.altSig = ui->altSig_spin->value();

    newShip.thrust = ui->sigSpin->value();

    newShip.hull = ui->hullSpin->value();

    newShip.PD = ui->pdSpin->value();

    newShip.groupL = ui->glSpin->value();

    newShip.groupH = ui->ghSpin->value();

    newShip.tonnage = QFleet_Tonnage(ui->tonnageCombo->currentText());

    newShip.armor = QFleet_Armor(ui->armorCombo->currentText());

    newShip.passive = QFleet_Armor(ui->passiveCombo->currentText());

    {
    auto weapons = weaponWidget->getData();

        for (auto& weapon : weapons)
            newShip.weapons.push_back(weapon);
    }

    {
        auto launchProfiles = launchWidget->getData();

        for (auto& lp : launchProfiles)
            newShip.launch.push_back(lp);
    }

    {
        auto options = optionWidget->getData();

        for (auto& opt : options)
            newShip.options.push_back(opt);
    }

    {
        QVector<QFleet_Faction> factions;

        if (ui->ucmCheck->isChecked())
            factions.push_back(QFleet_Faction(faction::UCM));
        if (ui->scourgeCheck->isChecked())
            factions.push_back(QFleet_Faction(faction::SCOURGE));
        if (ui->phrCheck->isChecked())
            factions.push_back(QFleet_Faction(faction::PHR));
        if (ui->shaltariCheck->isChecked())
            factions.push_back(QFleet_Faction(faction::SHALTARI));
        if (ui->resistanceCheck->isChecked())
            factions.push_back(QFleet_Faction(faction::RESISTANCE));

        newShip.factions = factions;

    }

    newShip.admiralDiscount = ui->admiralDiscountSpin->value();

    newShip.maxBroadsides = ui->maxBroadsideSpin->value();

    newShip.maxOptions = ui->maxOptionsSpin->value();

    newShip.minOptions = ui->maxOptionsSpin->value();

    {
        QVector<QString> specials = specialWidget->getData();

        newShip.specialRules = specials;
    }


    shipWidget->add(newShip);
}


void Shipyard::on_loadShipButton_clicked()
{
    auto loadShip = shipWidget->getSelected();

    if (loadShip)
    {

        weaponWidget->clear();
        specialWidget->clear();
        launchWidget->clear();
        optionWidget->clear();

        ui->nameEdit->setText(loadShip->name);

        ui->pointsSpin->setValue(loadShip->points);

        ui->thrustSpin->setValue(loadShip->thrust);

        ui->scanSpin->setValue(loadShip->scan);

        ui->sigSpin->setValue(loadShip->signature);

        ui->altSig_spin->setValue(loadShip->altSig);

        ui->hullSpin->setValue(loadShip->hull);

        ui->pdSpin->setValue(loadShip->PD);

        ui->glSpin->setValue(loadShip->groupL);

        ui->ghSpin->setValue(loadShip->groupH);

        ui->armorCombo->setCurrentText(loadShip->armor.toString());
        ui->passiveCombo->setCurrentText(loadShip->passive.toString());

        ui->tonnageCombo->setCurrentText(loadShip->tonnage.toString());

        specialWidget->add(loadShip->specialRules);

        weaponWidget->add(loadShip->weapons);

        optionWidget->add(loadShip->options);

        launchWidget->add(loadShip->launch);

        ui->maxBroadsideSpin->setValue(loadShip->maxBroadsides);

        ui->minOptionsSpin->setValue(loadShip->minOptions);

        ui->maxOptionsSpin->setValue(loadShip->maxOptions);

        ui->admiralDiscountSpin->setValue(loadShip->admiralDiscount);

        {
            QMap<faction, bool> factionMap;

            for (auto faction : loadShip->factions)
                factionMap.insert(faction.getVal(), true);

            if (factionMap.contains(faction::UCM))
                ui->ucmCheck->setCheckState(Qt::Checked);
            if (factionMap.contains(faction::SCOURGE))
                ui->scourgeCheck->setCheckState(Qt::Checked);
            if (factionMap.contains(faction::PHR))
                ui->phrCheck->setCheckState(Qt::Checked);
            if (factionMap.contains(faction::SHALTARI))
                ui->shaltariCheck->setCheckState(Qt::Checked);
            if (factionMap.contains(faction::RESISTANCE))
                ui->resistanceCheck->setCheckState(Qt::Checked);
        }
    }
}


void Shipyard::on_loadLaunchAssetsButton_clicked()
{
    QVector<QFleet_LaunchAsset> assets;

    loadVectorFromJsonFile(this, assets, fileType_launchData());

    launchSelectWidget->add(assets);
}

