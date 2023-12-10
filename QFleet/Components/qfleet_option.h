#ifndef QFLEET_OPTION_H
#define QFLEET_OPTION_H
#include <memory>

#include "qft_component.h"

#include "qfleet_weapon.h"
#include "qfleet_launchprofile.h"

class QFleet_Option : public qft_component<QFleet_Option>
{
    friend class qft_component<QFleet_Option>;

public:
    QFleet_Option(const QString);

    QFleet_Option(QJsonObject);

    // VARS
    // this are pts because they may or not be defined for a given option
    std::shared_ptr<QVector<QFleet_Weapon>> weaponPtr = NULL;
    std::shared_ptr<QFleet_launchProfile> launchProfilePtr = NULL;
    QString specialRule;
    unsigned int statBonus;

    bool broadside;
    bool oneOnly;

    unsigned int points;


private:





    // STRINGS

    const static QString label;
    const static QString field_weapons;
    const static QString field_launchProfile;
    const static QString field_specialRule;
    const static QString field_statBonus;
    const static QString field_broadside;
    const static QString field_oneOnly;

    // FX

    void impl_toJson(QJsonObject& json);



};

#endif // QFLEET_OPTION_H
