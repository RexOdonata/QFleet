#ifndef QFLEET_SHIP_SHIPYARD_H
#define QFLEET_SHIP_SHIPYARD_H

#include "qfleet_ship.h"
#include "qfleet_option.h"
#include "qfleet_faction.h"

class QFleet_Ship_Shipyard : public QFleet_Ship
{
public:
    QFleet_Ship_Shipyard(QJsonObject);

    QFleet_Ship_Shipyard(const QString, const QString);

    // VARS

    unsigned int admiralDiscount;

    bool admiralForced;

    bool admiralAllowed;

    // all options available to the ship
    QVector<QFleet_Option> options;

    QVector<QFleet_Faction> factions;


protected:


    void impl_toJson(QJsonObject& json);

    const static QString label;
    const static QString field_admiralDiscount;
    const static QString field_admiralForced;
    const static QString field_admiralAllowed;
    const static QString field_options;

};

#endif // QFLEET_SHIP_SHIPYARD_H
