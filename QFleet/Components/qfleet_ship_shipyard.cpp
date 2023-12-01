#include "qfleet_ship_shipyard.h"

const QString QFleet_Ship_Shipyard::field_admiralAllowed="Admiral.allowed";
const QString QFleet_Ship_Shipyard::field_admiralDiscount="Admiral.discount";
const QString QFleet_Ship_Shipyard::field_admiralForced="Admiral.forced";
const QString QFleet_Ship_Shipyard::field_factions="factions";
const QString QFleet_Ship_Shipyard::field_options="options";
const QString QFleet_Ship_Shipyard::label="Ship.shipyard";

QFleet_Ship_Shipyard::QFleet_Ship_Shipyard (const QString setName) : QFleet_Ship(setName)
{

}

QFleet_Ship_Shipyard::QFleet_Ship_Shipyard(QJsonObject in) : QFleet_Ship(in)
{
    fieldFromJson(in, field_admiralAllowed, admiralAllowed);
    fieldFromJson(in, field_admiralDiscount, admiralDiscount);
    fieldFromJson(in, field_admiralForced, admiralForced);

    fieldFromJson(in, field_factions, factions);
    fieldFromJson(in, field_options, options);
}

void QFleet_Ship_Shipyard::impl_toJson(QJsonObject& in)
{
    this->ShipToJson(in);

    fieldToJson(in, field_admiralAllowed, admiralAllowed);
    fieldToJson(in, field_admiralDiscount, admiralDiscount);
    fieldToJson(in, field_admiralForced,admiralForced);

    fieldToJson(in, field_factions, factions);
    fieldToJson(in, field_options, options);
}
