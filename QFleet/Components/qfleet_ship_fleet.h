#ifndef QFLEET_SHIP_FLEET_H
#define QFLEET_SHIP_FLEET_H

#include "qfleet_ship.h"
#include "qfleet_option.h"


class QFleet_Ship_Fleet : public QFleet_Ship<QFleet_Ship_Fleet>
{
    friend class QFleet_Ship<QFleet_Ship_Fleet>;

public:
    QFleet_Ship_Fleet(QJsonObject);

    QFleet_Ship_Fleet(const QString);

    // all options available to the ship
    QVector<QFleet_Option> selectedOptions;

protected:


    void impl_toJson(QJsonObject& json);


    const static QString label;
    const static QString field_selectedOptions;

};

#endif // QFLEET_SHIP_FLEET_H
