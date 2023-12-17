#include "qfleet_ship_shipyard.h"

const QString QFleet_Ship_Shipyard::field_admiralAllowed="Admiral.allowed";
const QString QFleet_Ship_Shipyard::field_admiralDiscount="Admiral.discount";
const QString QFleet_Ship_Shipyard::field_admiralForced="Admiral.forced";
const QString QFleet_Ship_Shipyard::field_factions="factions";
const QString QFleet_Ship_Shipyard::field_options="options";
const QString QFleet_Ship_Shipyard::field_maxOptions="maxOptions";
const QString QFleet_Ship_Shipyard::field_minOptions="minOptions";
const QString QFleet_Ship_Shipyard::field_maxBroadsides="maxBroadsides";

const QString QFleet_Ship_Shipyard::label="Ship.shipyard";

QFleet_Ship_Shipyard::QFleet_Ship_Shipyard (const QString setName) : QFleet_Ship(setName)
{

}

QFleet_Ship_Shipyard::QFleet_Ship_Shipyard () : QFleet_Ship("newShip")
{

}

QFleet_Ship_Shipyard::QFleet_Ship_Shipyard(QJsonObject in) : QFleet_Ship(in)
{

    fieldFromJson(in, field_admiralDiscount, admiralDiscount);

    fieldFromJson(in, field_factions, factions);
    fieldFromJson(in, field_options, options);

    fieldFromJson(in,field_maxOptions,maxOptions);
    fieldFromJson(in,field_minOptions,minOptions);
    fieldFromJson(in,field_maxBroadsides,maxBroadsides);
}

void QFleet_Ship_Shipyard::impl_toJson(QJsonObject& in)
{

    fieldToJson(in, field_admiralDiscount, admiralDiscount);

    fieldToJson(in, field_factions, factions);
    fieldToJson(in, field_options, options);

    fieldToJson(in, field_maxOptions, maxOptions);
    fieldToJson(in, field_minOptions, minOptions);
    fieldToJson(in, field_maxBroadsides, maxBroadsides);
}
