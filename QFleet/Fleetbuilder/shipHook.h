#ifndef SHIPHOOK_H
#define SHIPHOOK_H

#include "../Components/qfleet_ship_fleet.h"

struct shipHook
{
    QFleet_Ship_Fleet ship;
    bool valid;

    shipHook() : ship(QFleet_Ship_Fleet("Blank Ship")), valid(false)
    {

    }
};

#endif // SHIPHOOK_H
