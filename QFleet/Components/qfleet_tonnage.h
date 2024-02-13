#ifndef QFLEET_TONNAGE_H
#define QFLEET_TONNAGE_H



#include "qft_enum.h"
#include <QMap>
#include <optional>

enum class tonnage
{
    L,
    L2,
    M,
    H,
    S,
    S2
};


class QFleet_Tonnage : public qft_enum<QFleet_Tonnage, tonnage>
{
    friend class qft_enum<QFleet_Tonnage, tonnage>;

public:
    QFleet_Tonnage(const QString set) : qft_enum<QFleet_Tonnage, tonnage>(set)
    {
    }

    QFleet_Tonnage(const tonnage set) : qft_enum<QFleet_Tonnage, tonnage>(set)
    {
    }

    QFleet_Tonnage(QJsonObject in) : qft_enum<QFleet_Tonnage, tonnage>(in)
    {
    }

    unsigned int getIntValue() const
    {
        if (val)
            return e2u[*val];
        else
            return 0;
    }

    QFleet_Tonnage()
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

    QVector<QString> impl_getEnumStrings() const
    {
        return QVector<QString>{val_L,val_L2,val_M,val_H,val_S,val_S2};
    }

    tonnage impl_string_to_enum(const QString in) const
    {
        return s2e[in];
    }

    QString impl_enum_to_string(const tonnage in) const
    {
        return e2s[in];
    }

private:
    const static QString label;
    const static QString val_L;
    const static QString val_L2;
    const static QString val_M;
    const static QString val_H;
    const static QString val_S;
    const static QString val_S2;

    const static QMap<QString, tonnage> s2e;
    const static QMap<tonnage, QString> e2s;
    const static QMap<tonnage, unsigned int> e2u;
};

#endif // QFLEET_TONNAGE_H
