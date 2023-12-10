#ifndef QFLEET_BGT_H
#define QFLEET_BGT_H

#include "qft_enum.h"


enum class bgt
{
    PF,
    LN,
    VG,
    FL

};

// the type of battlegroup
class QFleet_BGT : public qft_enum<QFleet_BGT, bgt>
{
    friend class qft_enum<QFleet_BGT, bgt>;

public:
    QFleet_BGT(const QString set) : qft_enum<QFleet_BGT, bgt>(set)
    {
    }

    QFleet_BGT(const bgt set) : qft_enum<QFleet_BGT, bgt>(set)
    {
    }

    QFleet_BGT(QJsonObject in) : qft_enum<QFleet_BGT, bgt>(in)
    {
    }

    QFleet_BGT()
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

    bgt impl_string_to_enum(const QString in)
    {
        return s2e[in];
    }

    QString impl_enum_to_string(const bgt in)
    {
        return e2s[in];
    }

    QVector<QString> impl_getEnumStrings()
    {
        return QVector<QString>{val_PF,val_LN,val_VG,val_FL};
    }

private:

    const static QString label;
    const static QString val_PF;
    const static QString val_LN;
    const static QString val_VG;
    const static QString val_FL;

    const static QMap<QString, bgt> s2e;
    const static QMap<bgt, QString> e2s;
};


#endif // QFLEET_BGT_H
