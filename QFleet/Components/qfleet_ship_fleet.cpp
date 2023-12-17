#include "qfleet_ship_fleet.h"

const QString  QFleet_Ship_Fleet::label="Ship.fleet";
const QString  QFleet_Ship_Fleet::field_selectedOptions="selectedOptions";


QFleet_Ship_Fleet::QFleet_Ship_Fleet(QJsonObject in) : QFleet_Ship(in)
{
    fieldToJson(in, field_selectedOptions, selectedOptions);
}

QFleet_Ship_Fleet::QFleet_Ship_Fleet (const QString setName) : QFleet_Ship(setName)
{

}

void QFleet_Ship_Fleet::impl_toJson(QJsonObject& in)
{
    fieldFromJson(in, field_selectedOptions, selectedOptions);
}
