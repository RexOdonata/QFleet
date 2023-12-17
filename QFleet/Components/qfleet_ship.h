#ifndef QFLEET_SHIP_H
#define QFLEET_SHIP_H

#include "qfleet_launchprofile.h"
#include "qfleet_tonnage.h"
#include "qfleet_weapon.h"
#include "qft_component.h"
#include "qfleet_armor.h"


// this is the parent class for:
    // 1. (S)hipyard ship : the inputs to fleetbuilder
    // 2. (B)uilder ship: represents a selected ship in a fleet builder list
    // 3. (F)leet ship: an output object of fleetbuilder created to flatten a list into an output for printing, cards etc.

class QFleet_Ship : public qft_component<QFleet_Ship>
{
    friend class qft_component<QFleet_Ship>;

public:
    QFleet_Ship(QJsonObject in);
    QFleet_Ship(const QString);

    // VARS

    unsigned int points;
    unsigned int scan;
    unsigned int signature;
    unsigned int thrust;
    unsigned int hull;
    QFleet_Armor armor;
    QFleet_Armor passive;
    unsigned int PD;
    unsigned int groupL;
    unsigned int groupH;
    QFleet_Tonnage tonnage;
    QVector<QString> specialRules;

    QVector<QFleet_Weapon> weapons;
    QVector<QFleet_launchProfile> launch;


protected:


    // FXs

    void impl_toJson(QJsonObject& json);

    // used by child classes
    void ShipToJson(QJsonObject&);


    // STRINGS


    const static QString field_points;
    const static QString field_scan;
    const static QString field_signature;
    const static QString field_thrust;
    const static QString field_hull;
    const static QString field_armor;
    const static QString field_passive;
    const static QString field_PD;
    const static QString field_groupL;
    const static QString field_groupH;
    const static QString field_tonnage;
    const static QString field_special;

    const static QString field_weapons;
    const static QString field_launch;

};

#endif // QFLEET_SHIP_H
