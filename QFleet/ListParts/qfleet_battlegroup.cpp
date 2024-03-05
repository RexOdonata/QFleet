#include "qfleet_battlegroup.h"

const QString QFleet_Battlegroup::label="Battlegroup";
const QString QFleet_Battlegroup::field_groups="groups";
const QString QFleet_Battlegroup::field_cost="cost";
const QString QFleet_Battlegroup::field_type="type";

QFleet_Battlegroup::QFleet_Battlegroup(QJsonObject in) :
    qft_component<QFleet_Battlegroup>(in.value(field_name).toString()),
    type(in[field_type].toObject()),
    cost(in[field_cost].toObject())
{
    fieldFromJson(in, field_groups, groups);
    fieldFromJson(in, field_cost, cost);
    fieldFromJson(in, field_type, type);

    updateCost();
}


QFleet_Battlegroup::QFleet_Battlegroup(QString setName, QFleet_BGT type) : qft_component<QFleet_Battlegroup>(setName),
    type(type),
    cost(QFleet_Cost("battlegroupCost"))
{
    // creating an empty group
}

void QFleet_Battlegroup::impl_toJson(QJsonObject& json)
{
    fieldToJson(json, field_groups, groups);
    fieldToJson(json, field_cost, cost);
    fieldToJson(json, field_type, type);
}

QVector<QFleet_Group> QFleet_Battlegroup::getGroups() const
{
    return groups;
}

void QFleet_Battlegroup::updateCost()
{
    this->cost.zero();

    // sum costs of battlegroups
    for (auto groupPtr : groups)
    {
        cost + groupPtr.getCost();
    }
}

QFleet_Cost QFleet_Battlegroup::getCost() const
{
    return this->cost;
}

void QFleet_Battlegroup::addGroup(const QFleet_Group& newGroup)
{
    groups.push_back(newGroup);
}

QFleet_BGT QFleet_Battlegroup::getType() const
{
    return type;
}

QString QFleet_Battlegroup::getListString()
{
    QString nameStr = this->name;

    nameStr.append(", ");

    nameStr.append(QString::number(this->cost.SR));

    nameStr.append(" SR");

    for (auto& group : groups)
    {
        QString groupStr = "\r\t\t";

        groupStr.append(group.getListString());

        nameStr.append(groupStr);
    }

    return nameStr;
}
