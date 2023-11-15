#ifndef QFLEET_FACTION_H
#define QFLEET_FACTION_H



#include "qft_enum.h"
#include <QMap>
#include <optional>

enum class faction
{
    UCM,
    SCOURGE,
    PHR,
    SHALTARI,
    RESISTANCE
};


class QFleet_Faction : public qft_enum<QFleet_Faction>
{
    friend class qft_enum<QFleet_Faction>;

public:
    QFleet_Faction(const QString set) : value(s2e[set])
    {

    }

    QFleet_Faction(const faction set) : value(set)
    {

    }

    QFleet_Faction(QJsonObject in)
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

    QFleet_Faction()
    {
        value = {};
    }

protected:

    std::optional<faction> value;

    QJsonObject impl_toJson()
    {
        QJsonObject json;
        json.insert(label, this->getString());
        return json;
    }

    QVector<QString> impl_getEnumStrings()
    {
        return QVector<QString>{val_ucm, val_scourge, val_phr, val_shaltari, val_resistance};
    }

private:
    const static QString label;
    const static QString val_ucm;
    const static QString val_scourge;
    const static QString val_phr;
    const static QString val_shaltari;
    const static QString val_resistance;

    const static QMap<QString, faction> s2e;
    const static QMap<faction, QString> e2s;
};

#endif // QFleet_Faction_H
