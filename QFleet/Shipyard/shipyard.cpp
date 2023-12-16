#include "shipyard.h"
#include "./ui_shipyard.h"
#include "../Components/qfu_specialrules.h"

#include "arsenal.h"
#include "scrapyard.h"
#include "../Components/qfu_xrulesub.h"
#include "../common/fileTypes.h"
#include "../common/windowUtils.h"
#include "../Components/qfleet_launchasset.h"


Shipyard::Shipyard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Shipyard)
    , weaponWidget(std::make_shared<dvsx_Widget>(parent))
    , shipWidget(std::make_shared<dvsx_Widget>(parent))
    , optionWidget(std::make_shared<dvsx_Widget>(parent))
    , specialWidget(std::make_shared<dvs_Widget>(parent))
    , launchWidget(std::make_shared<dvs_Widget>(parent))
    , launchSelectWidget(std::make_shared<dvs_Widget>(parent))
{
    ui->setupUi(this);

    ui->weaponRosterLayout->addWidget(weaponWidget.get());
    weaponRoster = std::make_shared<dvs_Data<QFleet_Weapon, dvsx_Widget>>(weaponWidget.get());
    weaponWidget->setLabel("Weapons");

    ui->shipRosterLayout->addWidget(shipWidget.get());
    shipRoster = std::make_shared<dvs_Data<QFleet_Ship_Shipyard, dvsx_Widget>>(shipWidget.get());
    shipWidget->setLabel("Ships");

    ui->optionLayout->addWidget(optionWidget.get());
    optionRoster = std::make_shared<dvs_Data<QFleet_Option, dvsx_Widget>>(optionWidget.get());
    optionWidget->setLabel("Options");

    ui->specialLayout->addWidget(specialWidget.get());
    specialRoster = std::make_shared<dvs_Data<QString, dvs_Widget>>(specialWidget.get());
    specialWidget->setLabel("Special Rules");

    ui->launchProfileLayout->addWidget(launchWidget.get());
    launchRoster = std::make_shared<dvs_Data<QFleet_launchProfile, dvs_Widget>>(launchWidget.get());
    launchWidget->setLabel("Launch Profiles");

    ui->launchAssetLayout->addWidget(launchSelectWidget.get());
    launchSelect = std::make_shared<dvs_Data<QFleet_LaunchAsset, dvs_Widget>>(launchSelectWidget.get());
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
    launchSelect->add(strike);

}

Shipyard::~Shipyard()
{
    delete ui;
}


void Shipyard::on_newWeaponButton_clicked()
{

    std::shared_ptr<QFleet_Weapon> newWeaponPtr = std::make_shared<QFleet_Weapon>("New Weapon");

    Arsenal * arsenalWindow = new Arsenal(this, newWeaponPtr);

    int r = arsenalWindow->exec();

    if (r == QDialog::Accepted)
        weaponRoster->add(*newWeaponPtr);

    delete arsenalWindow;

}


void Shipyard::on_copyWeaponButton_clicked()
{
    auto sel = weaponRoster->getSelected();

    if (sel)
    {
        std::shared_ptr<QFleet_Weapon> clonedWeaponPtr = std::make_shared<QFleet_Weapon>(*sel);

        Arsenal * arsenalWindow = new Arsenal(this, clonedWeaponPtr);

        int r = arsenalWindow->exec();

        if (r == QDialog::Accepted)
            weaponRoster->add(*clonedWeaponPtr);

        delete arsenalWindow;
    }

}

// works by removing the existing weapon and adding a copy of it after modifications back
void Shipyard::on_editWeaponButton_clicked()
{
    auto sel = weaponRoster->getSelected();
    if (sel)
    {
        weaponRoster->remove();

        std::shared_ptr<QFleet_Weapon> newWeaponPtr = std::make_shared<QFleet_Weapon>(*sel);

        Arsenal * arsenalWindow = new Arsenal(this, newWeaponPtr);

        int r = arsenalWindow->exec();

        if (r == QDialog::Accepted)
            weaponRoster->add(*newWeaponPtr);
        else
            weaponRoster->add(*sel);

        delete arsenalWindow;

    }
}


void Shipyard::on_deleteWeaponButton_clicked()
{
    auto sel = weaponRoster->getSelected();

    if (sel)
        weaponRoster->remove();
}

void Shipyard::on_actionLoad_triggered()
{
    shipRoster->loadFromFile(this, fileType_shipData());
}


void Shipyard::on_actionSave_triggered()
{
    shipRoster->saveToFile(this, fileType_shipData());
}


void Shipyard::on_launchAddButton_clicked()
{
    QVector<QFleet_LaunchAsset> assets = launchSelect->getMultiSelected();


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

    launchRoster->add(lp);
}


void Shipyard::on_launchDeleteButton_clicked()
{
    auto sel = launchRoster->getSelected();

    if (sel)
        launchRoster->remove();

}

void Shipyard::on_addSpecialButton_clicked()
{
    QString str = ui->specialSelectCombo->currentText();
    unsigned int num = ui->specialNumSpin->value();

    str = xrulesub(str, num);

    specialRoster->add(str);
}


void Shipyard::on_deleteSpecialCombo_clicked()
{
    specialRoster->remove();
}


void Shipyard::on_newOptionButton_clicked()
{
    std::shared_ptr<QFleet_Option> newOptionPtr = std::make_shared<QFleet_Option>("newOption");

    auto launchAssetData = launchSelect->getData();
    Scrapyard * scrapyardWindow = new Scrapyard(this, newOptionPtr, &launchAssetData);

    int r = scrapyardWindow->exec();

    if (r == QDialog::Accepted)
        optionRoster->add(*newOptionPtr);

    delete scrapyardWindow;

}


void Shipyard::on_editOptionButton_clicked()
{
    auto sel = optionRoster->getSelected();

    if (sel)
    {
        optionRoster->remove();

        std::shared_ptr<QFleet_Option> newOptionPtr = std::make_shared<QFleet_Option>(*sel);

        auto launchAssetData = launchSelect->getData();
        Scrapyard * scrapyardWindow = new Scrapyard(this, newOptionPtr, &launchAssetData);

        int r = scrapyardWindow->exec();

        if (r == QDialog::Accepted)
            optionRoster->add(*newOptionPtr);
        else
            optionRoster->add(*sel);

        delete scrapyardWindow;
    }
}


void Shipyard::on_deleteOptionButton_clicked()
{
    auto sel = optionRoster->getSelected();

    if (sel)
        optionRoster->remove();
}


void Shipyard::on_saveShipButton_clicked()
{

}


void Shipyard::on_loadShipButton_clicked()
{

}


void Shipyard::on_loadLaunchAssetsButton_clicked()
{
    QVector<QFleet_LaunchAsset> assets;

    loadVectorFromJsonFile(this, assets, fileType_launchData());

    launchSelect->add(assets);
}

