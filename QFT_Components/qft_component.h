#ifndef QFT_COMPONENT_H
#define QFT_COMPONENT_H

#include <QJsonObject>
#include <QJsonArray>


template <typename T>
class qft_component
{
public:

    qft_component(const QString set_name, const QString set_id) : name(set_name), id(set_id)
    {
        // nothing needs to happen here
    }

    // creates a json object out of this component
    QJsonObject toJson()
    {
        QJsonObject json;
        json.insert(field_name(), name);
        json.insert(field_id(), id);
        static_cast<T*>(this)->impl_toJson(json);
        return json;
    }

protected:

    void impl_toJson(QJsonObject& json)
    {
        // whoopsie
        // exception goes here
    }

    // variables
    const QString name;
    const QString id;

    inline static const QString field_name()
    {
        return "name";
    }

    inline static const QString field_id()
    {
        return "id";
    }

    void intToJson(QJsonObject& json, const QString field, const unsigned int val) const
    {
        json.insert(field, QVariant(val).toJsonValue());
    }

    void fieldFromJson(QJsonObject& json, const QString field, unsigned int& val)
    {
        if (json.contains(field))
        {
            val = json.value(field).toInt();
        }
        else
        {
            // exception goes here
        }
    }

    void fieldToJson(QJsonObject& json, const QString field, const QString val) const
    {
        json.insert(field, val);
    }

    void fieldFromJson(QJsonObject& json, const QString field, QString& val)
    {
        if (json.contains(field))
        {
            val = json.value(field).toString();
        }
        else
        {
            // exception goes here
        }
    }

    void fieldToJson(QJsonObject& json, const QString field, const bool val) const
    {
        json.insert(field, val);
    }

    void fieldFromJson(QJsonObject& json, const QString field, bool& val)
    {
        if (json.contains(field))
        {
            val = json.value(field).toBool();
        }
        else
        {
            // exception goes here
        }
    }


    void fieldToJson(QJsonObject& json, const QString field, const QVector<QString> vals) const
    {
        QJsonArray jsonArr;

        for (auto& element : vals)
        {
            jsonArr.push_back(element);
        }

        json.insert(field, jsonArr);
    }

    template<typename O>
    void fieldToJson(QJsonObject& json, const QString field, const QVector<O> vals) const
    {
        QJsonArray jsonArr;

        for (auto& element : vals)
        {
            jsonArr.push_back(element.toJson().toJsonValue());
        }

        json.insert(field, jsonArr);
    }

    template <typename O>
    void fieldFromJson(QJsonObject& json, const QString field, QVector<O>& vals)
    {
        vals.clear();


        if (json.contains(field))
        {
            for (auto element : json.value(field).toArray())
            {
                vals.push_back(O(element.toObject()));
            }
        }
        else
        {
            // exception goes here
        }
    }

    void fieldFromJson(QJsonObject& json, const QString field, QVector<QString>& vals)
    {
        vals.clear();


        if (json.contains(field))
        {
            for (auto element : json.value(field).toArray())
            {
                vals.push_back(element.toString());
            }
        }
        else
        {
            // exception goes here
        }
    }

};

#endif // QFT_COMPONENT_H
