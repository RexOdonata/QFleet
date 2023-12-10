#ifndef QFLEET_LIST_H
#define QFLEET_LIST_H

#include "qfleet_battlegroup.h"

#include "../Components/qft_component.h"
class QFleet_List : public qft_component<QFleet_List>
{
public:
    QFleet_List(QJsonObject);

    QFleet_List(const QString);

    void setPointsLimit(unsigned int);

    unsigned int getPointsLimit() const;

    QFleet_Cost getCost();

    void addCard(QFleet_BGT);

    void removeCard(QFleet_BGT);

    std::shared_ptr<QFleet_Battlegroup> getCard(unsigned int);

    bool checkLimits();

    void updateCost();

protected:

    void impl_toJson(QJsonObject&);


private:

    unsigned int pointsLimit;

    QFleet_Cost cost;

    unsigned int maxBattleGroups;

    unsigned int maxLC;

    QVector<std::shared_ptr<QFleet_Battlegroup>> cards;

    const static QString field_pointsLimit;
    const static QString field_cost;
    const static QString field_cards;

    const static std::array<unsigned int, 12> cardLimitMatrix;

    // allowed/actual
    unsigned int allowedL=0;
    unsigned int allowedM=0;
    unsigned int allowedH=0;
    unsigned int allowedSH=0;

    unsigned int countL=0;
    unsigned int countM=0;
    unsigned int countH=0;
    unsigned int countSH=0;

};

#endif // QFLEET_LIST_H
