#ifndef QFLEET_WEAPON_H
#define QFLEET_WEAPON_H

#include "qfleet_arc.h"
#include "qfleet_lock.h"
#include "qft_component.h"

class QFleet_Weapon : public qft_component<QFleet_Weapon>
{
public:
    QFleet_Weapon(const QString, const QString);

    QFleet_Weapon(QJsonObject);

    inline void setLock(const QFleet_Lock& set)
    {
        lock = set;
    }

    inline void setArc(const QFleet_Arc& set)
    {
        facing = set;
    }

    inline void setDamage(const QString& set)
    {
        damage = set;
    }

    inline void setAttacks(const QString& set)
    {
        attacks = set;
    }

    inline void setSpecials(const QVector<QString>& set)
    {
        specials.clear();
        specials = set;
    }

    inline QFleet_Lock getLock() const
    {
        return lock;
    }

    inline QFleet_Arc getArc() const
    {
        return facing;
    }

    inline QString getDamage() const
    {
        return damage;
    }

    inline QString getAttacks() const
    {
        return attacks;
    }

    inline QVector<QString> getSpecials() const
    {
        return specials;
    }

protected:

    // VARS

    QFleet_Lock lock;
    QString attacks;
    QString damage;
    QFleet_Arc facing;
    QVector<QString> specials;

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
