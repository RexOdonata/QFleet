#ifndef QFT_ENUM_H
#define QFT_ENUM_H

#include <QJsonObject>
#include <QVector>
#include <optional>


template<typename T>
class qft_enum
{
public:

    // creates a json object out of this enum
    QJsonObject toJson()
    {
        return static_cast<T*>(this)->impl_toJson();
    }

    QVector<QString> getEnumStrings()
    {
        return static_cast<T*>(this)->impl_getEnumStrings();
    }

    qft_enum()
    {

    }

protected:

    QJsonObject impl_toJson()
    {       
        qFatal("enum skeleton call to json impl");

        return QJsonObject();
    }

    QVector<QString> impl_getEnumStrings()
    {
        qFatal("enum skeleton call to string impl");
        return {};
    }


};

#endif // QFT_ENUM_H
