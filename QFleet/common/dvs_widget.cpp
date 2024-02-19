#include "dvs_widget.h"
#include <QLineEdit>
#include <QLabel>
#include "ui_dvs_widget.h"


dvs_WidgetBase::dvs_WidgetBase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dvs_WidgetBase)
{
    ui->setupUi(this);

    // model-list of data IDs
    listModel = new QStringListModel(this);

    ui->listView->setModel(listModel);


}

dvs_WidgetBase::~dvs_WidgetBase()
{
    if (completer)
        delete completer;

    delete listModel;

    delete ui;
}

void dvs_WidgetBase::setLabel(const QString in)
{
    ui->label->setText(in);
}

QString dvs_WidgetBase::getSelectedStr() const
{
    if (completer && completer->completionCount() == 1 && searchLinePtr->text().length() > 0)
    {
        return searchLinePtr->text();
    }
    else if (ui->listView->selectionModel()->selectedIndexes().size() > 0)
    {
        return ui->listView->selectionModel()->selectedIndexes().front().data().toString();
    }

    return "";
}

QVector<QString> dvs_WidgetBase::getMultiSelectStr() const
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

// documentation says that adding a widget to layout means layout takes ownership AND will delete it
// so I don't think that this will result in memory leaks, should check on that
void dvs_WidgetBase::createSearchBar()
{
    completer = new QCompleter(listModel, this);

    QLabel * label = new QLabel(this);

    label->setText("Search :");

    QLineEdit * searchLine = new QLineEdit(this);

    searchLinePtr = searchLine;

    ui->searchBoxLayout->addWidget(label);

    ui->searchBoxLayout->addWidget(searchLine);

    // set the lineEdit to provide data to the completer
    searchLine->setCompleter(completer);



}
