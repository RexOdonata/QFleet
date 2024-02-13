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

class QFleet_Arc : public qft_enum<QFleet_Arc, arc>
{
    friend class qft_enum<QFleet_Arc, arc>;

public:
    QFleet_Arc(const QString set) : qft_enum<QFleet_Arc, arc>(set)
    {

    }

    QFleet_Arc(const arc set) : qft_enum<QFleet_Arc, arc>(set)
    {

    }

    QFleet_Arc(QJsonObject in) : qft_enum<QFleet_Arc, arc>(in)
    {

    }

    QFleet_Arc()
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

    arc impl_string_to_enum(const QString in) const
    {
        return s2e[in];
    }

    QString impl_enum_to_string(const arc in) const
    {
        return e2s[in];
    }

    QVector<QString> impl_getEnumStrings() const
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
