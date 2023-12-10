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


class QFleet_Faction : public qft_enum<QFleet_Faction, faction>
{
    friend class qft_enum<QFleet_Faction, faction>;

public:
    QFleet_Faction(const QString set) : qft_enum<QFleet_Faction, faction>(set)
    {

    }

    QFleet_Faction(const faction set) : qft_enum<QFleet_Faction, faction>(set)
    {

    }

    QFleet_Faction(QJsonObject in) : qft_enum<QFleet_Faction, faction>(in)
    {
    }

    QFleet_Faction()
    {

    }

protected:

    QJsonObject impl_toJson()
    {
        QJsonObject json;
        json.insert(label, this->toString());
        return json;
    }

    QString impl_getLabel()
    {
        return label;
    }

    faction impl_string_to_enum(const QString in)
    {
        return s2e[in];
    }

    QString impl_enum_to_string(const faction in)
    {
        return e2s[in];
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
