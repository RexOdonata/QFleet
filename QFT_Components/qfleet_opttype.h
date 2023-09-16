#ifndef QFLEET_OPTTYPE_H
#define QFLEET_OPTTYPE_H

#include "qft_enum.h"

enum class optType
{
    WEAPONS,
    LAUNCH,
    STAT,
    SPECIAL
};

class QFleet_OptType : public qft_enum<QFleet_OptType>
{
public:
    QFleet_OptType();

    QFleet_OptType(const QString set) : value(s2e[set])
    {

    }

    QFleet_OptType(const optType set) : value(set)
    {

    }

    QFleet_OptType(QJsonObject in)
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

    std::optional<optType> value;

    QJsonObject impl_toJson()
    {
        QJsonObject json;
        json.insert(label, this->getString());
        return json;
    }

    QVector<QString> impl_getEnumStrings()
    {
        return QVector<QString>{val_weapon,val_launch,val_stat,val_special};
    }

private:

    const static QString label;
    const static QString val_weapon;
    const static QString val_launch;
    const static QString val_stat;
    const static QString val_special;

    const static QMap<QString, optType> s2e;
    const static QMap<optType, QString> e2s;

};

#endif // QFLEET_OPTTYPE_H
