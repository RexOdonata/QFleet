#ifndef QFLEET_LAUNCHASSET_H
#define QFLEET_LAUNCHASSET_H

#include "qft_component.h"

#include "qfleet_lock.h"
#include "qfleet_faction.h"
#include "qfleet_assettype.h"

class QFleet_LaunchAsset : public qft_component<QFleet_LaunchAsset>
{
    friend class qft_component<QFleet_LaunchAsset>;

public:
    QFleet_LaunchAsset(QJsonObject);

    QFleet_LaunchAsset(const QString setName, const QString setID);

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


};

#endif // QFLEET_LAUNCHASSET_H
