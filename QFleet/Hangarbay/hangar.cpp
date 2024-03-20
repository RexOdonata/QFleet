#include "hangar.h"
#include "./ui_hangar.h"
#include "fileTypes.h"
#include "../Components/qfu_specialrules.h"

#include "windowUtils.h"

Hangar::Hangar(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Hangar),
    rosterWidget(new dvsx_Widget<QFleet_LaunchAsset>(parent)),
    specialWidget(new dvs_Widget<QString>(parent))
{
    ui->setupUi(this);


    {
        qfu_specialRules specialRules;

        for (auto& rule : specialRules.launchRules)
            ui->special_combo->addItem(rule);

    }

    {
        QFleet_Lock fxl;
        auto lockStrings = fxl.getEnumStrings();
        for (auto& lock : lockStrings)
            ui->lock_combo->addItem(lock);
    }

    ui->launchLayout->addWidget(rosterWidget);
    rosterWidget->setLabel("Launch");

    ui->specialLayout->addWidget(specialWidget);
    specialWidget->setLabel("Special Rules");
}

Hangar::~Hangar()
{
    delete ui;

    delete rosterWidget;

    delete specialWidget;
}

QFleet_LaunchAsset Hangar::saveLaunch()
{
    QString name = ui->name_edit->text();

    QFleet_LaunchAsset newAsset(name);

    newAsset.thrust = ui->thrust_spin->value();

    newAsset.attacks = ui->attack_spin->value();

    newAsset.lock = QFleet_Lock(ui->lock_combo->currentText());

    newAsset.damage = ui->damage_spin->value();

    newAsset.PD = ui->PD_spin->value();

    assetType launchType;
    if (ui->bomber_radio->isChecked())
        launchType = assetType::bomber;
    else if (ui->torpedo_radio->isChecked())
        launchType = assetType::torpedo;
    else if (ui->fighter_radio->isChecked())
        launchType = assetType::fighter;
    else if (ui->drop_radio->isChecked())
        launchType = assetType::drop;
    else
        // put error dialog here?
        return QFleet_LaunchAsset("missing");

    newAsset.type = launchType;

    if (launchType != assetType::drop)
        newAsset.launchCap = true;
    else
        newAsset.launchCap = false;

   QVector<QFleet_Faction> factions;
    if (ui->UCM_check->isChecked())
        factions.push_back(QFleet_Faction(faction::UCM));
    if (ui->PHR_check->isChecked())
        factions.push_back(QFleet_Faction(faction::PHR));
    if (ui->Resistance_check->isChecked())
        factions.push_back(QFleet_Faction(faction::RESISTANCE));
    if (ui->Scourge_check->isChecked())
        factions.push_back(QFleet_Faction(faction::SCOURGE));
    if (ui->shaltari_check->isChecked())
        factions.push_back(QFleet_Faction(faction::SHALTARI));

    newAsset.factions = factions;

    newAsset.special =specialWidget->getData();

    return newAsset;
}

void Hangar::on_saveWeapon_button_clicked()
{
    QFleet_LaunchAsset newLaunch = saveLaunch();

    rosterWidget->add(newLaunch);
}

void Hangar::on_loadWeapon_button_clicked()
{
    auto launch = rosterWidget->getSelected();    

    if (launch)
    {

        specialWidget->clear();

        ui->name_edit->clear();
        ui->name_edit->insert(launch->getName());

        auto launchValues = *launch;

        ui->thrust_spin->setValue((int)launchValues.thrust);

        ui->PD_spin->setValue((int)launchValues.PD);

        ui->attack_spin->setValue((int)launchValues.attacks);

        setComboBoxSelection(*(ui->lock_combo), launchValues.lock.toString());

        ui->damage_spin->setValue((int)launchValues.damage);

        if (launchValues.type.getVal() == assetType::bomber)
            ui->bomber_radio->setChecked(true);
        else if (launchValues.type.getVal() == assetType::fighter)
             ui->fighter_radio->setChecked(true);
        else if (launchValues.type.getVal() == assetType::torpedo)
            ui->torpedo_radio->setChecked(true);
        else if (launchValues.type.getVal() == assetType::drop)
             ui->drop_radio->setChecked(true);

        QMap<faction, Qt::CheckState> factionMap =
        {
            {faction::UCM, Qt::CheckState::Unchecked},
            {faction::PHR, Qt::CheckState::Unchecked},
            {faction::RESISTANCE, Qt::CheckState::Unchecked},
            {faction::SCOURGE, Qt::CheckState::Unchecked},
            {faction::SHALTARI, Qt::CheckState::Unchecked}
        };

       for (auto& faction : launchValues.factions)
       {
            factionMap[faction.getVal()] = Qt::CheckState::Checked;
       }

       ui->UCM_check->setCheckState(factionMap[faction::UCM]);
       ui->PHR_check->setCheckState(factionMap[faction::PHR]);
       ui->Resistance_check->setCheckState(factionMap[faction::RESISTANCE]);
       ui->Scourge_check->setCheckState(factionMap[faction::SCOURGE]);
       ui->shaltari_check->setCheckState(factionMap[faction::SHALTARI]);

       specialWidget->add(launchValues.special);

       setValidFields();
    }
}


void Hangar::on_deleteWeapon_button_clicked()
{
    rosterWidget->remove();
}


void Hangar::on_specialAdd_button_clicked()
{
    QString special = ui->special_combo->currentText();

    specialWidget->add(special);
}


void Hangar::on_specialRemove_button_clicked()
{
    specialWidget->clear();
}

void Hangar::setComboBoxSelection(QComboBox& box, QString item)
{
    int index = box.findText(item);

    if (index > 0)
        box.setCurrentIndex(index);

}


void Hangar::on_actionLoad_triggered()
{
    QVector<QFleet_LaunchAsset> data;

    loadVectorFromJsonFile(this, data, fileType_launchData());

    rosterWidget->add(data);
}


void Hangar::on_actionSave_triggered()
{
    auto data = rosterWidget->getData();
    saveVectorToJsonFile(this, data, fileType_launchData());
}


void Hangar::setValidFields()
{
    if (ui->bomber_radio->isChecked() || ui->torpedo_radio->isChecked())
    {
        ui->attack_spin->setEnabled(true);

        ui->damage_spin->setEnabled(true);

        ui->lock_combo->setEnabled(true);

        ui->PD_spin->setValue(0);
        ui->PD_spin->setEnabled(false);
    }
    else if (ui->fighter_radio->isChecked())
    {
        ui->attack_spin->setValue(0);
        ui->attack_spin->setEnabled(false);

        ui->damage_spin->setValue(0);
        ui->damage_spin->setEnabled(false);

        ui->lock_combo->setCurrentIndex(0);
        ui->lock_combo->setEnabled(false);

        ui->PD_spin->setEnabled(true);
    }
    else if (ui->drop_radio->isChecked())
    {
        ui->attack_spin->setValue(0);
        ui->attack_spin->setEnabled(false);

        ui->damage_spin->setValue(0);
        ui->damage_spin->setEnabled(false);

        ui->lock_combo->setCurrentIndex(0);
        ui->lock_combo->setEnabled(false);

        ui->PD_spin->setValue(0);
        ui->PD_spin->setEnabled(false);
    }

}

void Hangar::on_bomber_radio_clicked()
{
    setValidFields();
}


void Hangar::on_torpedo_radio_clicked()
{
    setValidFields();
}


void Hangar::on_fighter_radio_clicked()
{
    setValidFields();
}


void Hangar::on_drop_radio_clicked()
{
    setValidFields();
}

