#ifndef QFLEET_LAUNCHASSET_H
#define QFLEET_LAUNCHASSET_H

#include "qft_component.h"

#include "qfleet_lock.h"
#include "qfleet_faction.h"
#include "qfleet_assettype.h"

// represents the rules attached to a launch asset
class QFleet_LaunchAsset : public qft_component<QFleet_LaunchAsset>
{
    friend class qft_component<QFleet_LaunchAsset>;

public:
    QFleet_LaunchAsset(QJsonObject);

    QFleet_LaunchAsset(const QString setName);

    bool strikecraft;

    bool launchCap;

    unsigned int thrust;

    unsigned int PD;

    unsigned int attacks;

    unsigned int damage;

    QFleet_Lock lock;

    QVector<QString> special;

    QVector<QFleet_Faction> factions;

    QFleet_AssetType type;



protected:

    void impl_toJson(QJsonObject&);

    const static QString field_strikecraft;
    const static QString field_launchcap;
    const static QString field_thrust;
    const static QString field_PD;
    const static QString field_attacks;
    const static QString field_damage;
    const static QString field_lock;
    const static QString field_special;
    const static QString field_factions;
    const static QString field_type;

};

#endif // QFLEET_LAUNCHASSET_H
