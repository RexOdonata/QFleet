#include "qfleet_option.h"

const QString QFleet_Option::label="option";
const QString QFleet_Option::field_weapons="weapons";
const QString QFleet_Option::field_launchProfile="launchProfile";
const QString QFleet_Option::field_specialRule="specialRule";
const QString QFleet_Option::field_statBonus="statBonus";
const QString QFleet_Option::field_broadside="broadside";
const QString QFleet_Option::field_oneOnly="oneOnly";

QFleet_Option::QFleet_Option(const QString setName) : qft_component<QFleet_Option>(setName)
{

}
QFleet_Option::QFleet_Option(QJsonObject in) : qft_component<QFleet_Option>
    (in.value(field_name()).toString())
{
    fieldFromJson(in, field_broadside, broadside);
    fieldFromJson(in, field_oneOnly, oneOnly);
    fieldFromJson(in, field_statBonus, statBonus);

    weaponPtr = std::make_shared<QVector<QFleet_Weapon>>();
    fieldFromJson(in, field_weapons, weaponPtr);


    fieldFromJson(in, field_launchProfile, launchProfilePtr);


}

void QFleet_Option::impl_toJson(QJsonObject& json)
{
    fieldToJson(json, field_broadside, broadside);
    fieldToJson(json, field_oneOnly, oneOnly);
    fieldToJson(json, field_statBonus, statBonus);
    fieldToJson(json, field_specialRule, specialRule);

    fieldToJson(json, field_weapons, weaponPtr);
    fieldToJson(json, field_launchProfile, launchProfilePtr);
}
