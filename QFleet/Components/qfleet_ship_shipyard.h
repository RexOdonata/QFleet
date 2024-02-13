#ifndef QFLEET_SHIP_SHIPYARD_H
#define QFLEET_SHIP_SHIPYARD_H

#include "qfleet_ship.h"
#include "qfleet_option.h"
#include "qfleet_faction.h"
#include "qft_component.h"

// output of shipyard, used to load details in fleet builder
class QFleet_Ship_Shipyard : public QFleet_Ship<QFleet_Ship_Shipyard>
{
    friend class QFleet_Ship<QFleet_Ship_Shipyard>;

public:
    QFleet_Ship_Shipyard(QJsonObject);

    QFleet_Ship_Shipyard(const QString);

    QFleet_Ship_Shipyard();

    // all options available to the ship
    QVector<QFleet_Option> options;

    // all factions the ship is available in
    QVector<QFleet_Faction> factions;

    unsigned int maxOptions;
    unsigned int minOptions;
    unsigned int maxBroadsides;


protected:


    void impl_toJson(QJsonObject& json);

    const static QString label;
    const static QString field_admiralDiscount;

    const static QString field_options;
    const static QString field_factions;

    const static QString field_maxOptions;
    const static QString field_minOptions;
    const static QString field_maxBroadsides;


};

#endif // QFLEET_SHIP_SHIPYARD_H
