#include "arsenal.h"
#include "ui_arsenal.h"
#include "../Components/qfu_specialrules.h"
#include "../Components/qfu_xrulesub.h"

Arsenal::Arsenal(QWidget *parent, std::shared_ptr<QFleet_Weapon> weaponPtr) :
    QDialog(parent),
    ui(new Ui::Arsenal), weapon(weaponPtr),
    specialWidget(std::make_shared<dvs_Widget>(parent))
{
    ui->setupUi(this);
    {
        qfu_specialRules specialRules;

        for (auto& rule : specialRules.weaponRules)
            ui->specialSelectCombo->addItem(rule);

    }

    // create the special rules container
    ui->specialRulesLayout->addWidget(specialWidget.get());
    specialRoster = std::make_shared<dvs_Data<QString, dvs_Widget>>(specialWidget.get());
    specialWidget->setLabel("Special Rules");

    // add random attack dice options
    ui->randomAttacksCombo->addItem("-");
    ui->randomAttacksCombo->addItem("xD3");
    ui->randomAttacksCombo->addItem("xD6");


    // add lock options to combo
    QFleet_Lock lock;
    QVector<QString> lockStrs = lock.getEnumStrings();

    for (auto& str : lockStrs)
    {
        ui->lockCombo->addItem(str);
    }

    QFleet_Arc arc;
    QVector<QString> arcStrs = arc.getEnumStrings();

    for (auto& str : arcStrs)
    {
        ui->arcCombo->addItem(str);
    }

    // LOAD CURRENT WEAPON VALUES
    if (weapon)
    {

        ui->nameEdit->setText(weapon->getName());

        // ATTACK

        auto tokens = weapon->attacks.split("+");

        if (tokens.size() > 1)
        {
            ui->attackSpin->setValue(tokens[1].toInt());

            auto tok2 = tokens[0].split("x");
            ui->randomAttacksCombo->setCurrentText(tok2[1]);
            ui->randomAttacksCombo->setCurrentText(tok2[0]);
        }
        else
        {
            ui->attackSpin->setValue(weapon->attacks.toInt());
            ui->randomAttacksCombo->setCurrentText("-");
            ui->randomAttackDice->setValue(0);
        }

        // DAMAGE
        if (weapon->damage=="X")
            ui->variableDamageCheck->setCheckState(Qt::Checked);
        else
        {
            ui->variableDamageCheck->setCheckState(Qt::Unchecked);
            ui->damageSpin->setValue(weapon->damage.toInt());
        }

        // FACING
        ui->arcCombo->setCurrentText(weapon->facing.toString());

        // LOCK
        ui->lockCombo->setCurrentText(weapon->lock.toString());

        // SPECIAL
        specialRoster->clear();

        specialRoster->add(weapon->specials);
    }
}

Arsenal::~Arsenal()
{
    delete ui;
}

void Arsenal::on_addSpecialButton_clicked()
{
    QString str = ui->specialSelectCombo->currentText();
    unsigned int num = ui->specialNumSpin->value();

    str = xrulesub(str, num);

    specialRoster->add(str);
}


void Arsenal::on_deleteSpecialButton_clicked()
{
    specialRoster->remove();
}


void Arsenal::on_saveButton_clicked()
{

    weapon->name = ui->nameEdit->text();

    // ATTACK
    QString attacksBase = QString::number(ui->attackSpin->value());

    QString attacksRng = ui->randomAttacksCombo->currentText();

    QString randomDice = QString::number(ui->randomAttackDice->value());

    QString attack;

    if (attacksRng != "-")
    {
        attacksRng.replace("-",randomDice);
        attack.append(attacksRng);
        attack.append("+");
    }

    attack.append(attacksBase);

    weapon->attacks = attack;

    // DAMAGE

    if (ui->variableDamageCheck->isChecked())
        weapon->damage = "X";
    else
        weapon->damage = QString::number(ui->damageSpin->value());

    // Lock

    QFleet_Lock lock(ui->lockCombo->currentText());

    weapon->lock = lock;

    // FACING

    QFleet_Arc arc(ui->arcCombo->currentText());

    weapon->facing = arc;

    // SPECIAL

    weapon->specials = specialRoster->getData();

    done(QDialog::Accepted);   

}

