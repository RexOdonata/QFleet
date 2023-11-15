#include "qfleet_weapon.h"

const QString QFleet_Weapon::label = "weapon";
const QString QFleet_Weapon::field_arc="arc";
const QString QFleet_Weapon::field_lock="lock";
const QString QFleet_Weapon::field_attacks="attacks";
const QString QFleet_Weapon::field_damage="damage";
const QString QFleet_Weapon::field_specials="specials";

QFleet_Weapon::QFleet_Weapon(const QString setName, const QString setID) : qft_component<QFleet_Weapon>(setName, setID), lock(QFleet_Lock()), facing(QFleet_Arc())
{

}

QFleet_Weapon::QFleet_Weapon(QJsonObject in) : qft_component<QFleet_Weapon>(in.value(field_name()).toString(), in.value(field_id()).toString())
{
    lock = QFleet_Lock(in.value(field_lock).toObject());
    facing = QFleet_Arc(in.value(field_arc).toObject());
    fieldFromJson(in, field_attacks, attacks);
    fieldFromJson(in, field_damage, damage);
    fieldFromJson(in, field_specials, attacks);


}

void QFleet_Weapon::impl_toJson(QJsonObject& json)
{
    fieldToJson(json, field_attacks, attacks);
    fieldToJson(json, field_damage, damage);
    fieldToJson(json, field_specials, specials);
    json.insert(field_arc, facing.toJson());
    json.insert(field_lock, lock.toJson());
}


