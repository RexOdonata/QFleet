#include "qfleet_list.h"


const QString QFleet_List::field_cards="cards";
const QString QFleet_List::field_cost="cost";
const QString QFleet_List::field_pointsLimit="pointsLimit";
const QString QFleet_List::field_faction="faction";

const std::array<unsigned int, 12> QFleet_List::cardLimitMatrix =
{
    2,2,1,0,
    2,3,2,1,
    3,4,3,2
};

QFleet_List::QFleet_List(QJsonObject json) : qft_component<QFleet_List>(json.value(field_name).toString()), cost(QFleet_Cost("Cost"))
{
    fieldFromJson(json, field_faction, listFaction);
    fieldFromJson(json, field_cards, cards);
    fieldFromJson(json, field_pointsLimit, pointsLimit);
    fieldFromJson(json, field_cost, cost);

    setPointsLimit(pointsLimit);
    updateCost();
}

QFleet_List::QFleet_List(const QString setName) : qft_component<QFleet_List>(setName), cost(QFleet_Cost("listCost"))
{
}

void QFleet_List::impl_toJson(QJsonObject& json)
{
    fieldToJson(json, field_faction, listFaction);
    fieldToJson(json, field_cards, cards);
    fieldToJson(json, field_pointsLimit, pointsLimit);
    fieldToJson(json, field_cost, cost);
}

// updates cost and included groups
void QFleet_List::updateCost()
{
    QFleet_Cost nc("nc");

    for (auto& element : cards)
    {
        element->updateCost();
        nc + element->getCost();

        bgt type = element->getType().getVal();

        if (type == bgt::PF)
            countL++;
        else if (type == bgt::LN)
            countM++;
        else if (type == bgt::VG)
            countH++;
        else if (type == bgt::FL)
            countSH++;
    }

    cost = nc;
}

void QFleet_List::addCard(QFleet_BGT newT)
{
    bgt type = newT.getVal();

    unsigned int index = 0;

    if (type == bgt::PF)
        countL++;
    else if (type == bgt::LN)
        countM++;
    else if (type == bgt::VG)
        countH++;
    else if (type == bgt::FL)
        countSH++;

}

void QFleet_List::removeCard(QFleet_BGT oldT)
{
    bgt type = oldT.getVal();

    unsigned int index = 0;

    if (type == bgt::PF)
        countL--;
    else if (type == bgt::LN)
        countM--;
    else if (type == bgt::VG)
        countH--;
    else if (type == bgt::FL)
        countSH--;

}

// should this call update cost or not?
bool QFleet_List::checkLimits()
{
    if (cost.points > pointsLimit)
        return false;
    else if (cost.LC > maxLC)
        return false;
    else if (cards.size() > maxBattleGroups)
        return false;
    else if (countL > allowedL || countM > allowedM || countH > allowedH || countSH > allowedSH)
        return false;
    else return true;

}

void QFleet_List::setPointsLimit(unsigned int newLimit)
{
    pointsLimit = newLimit;

    unsigned int index = 0;

    if (pointsLimit < 999)
    {
        maxBattleGroups = 4;
        maxLC=10;

    }
    else if (pointsLimit < 1999)
    {
        maxBattleGroups = 6;
        maxLC=15;
        index=1;
    }
    else if (pointsLimit < 3999)
    {
        maxBattleGroups = 7;
        maxLC=20;
        index=2;
    }

    allowedL=cardLimitMatrix[4*index];
    allowedM=cardLimitMatrix[4*index + 1];
    allowedH=cardLimitMatrix[4*index + 2];
    allowedSH=cardLimitMatrix[4*index + 3];
}

std::shared_ptr<QFleet_Battlegroup> QFleet_List::getCard(unsigned int index)
{
    if (index<cards.size())
        return cards[index];
    else
    {
        qFatal("Out of bounds card request");
        return NULL;
    }
}


unsigned int QFleet_List::getPointsLimit() const
{
    return pointsLimit;
}

unsigned int QFleet_List::getLaunchLimit() const
{
    return maxLC;
}

void QFleet_List::setFaction(faction setFaction)
{
    listFaction = QFleet_Faction(setFaction);
}

faction QFleet_List::getFaction() const
{
    return listFaction.getVal();
}

QFleet_Cost QFleet_List::getCost()
{
    return cost;
}
