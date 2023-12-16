#ifndef QFU_SPECIALRULES_H
#define QFU_SPECIALRULES_H

#include <QString>
#include <QVector>

class qfu_specialRules
{
public:
    qfu_specialRules();

    const QVector<QString> weaponRules;
    const QVector<QString> shipRules;

    static QVector<QString> populateWeaponRules();
    static QVector<QString> populateShipRules();

};

#endif // QFU_SPECIALRULES_H
