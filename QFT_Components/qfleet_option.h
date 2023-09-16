#ifndef QFLEET_OPTION_H
#define QFLEET_OPTION_H

#include "qft_component.h"

#include "qfleet_weapon.h"
#include "qfleet_launchprofile.h"

class QFleet_Option : public qft_component<QFleet_Option>
{
public:
    QFleet_Option();


private:

    QFleet_Weapon weapon;
    QFleet_launchProfile launchProfile;
    QString specialRule;
    unsigned int statBonus;


    bool broadside;
    bool oneOnly;

    unsigned int points;



};

#endif // QFLEET_OPTION_H
