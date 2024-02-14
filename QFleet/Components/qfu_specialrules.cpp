#include "qfu_specialrules.h"

qfu_specialRules::qfu_specialRules() :
    weaponRules(populateWeaponRules()), shipRules(populateShipRules())
{

}

QVector<QString> qfu_specialRules::populateWeaponRules()
{
    return QVector<QString>
    {"Air to Air",
    "Alt-X",
    "Bloom",
    "Bombardment",
    "Burnthrough-X",
    "Caliber-L",
    "Caliber-HS",
    "Close Action",
    "Close Action(Swarmer)",
    "Close Action(Beam)",
    "Corruptor",
    "Crippling",
    "Distortion",
    "Escape Velocity",
    "Flash",
    "Fusillade-X",
    "Impel-X",
    "Limited-X",
    "Linked-X",
    "Low Power",
    "Mauler",
    "Overcharge",
    "Particle",
    "Re-Entry",
    "Scald",
    "Squadron-X",
    "Subsystem Network",
    "Unstable"};
};

QVector<QString> qfu_specialRules::populateShipRules()
{
    return QVector<QString>
    {"Ablative Armor",
    "Aegis-X",
    "Atmospheric",
    "Beast",
    "Detector",
    "Dreadnought",
    "Full-Cloak",
    "Launch",
    "Monitor",
    "Open",
    "Outlier",
    "Partial Cloak",
    "Rare",
    "Reinforced Armor",
    "Regenerate-X",
    "Stealth",
    "Vectored"};
};

