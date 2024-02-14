#ifndef DVS_WIDGET_H
#define DVS_WIDGET_H


#include <QStringListModel>
#include <memory>
#include <QWidget>
#include <QCompleter>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <optional>


#include <type_traits>

namespace Ui {
class dvsx_Widget;
class dvs_Widget;
}


// creates a view for a DVS data package, packaging a listView with utility fxs
class dvs_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit dvs_Widget(QWidget *parent = nullptr);
    ~dvs_Widget();

    void setList(const QStringList in);

    QString getSelected();

    QVector<QString> getMultiSelect();

    void setLabel(const QString);


private:

    // is this being double deleted?
    Ui::dvs_Widget *ui;
    QStringListModel  * listModel;


};

// same functionality as DVS with a search menu
class dvsx_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit dvsx_Widget(QWidget *parent = nullptr);
    ~dvsx_Widget();

    void setList(const QStringList in);

    QString getSelected();

    QVector<QString> getMultiSelect();

    void setLabel(const QString);



private:
    Ui::dvsx_Widget *ui;
    QCompleter * completer;
    QStringListModel  * listModel;
};


QString getStr(const QString in);

QString getStr(const QString in);


template<typename T>
QString getStr(const T in)
{
    return in.getName();
}


// links to a DVS widget that it provides data for. Is the entrypoint for functions that modify the view
template<typename T, typename U>
class dvs_Data
{
    public:

    dvs_Data(U * ptr) : widgetPtr(ptr)
    {}

    void add(const T in)
    {
        data.insert(getStr(in),in);
        refresh();
    }

    void add(const QVector<T> in)
    {
        for (auto& element : in)
            data.insert(getStr(element),element);

        refresh();
    }

    int getSize()
    {
        return data.size();
    }

    std::optional<T> mapLookup(const QString in)
    {
        if (data.contains(in))
            return std::optional<T>(data[in]);
        else
            return {};
    }

    QVector<T> getData() const
    {
        QVector<T> output;

        for (auto& element : data)
            output.push_back(element);

        return output;
    }

    void clear()
    {
        data.clear();
        refresh();
    }

    // removes the selected item
    void remove()
    {
        auto opt = this->getSelected();

        if (opt)
        {
            QString key = getStr((*opt));

            data.remove(key);

            refresh();
        }
    }


    std::optional<T> getSelected() const
    {
        auto selID = widgetPtr->getSelected();
        if (data.contains(selID))
        {
            return data[selID];

        }

        else
            return {};
    }

    QVector<T> getMultiSelected() const
    {
        auto selIDs = widgetPtr->getMultiSelect();

        QVector<T> objs;

        for (auto& str : selIDs)
            if (data.contains(str))
                objs.push_back(data[str]);

        return objs;

    }



    void convertToRef()
    {
        for (auto& element : data)
        {
            element.purgeValue();
        }
    }


    void loadFromFile(QWidget * parent, const QString fileType)
    {
        data.clear();

        QString filename = QFileDialog::getOpenFileName(parent, "open content", QDir::currentPath());

        QFile file(filename);

        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QByteArray bytes = file.readAll();

            file.close();

            QJsonParseError err;

            QJsonDocument jsonData = QJsonDocument::fromJson(bytes, &err);

            QJsonObject wrapperObj = jsonData.object();

            if (wrapperObj.contains(fileType))
            {
                QJsonArray objects = wrapperObj[fileType].toArray();

                for (auto object : objects)
                {                    
                    T newObj(object.toObject());
                    data.insert(newObj.getName(), newObj);
                }
            }
            else
            {
                throw std::invalid_argument("Invalid File Type");
            }

        }

        refresh();
    }

    void saveToFile(QWidget * parent, const QString fileType)
    {
        QString filename = QFileDialog::getSaveFileName(parent, "save content", QDir::currentPath());

        QFile file(filename);

        QJsonArray jsonData;

        for (auto& element : data)
        {
            jsonData.append(QJsonValue(element.toJson()));

       }

        QJsonObject wrapperObj;

        wrapperObj.insert(fileType, jsonData);

        if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        {
            QJsonDocument json(wrapperObj);

            QByteArray bytes = json.toJson(QJsonDocument::Indented);

            QTextStream istream(&file);
            istream << bytes;
            file.close();
        }
    }
    private:

    U * widgetPtr;

    QMap<QString, T> data;


    void refresh()
    {
        QStringList strings;

        for (auto& item : data)
        {
            strings.push_back(getStr(item));
        }

        widgetPtr->setList(strings);

    }
};



#endif // DVS_WIDGET_H
