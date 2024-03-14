#ifndef WINDOWUTILS_H
#define WINDOWUTILS_H

#include "qjsonobject.h"
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVector>
#include <QStringListModel>
#include <QListView>

#include <exception>

#include "fileTypes.h"



namespace{
    template<typename T>
    struct listModel_Vector_pair
    {
        QVector<T> * vec;
        QStringListModel * listModel;
        QListView * listView;
        void refresh();
        void link(QWidget *, QListView *);
    };

    template<typename T>
    void listModel_Vector_pair<T>::refresh()
    {
        if (vec && listModel)
        {
            QStringList list;

            for (auto& element : *vec)
            {
                list.push_back(element.getName());
            }

            listModel->setStringList(list);
        }
    }

    template<typename T>
    void listModel_Vector_pair<T>::link(QWidget * parent,QListView * set_listView)
    {
        listModel = new QStringListModel(parent);
        listView = set_listView;
        listView->setModel(listModel);


    }

    template<>
    void listModel_Vector_pair<QString>::refresh()
    {
        if (vec && listModel)
        {
            QStringList list;

            for (auto& element : *vec)
            {
                list.push_back(element);
            }

            listModel->setStringList(list);
        }
    }

    template<typename T>
    void loadVectorFromJsonFile(QWidget * parentWindow, QVector<T>& vec, const QString fileType)
    {
        vec.clear();

        QString filename = QFileDialog::getOpenFileName(parentWindow, "open content", QDir::currentPath(), getExtensionFilter(fileType));

            QFile file(filename);

            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QByteArray data = file.readAll();

                file.close();

                QJsonParseError err;

                QJsonDocument jsonData = QJsonDocument::fromJson(data, &err);

                QJsonObject wrapperObj = jsonData.object();

                if (wrapperObj.contains(fileType))
                {
                    QJsonArray objects = wrapperObj[fileType].toArray();

                    for (auto object : objects)
                    {
                        T obj(object.toObject());
                        vec.push_back(obj);
                    }
                }
                else
                {
                    throw std::invalid_argument("Invalid File Type");
                }

        }
    }

    template<typename T>
    void loadMapFromJsonFile(QWidget * parentWindow, QMap<QString, T>& data,const QString fileType)
    {
        data.clear();

        QString filename = QFileDialog::getOpenFileName(parentWindow, "open content", QDir::currentPath(), getExtensionFilter(fileType));

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
    }

    template<typename T>
    void saveVectorToJsonFile(QWidget * parentWindow, QVector<T>& vec, const QString fileType)
    {
        QString filename = QFileDialog::getSaveFileName(parentWindow, "save content", QDir::currentPath(), getExtensionFilter(fileType));

        QFile file(filename);

        QJsonArray jsonData;

        for (auto& element : vec)
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


    template<typename T>
    void saveObjectToJsonFile(QWidget * parentWindow, T& obj, const QString fileType)
    {
        QString filename = QFileDialog::getSaveFileName(parentWindow, "save content", QDir::currentPath(), getExtensionFilter(fileType));

        QFile file(filename);

        QJsonObject wrapperObj;

        wrapperObj.insert(fileType, obj.toJson());

        if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        {
            QJsonDocument json(wrapperObj);

            QByteArray bytes = json.toJson(QJsonDocument::Indented);

            QTextStream istream(&file);
            istream << bytes;
            file.close();
        }

    }

    template<typename T>
    void loadObjectFromJsonFile(QWidget * parentWindow, T& obj, const QString fileType)
    {
        QString filename = QFileDialog::getOpenFileName(parentWindow, "open content", QDir::currentPath(), getExtensionFilter(fileType));

        QFile file(filename);

        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QByteArray data = file.readAll();

            file.close();

            QJsonParseError err;

            QJsonDocument jsonData = QJsonDocument::fromJson(data, &err);

            QJsonObject wrapperObj = jsonData.object();

            if (wrapperObj.contains(fileType))
            {
                    QJsonObject object = wrapperObj[fileType].toObject();

                    obj = T(object);
            }
            else
            {
                    throw std::invalid_argument("Invalid File Type");
            }

        }

    }



} // end of namespace

#endif // WINDOWUTILS_H
