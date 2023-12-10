#include "qfleet_launchasset.h"

const QString QFleet_LaunchAsset::field_strikecraft="strikecraft";
const QString QFleet_LaunchAsset::field_launchcap="launchcap";
const QString QFleet_LaunchAsset::field_thrust="thrust";
const QString QFleet_LaunchAsset::field_PD="PD";
const QString QFleet_LaunchAsset::field_attacks="attacks";
const QString QFleet_LaunchAsset::field_damage="damage";
const QString QFleet_LaunchAsset::field_lock="lock";
const QString QFleet_LaunchAsset::field_special="special";
const QString QFleet_LaunchAsset::field_factions="factions";
const QString QFleet_LaunchAsset::field_type="type";

QFleet_LaunchAsset::QFleet_LaunchAsset(QJsonObject in) : qft_component<QFleet_LaunchAsset>(in.value(field_name()).toString())
{
    fieldFromJson(in, field_strikecraft, strikecraft);
    fieldFromJson(in,field_launchcap,launchCap);
    fieldFromJson(in,field_thrust,thrust);
    fieldFromJson(in,field_PD,PD);
    fieldFromJson(in,field_attacks,attacks);
    fieldFromJson(in,field_damage,damage);
    fieldFromJson(in,field_lock,lock);
    fieldFromJson(in,field_special,special);
    fieldFromJson(in,field_factions,factions);
    fieldFromJson(in,field_type,type);
}

QFleet_LaunchAsset::QFleet_LaunchAsset(const QString setName) : qft_component<QFleet_LaunchAsset>(setName), lock(QFleet_Lock()), type(QFleet_AssetType())
{

}

QFleet_LaunchAsset::QFleet_LaunchAsset() : qft_component<QFleet_LaunchAsset>("blank"), lock(QFleet_Lock()), type(QFleet_AssetType())
{

}


void QFleet_LaunchAsset::impl_toJson(QJsonObject& in)
{
    fieldToJson(in,field_strikecraft,strikecraft);
    fieldToJson(in,field_launchcap,launchCap);
    fieldToJson(in,field_thrust,thrust);
    fieldToJson(in,field_PD,PD);
    fieldToJson(in,field_attacks,attacks);
    fieldToJson(in,field_damage,damage);
    fieldToJson(in, field_lock,lock);
    fieldToJson(in,field_special,special);
    fieldToJson(in,field_factions,factions);
    fieldToJson(in, field_type,type);

}

void QFleet_LaunchAsset::operator=(const QFleet_LaunchAsset& obj)
{
    this->strikecraft = obj.strikecraft;
    this->launchCap = obj.launchCap;
    this->thrust = obj.thrust;
    this->PD = obj.PD;
    this->attacks = obj.attacks;
    this->damage = obj.damage;
    this->lock = obj.lock;
    this->special = obj.special;
    this->factions = obj.factions;
    this->type = obj.type;

}
