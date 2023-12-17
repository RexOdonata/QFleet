#include "qfleet_battlegroup.h"

const QString QFleet_Battlegroup::label="Battlegroup";
const QString QFleet_Battlegroup::field_groups="groups";
const QString QFleet_Battlegroup::field_cost="cost";
const QString QFleet_Battlegroup::field_type="type";

const std::array<unsigned int, 16> QFleet_Battlegroup::groupLimitMatrix =
{
    3,1,0,0,
    2,3,0,0,
    1,1,2,0,
    1,0,0,2
};

QFleet_Battlegroup::QFleet_Battlegroup(QJsonObject in) :
    qft_component<QFleet_Battlegroup>(in.value(field_name).toString()),
    type(in[field_type].toObject()),
    cost(in[field_cost].toObject())
{
    fieldFromJson(in, field_groups, groups);
    fieldFromJson(in, field_cost, cost);
    fieldFromJson(in, field_type, type);

    updateCost();

    //does a wasteful reassignment but whatev, it implements the functionality for setting limits
    setType(type);

}


QFleet_Battlegroup::QFleet_Battlegroup(QString setName) : qft_component<QFleet_Battlegroup>(setName),
    type(QFleet_BGT()),
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

void QFleet_Battlegroup::updateCost()
{
    this->cost.zero();

    // sum costs of battlegroups
    for (auto groupPtr : groups)
    {
        cost + groupPtr->getCost();
    }

    for (auto group : groups)
    {
        tonnage groupType = group->ship->tonnage.getVal();

        if (groupType == tonnage::L || groupType == tonnage::L2)
            countL++;
        else if (groupType == tonnage::M)
            countM++;
        if (groupType == tonnage::H)
            countH++;
        if (groupType == tonnage::S || groupType == tonnage::S2)
            countSH++;
    }

}

void QFleet_Battlegroup::setType(QFleet_BGT setType)
{
    type = setType;

    bgt typeEnum = type.getVal();

    unsigned int index = 0;

    if (typeEnum==bgt::LN)
    {
        index = 1;
    }
    else if (typeEnum == bgt::VG)
    {
        index = 2;
    }
    else if (typeEnum == bgt::FL)
    {
        index = 3;
    }

    allowedL = groupLimitMatrix[4*index];
    allowedM = groupLimitMatrix[4*index + 1];
    allowedH = groupLimitMatrix[4*index + 2];
    allowedSH = groupLimitMatrix[4*index + 3];
}

QFleet_Cost QFleet_Battlegroup::getCost() const
{
    return this->cost;
}

// checks to see if it is possible to add the battlegroup based on current limits
bool QFleet_Battlegroup::canAdd(QFleet_BGT gt)
{
    bgt typeEnum = type.getVal();

    unsigned int index = 0;

    if (typeEnum==bgt::PF)
    {
        index = 0;
    }
    else if (typeEnum==bgt::LN)
    {
        index = 1;
    }
    else if (typeEnum == bgt::VG)
    {
        index = 2;
    }
    else if (typeEnum == bgt::FL)
    {
        index = 3;
    }

    std::array<unsigned int, 4> actual{countL, countM, countH, countSH};
    std::array<unsigned int, 4> limits{allowedL, allowedM, allowedH, allowedSH};

    if (actual[index]+1>=limits[index])
        return false;
    else
        return true;
}

bool QFleet_Battlegroup::checkMandatory()
{

    bgt typeEnum = type.getVal();

    unsigned int index = 0;

    if (typeEnum==bgt::LN)
    {
        index = 1;
    }
    else if (typeEnum == bgt::VG)
    {
        index = 2;
    }
    else if (typeEnum == bgt::FL)
    {
        index = 3;
    }

    std::array<unsigned int, 4> actual{countL, countM, countH, countSH};

    if (actual[index]>0)
        return true;
    else
        return false;

}

bool QFleet_Battlegroup::removeGroup(unsigned int index)
{
    // make sure the index entered is actually valid
    if (index < groups.size())
    {

        bool hasAdmiral = groups[index]->admiralLevel > 0;
        tonnage groupType = groups[index]->ship->tonnage.getVal();


        if (groupType == tonnage::L || groupType == tonnage::L2)
            countL--;
        else if (groupType == tonnage::M)
            countM--;
        if (groupType == tonnage::H)
            countH--;
        if (groupType == tonnage::S || groupType == tonnage::S2)
            countSH--;

        groups.remove(index);

        return hasAdmiral;
    }
    else
        return false;
}

void QFleet_Battlegroup::addGroup(QFleet_Group newGroup)
{

    tonnage groupType = newGroup.ship->tonnage.getVal();

    QFleet_BGT shipBGT;

    if (groupType == tonnage::L || groupType == tonnage::L2)
        shipBGT = QFleet_BGT(bgt::PF);
    else if (groupType == tonnage::M)
        shipBGT = QFleet_BGT(bgt::LN);
    if (groupType == tonnage::H)
        shipBGT = QFleet_BGT(bgt::VG);
    if (groupType == tonnage::S || groupType == tonnage::S2)
        shipBGT = QFleet_BGT(bgt::FL);

    if (canAdd(shipBGT))
    {
        std::shared_ptr<QFleet_Group> newPtr = std::make_shared<QFleet_Group>(newGroup);
        groups.push_back(newPtr);
    }
}

QFleet_BGT QFleet_Battlegroup::getType() const
{
    return type;
}
