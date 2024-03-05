#include "qfleet_list.h"


const QString QFleet_List::field_cards="cards";
const QString QFleet_List::field_cost="cost";
const QString QFleet_List::field_pointsLimit="pointsLimit";
const QString QFleet_List::field_faction="faction";



QFleet_List::QFleet_List(QJsonObject json) : qft_component<QFleet_List>(json.value(field_name).toString()), cost(QFleet_Cost("Cost"))
{
    fieldFromJson(json, field_faction, listFaction);
    fieldFromJson(json, field_cards, cards);
    fieldFromJson(json, field_pointsLimit, pointsLimit);
    fieldFromJson(json, field_cost, cost);


    updateCost();
}

QFleet_List::QFleet_List(const QString setName, QFleet_Faction setFaction, unsigned int setLimit) :
    qft_component<QFleet_List>(setName), cost(QFleet_Cost("listCost")),
    listFaction(setFaction), pointsLimit(setLimit)

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
        element.updateCost();
        nc + element.getCost();
    }

    cost = nc;
}

void QFleet_List::addCard(QFleet_Battlegroup& newCard)
{
    cards.push_back(newCard);
}



QVector<QFleet_Battlegroup> QFleet_List::getCards() const
{
    return cards;
}


unsigned int QFleet_List::getPointsLimit() const
{
    return pointsLimit;
}

unsigned int QFleet_List::getLaunchLimit() const
{
    if (pointsLimit < 1000)
    {
        return 10;
    }
    else if (pointsLimit < 2000)
    {
        return 15;
    }
    else if (pointsLimit < 3001)
    {
        return 20;
    }
    else
    {
        qFatal("List size too big!");
    }
}

faction QFleet_List::getFaction() const
{
    return listFaction.getVal();
}

QFleet_Cost QFleet_List::getCost() const
{
    return cost;
}

QString QFleet_List::getListString()
{
    QString nameStr = this->name;

    nameStr.append(", ");

    nameStr.append(QString::number(this->getCost().points));

    nameStr.append(" pts, ");

    nameStr.append(QFleet_Faction(this->getFaction()).toString());

    for (auto& card : cards)
    {

        QString cardStr = "\r\t";

        cardStr.append(card.getListString());

        nameStr.append(cardStr);


    }

        return nameStr;
}
