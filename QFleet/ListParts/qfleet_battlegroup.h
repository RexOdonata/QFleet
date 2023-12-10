#ifndef QFLEET_BATTLEGROUP_H
#define QFLEET_BATTLEGROUP_H

#include "../Components/qft_component.h"
#include "../Components/qfleet_bgt.h"
#include "qfleet_group.h"

class QFleet_Battlegroup : public qft_component<QFleet_Battlegroup>
{
    friend class qft_component<QFleet_Battlegroup>;

public:
    QFleet_Battlegroup(QJsonObject);

    QFleet_Battlegroup(const QString);


   
    // FXS

    void updateCost();

    QFleet_Cost getCost() const;

    // sets constraints based on battlegroup type
    void setType(QFleet_BGT);

    bool canAdd(QFleet_BGT);

    // adds a ship to the group
    void addGroup(QFleet_Group);

    // removes a ship, returns if the removed ship has an admiral
    bool removeGroup(unsigned int);

    // checks if the BG contains a group of type mandory for it
    bool checkMandatory();

    QFleet_BGT getType() const;

protected:

    QFleet_BGT type;
    QFleet_Cost cost;

    QVector<std::shared_ptr<QFleet_Group>> groups;

    void impl_toJson(QJsonObject&);

    unsigned int allowedL=0;
    unsigned int allowedM=0;
    unsigned int allowedH=0;
    unsigned int allowedSH=0;

    unsigned int countL=0;
    unsigned int countM=0;
    unsigned int countH=0;
    unsigned int countSH=0;

    const static QString label;


    const static QString field_groups;
    const static QString field_cost;
    const static QString field_type;

    const static std::array<unsigned int, 16> groupLimitMatrix;


};

#endif // QFLEET_BATTLEGROUP_H
