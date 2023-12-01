#ifndef QFLEET_BATTLEGROUP_H
#define QFLEET_BATTLEGROUP_H

#include "../Components/qft_component.h"
#include "qfleet_group.h"

class QFleet_Battlegroup : public qft_component<QFleet_Battlegroup>
{
    friend class qft_component<QFleet_Battlegroup>;

public:
    QFleet_Battlegroup(QJsonObject);

    QFleet_Battlegroup(const QString);

    std::shared_ptr<QFleet_Group> g1;
    std::shared_ptr<QFleet_Group> g2;
    std::shared_ptr<QFleet_Group> g3;

    QFleet_Cost cost;

    void updateCost();

protected:

    void impl_toJson(QJsonObject&);


};

#endif // QFLEET_BATTLEGROUP_H
