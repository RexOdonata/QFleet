#ifndef QFLEET_SHIP_FLEET_H
#define QFLEET_SHIP_FLEET_H

#include "qfleet_ship.h"


// this object is used to store actual ships existing in the fleet, linked to groups
class QFleet_Ship_Fleet : public QFleet_Ship<QFleet_Ship_Fleet>
{
    friend class QFleet_Ship<QFleet_Ship_Fleet>;

public:
    QFleet_Ship_Fleet(QJsonObject);

    QFleet_Ship_Fleet(const QString);

    // all options selected for this ship - this exists to preserve a little bit of info about the options
    QVector<QString> selectedOptions;


    QString getArmorString() const;

    QString getSigString() const;

    QString getGroupString() const;

    QString getSpecialString() const;

    // translates the desired admiral level to actual cost based on discount
    // returns no value on L ships
    std::optional<unsigned int> admiralCost(unsigned int);

protected:


    void impl_toJson(QJsonObject& json);


    const static QString label;
    const static QString field_selectedOptions;

};

#endif // QFLEET_SHIP_FLEET_H
