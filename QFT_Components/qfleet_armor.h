#ifndef QFLEET_ARMOR_H
#define QFLEET_ARMOR_H



#include "qft_enum.h"
#include <QMap>

enum class armor
{
    Arm2,
    Arm3,
    Arm4,
    Arm5,
    Arm6,
    none,
};


class QFleet_Armor : public qft_enum<QFleet_Armor>
{
public:
    QFleet_Armor(const QString set) : value(s2e[set])
    {

    }

    QFleet_Armor(const armor set) : value(set)
    {

    }

    QFleet_Armor(QJsonObject in)
    {
        if (in.contains(label))
            value = s2e[in.value(label).toString()];
        else
        //exception goes here
        {

        }
    }

    QString getString()
    {
        if (value)
            return e2s[*value];
        else
            return 0;
    }


protected:

    std::optional<armor> value;

    QJsonObject impl_toJson()
    {
        QJsonObject json;
        json.insert(label, this->getString());
        return json;
    }

    QVector<QString> impl_getEnumStrings()
    {
        return QVector<QString>{val_2,val_3,val_4,val_5,val_6,val_n};
    }

private:
    const static QString label;
    const static QString val_2;
    const static QString val_3;
    const static QString val_4;
    const static QString val_5;
    const static QString val_6;
    const static QString val_n;

    const static QMap<QString, armor> s2e;
    const static QMap<armor, QString> e2s;

};

#endif // QFLEET_TONNAGE_H
