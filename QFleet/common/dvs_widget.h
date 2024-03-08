#ifndef DVS_WIDGET_H
#define DVS_WIDGET_H


#include "qlineedit.h"
#include <QStringListModel>
#include <memory>
#include <QWidget>
#include <QCompleter>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <optional>

#include "fileTypes.h"

#include <type_traits>

namespace Ui {
class dvs_WidgetBase;
}

// The QOBJECT macro and templates doen't fix apparently.

// provides the UI
class dvs_WidgetBase : public QWidget
{
    Q_OBJECT

public:
    explicit dvs_WidgetBase(QWidget *parent = nullptr);
    ~dvs_WidgetBase();

    void setLabel(const QString);


protected:

    QStringListModel  * listModel;

    void createSearchBar();

    QString getSelectedStr() const;

    QVector<QString> getMultiSelectStr() const;

private:

    // is this being double deleted?
    Ui::dvs_WidgetBase *ui;

    QCompleter * completer = NULL;

    QLineEdit * searchLinePtr = NULL;

};


template <typename T>
inline QString getStr(const T in)
{
    return in.getName();
}

template <>
inline QString getStr<QString>(const QString in)
{
    return in;
}


template <typename T>
class dvs_Widget : public dvs_WidgetBase
{
    private:

    void refresh()
    {
        QStringList strings;

        for (auto& item : data)
        {
            strings.push_back(getStr(item));
        }

        this->listModel->setStringList(strings);
    }

    public:

    dvs_Widget(QWidget *parent = nullptr) : dvs_WidgetBase(parent)
    {

    }

    void add(const T in)
    {
        data.insert(getStr(in), in);
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
        auto selID = dvs_WidgetBase::getSelectedStr();
        if (data.contains(selID))
        {
            return data[selID];
        }

        else
            return {};
    }

    QVector<T> getMultiSelected() const
    {
        auto selIDs = dvs_WidgetBase::getMultiSelectStr();

        QVector<T> objs;

        for (auto& str : selIDs)
            if (data.contains(str))
                objs.push_back(data[str]);

        return objs;
    }

    void loadFromFile(QWidget * parent, const QString fileType)
    {
        data.clear();

        QString filename = QFileDialog::getOpenFileName(parent, "open content", QDir::currentPath(), getExtensionFilter(fileType));

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


        QString filename = QFileDialog::getSaveFileName(parent, "save content", QDir::currentPath(), getExtensionFilter(fileType));

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

    protected:

        QMap<QString, T> data;
};

template <typename T>
class dvsx_Widget : public dvs_Widget<T>
{
    public:

        dvsx_Widget(QWidget *parent = nullptr) : dvs_Widget<T>(parent)
        {
            this->createSearchBar();
        }
    private:

};



#endif // DVS_WIDGET_H
