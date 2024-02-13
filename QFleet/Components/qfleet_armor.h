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


class QFleet_Armor : public qft_enum<QFleet_Armor, armor>
{
    friend class qft_enum<QFleet_Armor,armor>;

public:
    QFleet_Armor(const QString set) : qft_enum<QFleet_Armor, armor>(set)
    {
    }

    QFleet_Armor(const armor set) : qft_enum<QFleet_Armor, armor>(set)
    {
    }

    QFleet_Armor(QJsonObject in) : qft_enum<QFleet_Armor, armor>(in)
    {
    }

    QFleet_Armor()
    {
    }


protected:    

    QJsonObject impl_toJson()
    {
        QJsonObject json;
        json.insert(label, this->toString());
        return json;
    }

    QString impl_getLabel() const
    {
        return label;
    }

    armor impl_string_to_enum(const QString in) const
    {
        return s2e[in];
    }

    QString impl_enum_to_string(const armor in) const
    {
        return e2s[in];
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
