#ifndef QFLEET_WEAPON_H
#define QFLEET_WEAPON_H

#include "qfleet_lock.h"
#include "qfleet_arc.h"
#include "qft_component.h"

class QFleet_Weapon : public qft_component<QFleet_Weapon>
{

    friend class qft_component<QFleet_Weapon>;

public:
    QFleet_Weapon(const QString);

    QFleet_Weapon(QJsonObject);

    // VARS

    QFleet_Lock lock;
    QString attacks;
    QString damage;
    QFleet_Arc facing;
    QVector<QString> specials;

protected:


    // STRINGS

    const static QString field_lock;
    const static QString field_attacks;
    const static QString field_damage;
    const static QString field_facing;
    const static QString field_arc;
    const static QString field_specials;
    const static QString label;

    // FX

    void impl_toJson(QJsonObject& json);

};

#endif // QFLEET_WEAPON_H
