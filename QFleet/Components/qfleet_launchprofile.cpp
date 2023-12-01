#include "qfleet_launchprofile.h"

const QString QFleet_launchProfile::label = "launchProfile";

QFleet_launchProfile::QFleet_launchProfile(const QString setName) : qft_component<QFleet_launchProfile>(setName)
{

}

QFleet_launchProfile::QFleet_launchProfile(QJsonObject in) : qft_component<QFleet_launchProfile>(in.value(field_name()).toString())
{
    fieldFromJson(in, field_assets, assetNames);
    fieldFromJson(in, field_count, count);
    fieldFromJson(in, field_limited, limited);
    fieldFromJson(in, field_strike, strike);
}

void QFleet_launchProfile::impl_toJson(QJsonObject& json)
{
    fieldToJson(json,field_assets, assetNames);
    fieldToJson(json, field_count, count);
    fieldToJson(json, field_limited, limited);
    fieldToJson(json, field_strike, strike);
}

void QFleet_launchProfile::setCount(const unsigned int setCount)
{
    count = setCount;
}

void QFleet_launchProfile::setLimited(const unsigned int set)
{
    limited = set;
}

void QFleet_launchProfile::setStrike(const bool set)
{
    strike = set;
}

void QFleet_launchProfile::setAssetNames(QVector<QString>& set)
{
    for (auto itr = set.begin(); itr != set.end(); itr++)
    {
        assetNames.append(*itr);

        if (itr+1 != set.end())
            assetNames.append(" & ");
    }
}


