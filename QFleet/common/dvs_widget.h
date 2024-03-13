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
#include <QComboBox>
#include <optional>
#include <QStandardItemModel>

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

    QStandardItemModel  * listModel;

    QString getSelectedStr() const;

    QVector<QString> getMultiSelectStr() const;

    std::optional<QString> hasSearchResult() const;

    void addSearchWidget(QWidget *);

    void addFilterWidget(QWidget *);

private:

    // is this being double deleted?
    Ui::dvs_WidgetBase *ui;

    QCompleter * completer = NULL;

    QLineEdit * searchLinePtr = NULL;

protected:
    QComboBox * factionFilter = NULL;

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
    protected:

    void populateStringList(QString)
    {
        // this is just here to get inherited
    }

    void resetStringList()
    {
        // this is just here to get inherited
    }

    void setStringList()
    {
        // this is just here to get inherited
    }

    void clearModel()
    {
        listModel->clear();
    }



    void refresh()
    {

        listModel->clear();

        resetStringList();

        for (auto& item : data)
        {
            QString str = getStr(item);
            auto newItem = new QStandardItem(str);
            populateStringList(str);
            listModel->appendRow(newItem);
        }

        // this iterates over the string list of tiems
        setStringList();

        listModel->setHeaderData(0,Qt::Horizontal, "Data");
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

        ~dvsx_Widget()
        {
            delete searchLinePtr;

            delete completer;

            delete strListModel;
        }
    protected:

        void resetStringList()
        {
            strList.clear();
        }

        void populateStringList(QString str)
        {
            strList.append(str);
        }

    private:

        // VAR

        QLineEdit * searchLinePtr = NULL;
        QCompleter * completer = NULL;

        QStringListModel * strListModel = NULL;

        QStringList strList;

        // FX

        std::optional<QString> hasSearchResult() const
        {
            if (completer != NULL && searchLinePtr != NULL &&
                completer->completionCount() == 1 && searchLinePtr->text().length() > 0)

            return searchLinePtr->text();

            else
                return {};
        }

        void createSearchBar()
        {
            strListModel = new QStringListModel(this);

            completer = new QCompleter(strListModel, this);

            searchLinePtr = new QLineEdit(this);

            this->addSearchWidget(searchLinePtr);

            // set the lineEdit to provide data to the completer
            searchLinePtr->setCompleter(completer);

            strListModel->setStringList(strList);
        }







};


#endif // DVS_WIDGET_H
