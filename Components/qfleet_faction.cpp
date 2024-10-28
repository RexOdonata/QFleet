#include "qfleet_faction.h"


const QString QFleet_Faction::val_ucm = "UCM";
const QString QFleet_Faction::val_scourge = "Scourge";
const QString QFleet_Faction::val_phr = "PHR";
const QString QFleet_Faction::val_shaltari = "Shaltari";
const QString QFleet_Faction::val_resistance = "Resistance";
const QString QFleet_Faction::val_bioficer = "Bioficer";
const QString QFleet_Faction::val_custom = "Custom";


const QHash<QString, faction> QFleet_Faction::s2e =
{
    {val_ucm,faction::UCM},
    {val_scourge,faction::SCOURGE},
    {val_phr,faction::PHR},
    {val_shaltari,faction::SHALTARI},
    {val_resistance, faction::RESISTANCE},
    {val_bioficer, faction::BIOFICERS},
    {val_custom, faction::CUSTOM}
};

const QHash<faction, QString> QFleet_Faction::e2s =
{
        {faction::UCM, val_ucm},
        {faction::SCOURGE, val_scourge},
        {faction::PHR, val_phr},
        {faction::SHALTARI, val_shaltari},
        {faction::RESISTANCE, val_resistance},
        {faction::BIOFICERS, val_bioficer},
        {faction::CUSTOM, val_custom}
};
