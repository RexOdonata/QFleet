#ifndef QFLEET_TONNAGE_H
#define QFLEET_TONNAGE_H



#include "qft_enum.h"
#include <QMap>

enum class lock
{
    lk2,
    lk3,
    lk4,
    lk5,
    lk6,
    lkX
};


class QFleet_Lock : public qft_enum<QFleet_Lock>
{
public:
    QFleet_Lock(const QString set) : value(s2e[set])
    {

    }

    QFleet_Lock(const lock set) : value(set)
    {

    }

    QFleet_Lock()
    {
        value = {};
    }

    QFleet_Lock(QJsonObject in)
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

protected:

    std::optional<lock> value;

    QJsonObject impl_toJson()
    {
        QJsonObject json;
        json.insert(label, this->getString());
        return json;
    }

    QVector<QString> impl_getEnumStrings()
    {
        return QVector<QString>{val_2,val_3,val_4,val_5,val_6,val_x};
       }

private:
    const static QString label;
    const static QString val_2;
    const static QString val_3;
    const static QString val_4;
    const static QString val_5;
    const static QString val_6;
    const static QString val_x;

    const static QMap<QString, lock> s2e;
    const static QMap<lock, QString> e2s;
};

#endif // QFLEET_TONNAGE_H
