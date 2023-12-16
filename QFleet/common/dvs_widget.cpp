#include "dvs_widget.h"
#include "ui_dvs_widget.h"
#include "ui_dvsx_widget.h"

// view and search widget

dvsx_Widget::dvsx_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dvsx_Widget)
{
    ui->setupUi(this);

    // model-list of data IDs
    listModel = new QStringListModel(this);

    //  create a completer linked to the list of data IDs
    completer = new QCompleter(listModel, this);


    ui->listView->setModel(listModel);

    // set the lineEdit to provide data to the completer
    ui->searchLine->setCompleter(completer);


}

void dvsx_Widget::setList(const QStringList in)
{
    listModel->setStringList(in);
}

QString dvsx_Widget::getSelected()
{
    if (completer->completionCount() == 1 && ui->searchLine->text().length() > 0)
    {
        return ui->searchLine->text();
    }
    else if (ui->listView->selectionModel()->selectedIndexes().size() > 0)
    {
        return ui->listView->selectionModel()->selectedIndexes().front().data().toString();
    }

    return "";
}

QVector<QString> dvsx_Widget::getMultiSelect()
{
    if (ui->listView->selectionModel()->selectedIndexes().size() > 0)
    {
        auto selectedIndices = ui->listView->selectionModel()->selectedIndexes();

        QVector<QString> strs;
        for (auto index : selectedIndices)

            strs.push_back(index.data().toString());

        return strs;
    }
    else
        return QVector<QString>();
}

void dvsx_Widget::setLabel(const QString in)
{
    ui->label->setText(in);
}


dvsx_Widget::~dvsx_Widget()
{
    delete completer;

    delete listModel;

    delete ui;
}

// view only widget

dvs_Widget::dvs_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dvs_Widget)
{
    ui->setupUi(this);

    // model-list of data IDs
    listModel = new QStringListModel(this);

    // set the list to display only items that match the current completionList
    ui->listView->setModel(listModel);

}

void dvs_Widget::setList(const QStringList in)
{
    listModel->setStringList(in);
}

QString dvs_Widget::getSelected()
{
    if (ui->listView->selectionModel()->selectedIndexes().size() > 0)
    {
        return ui->listView->selectionModel()->selectedIndexes().front().data().toString();
    }

    return "";
}

QVector<QString> dvs_Widget::getMultiSelect()
{
    if (ui->listView->selectionModel()->selectedIndexes().size() > 0)
    {
        auto selectedIndices = ui->listView->selectionModel()->selectedIndexes();

        QVector<QString> strs;
        for (auto index : selectedIndices)

            strs.push_back(index.data().toString());

        return strs;
    }
    else
        return QVector<QString>();
}


void dvs_Widget::setLabel(const QString in)
{
    ui->label->setText(in);
}

QString getStr(const QString in)
{
    return in;
}

dvs_Widget::~dvs_Widget()
{
    delete listModel;


    delete ui;
}


