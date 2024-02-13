#include "qfleet_ship_fleet.h"

const QString  QFleet_Ship_Fleet::label="Ship.fleet";
const QString  QFleet_Ship_Fleet::field_selectedOptions="selectedOptions";


QFleet_Ship_Fleet::QFleet_Ship_Fleet(QJsonObject in) : QFleet_Ship(in)
{
    fieldToJson(in, field_selectedOptions, selectedOptions);
}

QFleet_Ship_Fleet::QFleet_Ship_Fleet (const QString setName) : QFleet_Ship(setName)
{

}

void QFleet_Ship_Fleet::impl_toJson(QJsonObject& in)
{
    fieldFromJson(in, field_selectedOptions, selectedOptions);
}

QString QFleet_Ship_Fleet::getArmorString() const
{
    QString str=this->armor.toString();

    if (this->passive.getVal() != armor::none)
    {
        str.append("/");
        str.append(this->passive.toString());
    }

    return str;
}

QString QFleet_Ship_Fleet::getSigString() const
{
    QString str = QString(this->signature);

    if (this->altSig > 0)
    {
        str.append("/");
        str.append(QString(this->altSig));
    }

    return str;
}

QString QFleet_Ship_Fleet::getGroupString() const
{
    QString str = QString(this->groupL);

    if (this->groupL != this->groupH)
    {
        str.append("-");
        str.append(QString(this->groupH));
    }

    return str;
}

QString QFleet_Ship_Fleet::getSpecialString() const
{
    QString str;

    for (auto& special : specialRules)
    {
        str.append(special);

        if (special != specialRules.back())
            str.append(",");
    }

    return str;
}
