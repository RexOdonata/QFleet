#include "qfleet_group.h"

const QString QFleet_Group::label="";
const QString QFleet_Group::field_cost="cost";
const QString QFleet_Group::field_ship="ship";
const QString QFleet_Group::field_number="number";
const QString QFleet_Group::field_admiralForced="admiralForced";
const QString QFleet_Group::field_admiralAllowed="admiralAllowed";
const QString QFleet_Group::field_admiralDiscount="admiralDiscount";
const QString QFleet_Group::field_admiralLevel="admiralLevel";


QFleet_Group::QFleet_Group(const QString setName) : qft_component<QFleet_Group>(setName), cost(QFleet_Cost("GroupCost"))
{

}

QFleet_Group::QFleet_Group(QJsonObject json) : qft_component<QFleet_Group>(json.value(field_name()).toString()), cost(QFleet_Cost("GroupCost"))
{
    fieldFromJson(json, field_cost, cost);
    fieldFromJson(json, field_ship, ship);
    fieldFromJson(json, field_number, number);
    fieldFromJson(json, field_admiralForced, admiralForced);
    fieldFromJson(json, field_admiralAllowed, admiralAllowed);
    fieldFromJson(json, field_admiralDiscount, admiralDiscount);
    fieldFromJson(json, field_admiralLevel, admiralLevel);
}

void QFleet_Group::impl_toJson(QJsonObject& json)
{
    fieldToJson(json, field_cost, cost);
    fieldToJson(json, field_ship, ship);
    fieldToJson(json, field_number, number);
    fieldToJson(json, field_admiralForced, admiralForced);
    fieldToJson(json, field_admiralAllowed, admiralAllowed);
    fieldToJson(json, field_admiralDiscount, admiralDiscount);
    fieldToJson(json, field_admiralLevel, admiralLevel);
}

void QFleet_Group::updateCost(const unsigned int set)
{
    number = set;

    QFleet_Cost tc("cost copy");

    for (int i=0; i<number; i++)
    {
        cost + tc;
    }

}
