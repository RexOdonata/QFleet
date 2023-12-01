#ifndef QFLEET_GROUP_H
#define QFLEET_GROUP_H


#include "../Components/qft_component.h"
#include "qfleet_cost.h"
#include "../Components/qfleet_ship_fleet.h"

class QFleet_Group : public qft_component<QFleet_Group>
{
public:
    QFleet_Group(QJsonObject);

    QFleet_Group(const QString);
    
    QFleet_Cost cost;
    
    std::shared_ptr<QFleet_Ship_Fleet> ship = NULL;
    
    unsigned int number;

    // admiral poss
    
    bool admiralForced;
    
    bool admiralAllowed;
    
    unsigned int admiralDiscount;

    // admiral actual
    
    unsigned int admiralLevel;

    // FXs

    void updateCost(const unsigned int);
    
protected:

    const static QString label;
    const static QString field_cost;
    const static QString field_ship;
    const static QString field_number;
    const static QString field_admiralForced;
    const static QString field_admiralAllowed;
    const static QString field_admiralDiscount;
    const static QString field_admiralLevel;

    void impl_toJson(QJsonObject&);
};

#endif // QFLEET_GROUP_H
