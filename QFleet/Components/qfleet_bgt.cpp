#include "qfleet_bgt.h"

const QString QFleet_BGT::label="battlegroupType";

const QString QFleet_BGT::val_PF="PF";
const QString QFleet_BGT::val_LN="LN";
const QString QFleet_BGT::val_VG="VG";
const QString QFleet_BGT::val_FL="FL";

const QMap<bgt, QString> QFleet_BGT::e2s =
{
    {bgt::PF,val_PF},
    {bgt::LN,val_LN},
    {bgt::VG,val_VG},
    {bgt::FL,val_FL}
};

const QMap<QString, bgt> QFleet_BGT::s2e =
    {
        {val_PF, bgt::PF},
        {val_LN, bgt::LN},
        {val_VG, bgt::VG},
        {val_FL, bgt::FL}
};
