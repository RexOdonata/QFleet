#ifndef QFLEET_ARC_H
#define QFLEET_ARC_H

#include "qft_enum.h"
#include <QMap>

enum class arc
{
    FN,
    F,
    FS,
    FSl,
    FSr,
    FSR,
    L,
    R,
};

class QFleet_Arc : public qft_enum<QFleet_Arc>
{
    friend class qft_enum<QFleet_Arc>;

public:
    QFleet_Arc(const QString set) : value(s2e[set])
    {

    }

    QFleet_Arc(const arc set) : value(set)
    {

    }

    QFleet_Arc(QJsonObject in)
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

    QFleet_Arc()
    {
        value = {};
    }


protected:

    std::optional<arc> value;

    QJsonObject impl_toJson()
    {
        QJsonObject json;
        json.insert(label, this->getString());
        return json;
    }

    QVector<QString> impl_getEnumStrings()
    {
        return QVector<QString>{val_FN, val_F, val_FS, val_FSl, val_FSr, val_FSR, val_L, val_R};
    }

private:
    const static QString label;
    const static QString val_FN;
    const static QString val_F;
    const static QString val_FS;
    const static QString val_FSl;
    const static QString val_FSr;
    const static QString val_FSR;
    const static QString val_L;
    const static QString val_R;

    const static QMap<QString, arc> s2e;
    const static QMap<arc, QString> e2s;

};

#endif // QFLEET_ARC_H
