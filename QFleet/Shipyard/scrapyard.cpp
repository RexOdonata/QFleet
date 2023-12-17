#include "scrapyard.h"
#include "ui_scrapyard.h"

#include "../Components/qfu_xrulesub.h"
#include "../Components/qfu_specialrules.h"

#include "arsenal.h"

Scrapyard::Scrapyard(QWidget *parent, std::shared_ptr<QFleet_Option> optionPtr, QVector<QFleet_LaunchAsset> * assetVec) :
    QDialog(parent),
    ui(new Ui::Scrapyard),
    weaponWidget(new dvs_Widget(parent)),
    launchAssetWidget(new dvs_Widget(parent)),
    launchProfileWidget(new dvs_Widget(parent)),
    specialWidget(new dvs_Widget(parent)),
    option(optionPtr)

{
    ui->setupUi(this);

    // create the launchAssets container
    ui->launchAssetLayout->addWidget(launchAssetWidget);
    launchAssetRoster = new dvs_Data<QFleet_LaunchAsset, dvs_Widget>(launchAssetWidget);
    launchAssetWidget->setLabel("Launch Assets ");

    launchAssetRoster->add(*assetVec);

    // create the LaunchProfile container
    ui->launchProfileLayout->addWidget(launchProfileWidget);
    launchProfileRoster = new dvs_Data<QFleet_launchProfile, dvs_Widget>(launchProfileWidget);
    launchProfileWidget->setLabel("Special Rules");

    // create the special rules container
    ui->specialRosterLayout->addWidget(specialWidget);
    specialRoster = new dvs_Data<QString, dvs_Widget>(specialWidget);
    specialWidget->setLabel("Launch profile");

    // create the weapon container
    ui->weaponLayout->addWidget(weaponWidget);
    weaponRoster = new dvs_Data<QFleet_Weapon, dvs_Widget>(weaponWidget);
    weaponWidget->setLabel("Weapon");

    {
        qfu_specialRules specialRules;

        for (auto& rule : specialRules.shipRules)
            ui->specialSelectCombo->addItem(rule);

    }

    // LOAD CURRENT VALUES
    if (option)
    {
        ui->nameEdit->setText(option->getName());

        ui->pointSpin->setValue(option->points);

        if (option->type.hasVal())
        {

            optType type = option->type.getVal();

            if (type == optType::WEAPONS)
            {
                weaponRoster->add(*option->weaponVecPtr);
            }
            else if (type == optType::LAUNCH)
            {
                launchProfileRoster->add(*option->launchProfilePtr);
            }
            else if (type == optType::STAT)
            {
                statID statType = option->statTypePtr->getVal();

                if (statType==statID::scan)
                    ui->scanRadio->setChecked(true);
                else if (statType==statID::thrust)
                    ui->thrustRadio->setChecked(true);
                else if (statType==statID::PD)
                    ui->pdRadio->setChecked(true);
                else if (statType==statID::sig)
                    ui->sigRadio->setChecked(true);
                else if (statType==statID::hull)
                    ui->scanRadio->setChecked(true);

                ui->statBonusSpin->setValue(*option->statBonusPtr);
            }
            else if (type == optType::SPECIAL)
            {
                specialRoster->add(*option->specialPtr);
            }
        }


        if (option->oneOnly)
            ui->singleCheck->setCheckState(Qt::Checked);
        else
            ui->singleCheck->setCheckState(Qt::Unchecked);

        if (option->broadside)
            ui->broadsideCheck->setCheckState(Qt::Checked);
        else
            ui->broadsideCheck->setCheckState(Qt::Unchecked);
    }

}

Scrapyard::~Scrapyard()
{
    // widgets

    delete weaponWidget;

    delete launchAssetWidget;

    delete launchProfileWidget;

    delete specialWidget;

    // data

    delete weaponRoster;

    delete launchAssetRoster;

    delete launchProfileRoster;

    delete specialRoster;

    delete ui;
}


void Scrapyard::on_launchAddButton_clicked()
{
    QVector<QFleet_LaunchAsset> assets = launchAssetRoster->getMultiSelected();


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

    launchProfileRoster->clear();

    launchProfileRoster->add(lp);
}


void Scrapyard::on_launchDeleteButton_clicked()
{
    auto sel = weaponRoster->getSelected();

    if (sel)
        launchProfileRoster->remove();
}


// going with approach of creating a new weapon and replacing the old one because of the shared_ptrs
void Scrapyard::on_saveButton_clicked()
{
    QFleet_Option newOpt(ui->nameEdit->text());

    QFleet_OptType type;

    if (ui->typeWeaponRadio->isChecked())
    {
        type = QFleet_OptType(optType::WEAPONS);

        newOpt.weaponVecPtr = std::make_shared<QVector<QFleet_Weapon>>();

        auto weapons = weaponRoster->getData();

        for (auto& element : weapons)
            newOpt.weaponVecPtr->push_back(element);
    }
    else if (ui->typeLaunchRadio->isChecked())
    {
        type = QFleet_OptType(optType::LAUNCH);

        newOpt.launchProfilePtr = std::make_shared<QFleet_launchProfile>("blank");

        auto lp = launchProfileRoster->getData().front();

        *(newOpt.launchProfilePtr) = lp;
    }
    else if (ui->typeStatRadio->isChecked())
    {this->done(QDialog::Accepted);
        type = QFleet_OptType(optType::STAT);

        newOpt.statTypePtr = std::make_shared<QFleet_StatID>();
        newOpt.statBonusPtr = std::make_shared<unsigned int>();

        if (ui->scanRadio->isChecked())
            *(newOpt.statTypePtr) = QFleet_StatID(statID::scan);
        else if (ui->thrustRadio->isChecked())
            *(newOpt.statTypePtr) = QFleet_StatID(statID::thrust);
        else if (ui->sigRadio->isChecked())
                *(newOpt.statTypePtr) = QFleet_StatID(statID::sig);
        else if (ui->hullRadio->isChecked())
            *(newOpt.statTypePtr) = QFleet_StatID(statID::hull);
        else if (ui->pdRadio->isChecked())
                *(newOpt.statTypePtr) = QFleet_StatID(statID::PD);
    }
    else if (ui->typeSpecialRadio->isChecked())
    {
        type = QFleet_OptType(optType::SPECIAL);

        newOpt.specialPtr =  std::make_shared<QString>();

        QString special = specialRoster->getData().front();

        *(newOpt.specialPtr) = special;
    }

    newOpt.type = type;
    newOpt.points = ui->pointSpin->value();

    newOpt.broadside = ui->broadsideCheck->isChecked();

    newOpt.oneOnly = ui->singleCheck->isChecked();

    *option = newOpt;

    this->done(QDialog::Accepted);
}


void Scrapyard::on_newWeaponButton_clicked()
{
    std::shared_ptr<QFleet_Weapon> newWeaponPtr = std::make_shared<QFleet_Weapon>("New Weapon");

    Arsenal * arsenalWindow = new Arsenal(this, newWeaponPtr);

    arsenalWindow->setAttribute(Qt::WA_DeleteOnClose);

    int r = arsenalWindow->exec();

    if (r == QDialog::Accepted)
        weaponRoster->add(*newWeaponPtr);

}


void Scrapyard::on_deleteWeaponButton_clicked()
{
    auto sel = weaponRoster->getSelected();

    if (sel)
        weaponRoster->remove();
}


void Scrapyard::on_editWeaponbutton_clicked()
{
    auto sel = weaponRoster->getSelected();
    if (sel)
    {
        weaponRoster->remove();

        std::shared_ptr<QFleet_Weapon> newWeaponPtr = std::make_shared<QFleet_Weapon>(*sel);

        Arsenal * arsenalWindow = new Arsenal(this, newWeaponPtr);

        arsenalWindow->setAttribute(Qt::WA_DeleteOnClose);

        int r = arsenalWindow->exec();

        if (r == QDialog::Accepted)
            weaponRoster->add(*newWeaponPtr);
        else
            weaponRoster->add(*sel);        

    }
}


void Scrapyard::on_CopyWeaponButton_clicked()
{
    auto sel = weaponRoster->getSelected();

    if (sel)
    {
        std::shared_ptr<QFleet_Weapon> clonedWeaponPtr = std::make_shared<QFleet_Weapon>(*sel);

        Arsenal * arsenalWindow = new Arsenal(this, clonedWeaponPtr);

        int r = arsenalWindow->exec();

        arsenalWindow->setAttribute(Qt::WA_DeleteOnClose);

        if (r == QDialog::Accepted)
            weaponRoster->add(*clonedWeaponPtr);


    }
}


void Scrapyard::on_specialAddButton_clicked()
{
    QString str = ui->specialSelectCombo->currentText();

    unsigned int num = ui->specialNumSpin->value();

    str = xrulesub(str,num);

    specialRoster->clear();

    specialRoster->add(str);
}


void Scrapyard::on_specialDeleteButton_clicked()
{
    auto sel = weaponRoster->getSelected();

    if (sel)
        specialRoster->remove();
}

