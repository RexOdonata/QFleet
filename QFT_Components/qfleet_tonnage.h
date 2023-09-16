#ifndef QFLEET_TONNAGE_H
#define QFLEET_TONNAGE_H



#include "qft_enum.h"
#include <QMap>

enum class tonnage
{
    L,
    L2,
    M,
    H,
    S,
    S2
};


class QFleet_Tonnage : public qft_enum<QFleet_Tonnage>
{
public:
    QFleet_Tonnage(const QString set) : value(s2e[set])
    {

    }

    QFleet_Tonnage(const tonnage set) : value(set)
    {

    }

    QFleet_Tonnage(QJsonObject in)
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

    unsigned int getIntValue()
    {
        if (value)
            return e2u[*value];
        else
            return 0;
    }

protected:

    std::optional<tonnage> value;

    QJsonObject impl_toJson()
    {
        QJsonObject json;
        json.insert(label, this->getString());
        return json;
    }

    QVector<QString> impl_getEnumStrings()
    {
        return QVector<QString>{val_L,val_L2,val_M,val_H,val_S,val_S2};
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
