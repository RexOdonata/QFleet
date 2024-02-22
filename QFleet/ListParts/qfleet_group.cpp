#include "qfleet_group.h"

const QString QFleet_Group::label="";
const QString QFleet_Group::field_cost="cost";
const QString QFleet_Group::field_ship="ship";
const QString QFleet_Group::field_number="number";
const QString QFleet_Group::field_admiral="admiral";


QFleet_Group::QFleet_Group(const QFleet_Ship_Fleet& setShip, const unsigned int) :
    qft_component<QFleet_Group>(setShip.name), cost(QFleet_Cost("GroupCost")),
    ship(setShip), number(setShip.groupL)
{

}

QFleet_Group::QFleet_Group(QJsonObject json) :
    qft_component<QFleet_Group>(json.value(field_name).toString()), cost(QFleet_Cost("GroupCost")),
    ship(json.value(field_ship).toObject())
{
    fieldFromJson(json, field_cost, cost);
    fieldFromJson(json, field_number, number);
    fieldFromJson(json, field_admiral, admiral);


}

void QFleet_Group::impl_toJson(QJsonObject& json)
{
    fieldToJson(json, field_cost, cost);
    fieldToJson(json, field_ship, ship);
    fieldToJson(json, field_number, number);
    fieldToJson(json, field_admiral, admiral);
}


QFleet_Cost QFleet_Group::getCost() const
{
    return this->cost;
}

unsigned int QFleet_Group::getNumber() const
{
    return this->number;
}

unsigned int QFleet_Group::getAdmiral() const
{
    return admiral;
}

QFleet_Ship_Fleet QFleet_Group::getShip() const
{
    return ship;
}

void QFleet_Group::admiralAdjust()
{
    auto admiralPoints = ship.admiralCost(admiral);

    if (admiralPoints)
        cost.points +=  *admiralPoints;
}
