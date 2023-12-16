#ifndef QFLEET_STATID_H
#define QFLEET_STATID_H

#include "qft_enum.h"


// not putting armor in here because its an enum, not an int
enum class statID
{
    scan,
    sig,
    thrust,
    hull,
    PD
};

class QFleet_StatID : public qft_enum<QFleet_StatID, statID>
{
    friend class qft_enum<QFleet_StatID, statID>;

public:
    QFleet_StatID(const QString set) : qft_enum<QFleet_StatID, statID>(set)
    {

    }

    QFleet_StatID(const statID set) : qft_enum<QFleet_StatID, statID>(set)
    {

    }

    QFleet_StatID(QJsonObject in) : qft_enum<QFleet_StatID, statID>(in)
    {

    }

    QFleet_StatID()
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

    statID impl_string_to_enum(const QString in)
    {
        return s2e[in];
    }

    QString impl_enum_to_string(const statID in)
    {
        return e2s[in];
    }

    QVector<QString> impl_getEnumStrings()
    {
        return QVector<QString>{val_scan, val_sig, val_thrust, val_hull, val_PD};
    }

private:

    const static QString label;
    const static QString val_scan;
    const static QString val_sig;
    const static QString val_thrust;
    const static QString val_hull;
    const static QString val_PD;

    const static QMap<QString, statID> s2e;
    const static QMap<statID, QString> e2s;


};

#endif // QFLEET_STATID_H
