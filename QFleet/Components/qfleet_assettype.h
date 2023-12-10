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

class QFleet_AssetType : public qft_enum<QFleet_AssetType, assetType>
{
    friend class qft_enum<QFleet_AssetType, assetType>;

public:
    QFleet_AssetType(const QString set) : qft_enum<QFleet_AssetType, assetType>(set)
    {
    }

    QFleet_AssetType(const assetType set) : qft_enum<QFleet_AssetType, assetType>(set)
    {
    }

    QFleet_AssetType(QJsonObject in) : qft_enum<QFleet_AssetType, assetType>(in)
    {
    }

    QFleet_AssetType()
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

    assetType impl_string_to_enum(const QString in)
    {
        return s2e[in];
    }

    QString impl_enum_to_string(const assetType in)
    {
        return e2s[in];
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
