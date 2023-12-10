#ifndef QFLEET_GROUP_H
#define QFLEET_GROUP_H


#include "../Components/qft_component.h"
#include "qfleet_cost.h"
#include "../Components/qfleet_ship_fleet.h"

class QFleet_Group : public qft_component<QFleet_Group>
{
    friend class qft_component<QFleet_Group>;

public:
    QFleet_Group(QJsonObject);

    QFleet_Group(QFleet_Ship_Fleet, const QString);

    std::shared_ptr<QFleet_Ship_Fleet> ship = NULL;

    // admiral poss
    
    bool admiralForced = false;
    
    bool admiralAllowed;
    
    unsigned int admiralDiscount = 0;

    // admiral actual
    
    unsigned int admiralLevel = 0;

    // FXs

    void update();
    void updateCost(const unsigned int);
    unsigned int getNumber() const;
    QFleet_Cost getCost() const;
    
protected:

    QFleet_Cost cost;
    unsigned int number;

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
