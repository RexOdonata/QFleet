#ifndef QFT_ENUM_H
#define QFT_ENUM_H

#include <QJsonObject>
#include <QVector>
#include <optional>


template<typename T, typename B>
class qft_enum
{
public:

    // creates a json object out of this enum
    QJsonObject toJson()
    {
        return static_cast<T*>(this)->impl_toJson();
    }

    qft_enum(QJsonObject json)
    {
        QString label = static_cast<T*>(this)->impl_getLabel();

        val = static_cast<T*>(this)->impl_string_to_enum(json.value(label).toString());
    }   

    QVector<QString> getEnumStrings()
    {
        return static_cast<T*>(this)->impl_getEnumStrings();
    }

    qft_enum(const QString in)
    {
        val = static_cast<T*>(this)->impl_string_to_enum(in);
    }

    qft_enum(const B set) : val(set)
    {
    }

    qft_enum() : val({})
    {

    }

    bool hasVal() const
    {
        if (val)
            return true;
        else
            return false;
    }

    B getVal()
    {
        if (val)
            return *val;
        else
            qFatal("Opened empty enum instance");
    }

    QString toString()
    {
        if (val)
            return static_cast<T*>(this)->impl_enum_to_string(*val);
        else
            return "{empty}";
    }

protected:

    std::optional<B> val;

    QJsonObject impl_toJson()
    {       
        qFatal("enum skeleton call to json impl");

        return QJsonObject();
    }

    QString impl_getLabel()
    {
        qFatal("enum skeleton call to label get impl");

        return "whoops";
    }

    QVector<QString> impl_getEnumStrings()
    {
        qFatal("enum skeleton call to string impl");
        return {};
    }

    B impl_string_to_enum(const QString)
    {
        qFatal("enum skeleton call to s2e");
    }

    QString impl_string_to_enum(const B)
    {
        qFatal("enum skeleton call to s2e");
    }







};

#endif // QFT_ENUM_H
