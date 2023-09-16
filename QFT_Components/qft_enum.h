#ifndef QFT_ENUM_H
#define QFT_ENUM_H

#include <QJsonObject>
#include <QVector>


template<typename T>
class qft_enum
{
public:

    // creates a json object out of this component
    QJsonObject toJson()
    {
        QJsonObject json;
        return static_cast<T*>(this)->impl_toJson(json);
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
        // whoopsie
        // exception goes here
    }

    QVector<QString> impl_getEnumStrings()
    {
        // whoopsie
        // exception goes here
        return {};
    }


};

#endif // QFT_ENUM_H
