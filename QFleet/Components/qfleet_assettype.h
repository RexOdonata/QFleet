#ifndef QFLEET_ASSETTYPE_H
#define QFLEET_ASSETTYPE_H

#include "qft_enum.h"
#include <QMap>

enum class assetType
{
    fighter,
    bomber,
    torpedo,
    drop
};

class QFleet_AssetType : public qft_enum<QFleet_AssetType>
{
    friend class qft_enum<QFleet_AssetType>;

public:
    QFleet_AssetType(const QString set) : value(s2e[set])
    {

    }

    QFleet_AssetType(const assetType set) : value(set)
    {

    }

    QFleet_AssetType(QJsonObject in)
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

    QFleet_AssetType()
    {
        value = {};
    }


protected:

    std::optional<assetType> value;

    QJsonObject impl_toJson()
    {
        QJsonObject json;
        json.insert(label, this->getString());
        return json;
    }

    QVector<QString> impl_getEnumStrings()
    {
        return QVector<QString>{val_fighter, val_bomber, val_torpedo, val_drop};
    }

private:
    const static QString label;
    const static QString val_fighter;
    const static QString val_bomber;
    const static QString val_torpedo;
    const static QString val_drop;

    const static QMap<QString, assetType> s2e;
    const static QMap<assetType, QString> e2s;

};

#endif // QFleet_AssetType_H
