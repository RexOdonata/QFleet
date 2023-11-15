#include "QFleet_Faction.h"

const QString QFleet_Faction::label = "faction";
const QString QFleet_Faction::val_ucm = "ucm";
const QString QFleet_Faction::val_scourge = "scourge";
const QString QFleet_Faction::val_phr = "phr";
const QString QFleet_Faction::val_shaltari = "shaltari";
const QString QFleet_Faction::val_resistance = "resistance";


const QMap<QString, faction> QFleet_Faction::s2e =
{
    {val_ucm,faction::UCM},
    {val_scourge,faction::SCOURGE},
    {val_phr,faction::PHR},
    {val_shaltari,faction::SHALTARI},
    {val_resistance, faction::RESISTANCE}
};

const QMap<faction, QString> QFleet_Faction::e2s =
{
        {faction::UCM, val_ucm},
        {faction::SCOURGE, val_scourge},
        {faction::PHR, val_phr},
        {faction::SHALTARI, val_shaltari},
        {faction::RESISTANCE, val_resistance}
};
