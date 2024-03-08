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
    listModel = new QStandardItemModel(this);

    ui->treeView->setModel(listModel);

}

dvs_WidgetBase::~dvs_WidgetBase()
{
    if (completer)
        delete completer;

    if (searchLinePtr)
        delete searchLinePtr;

    if (factionFilter)
        delete factionFilter;

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
    else if (ui->treeView->selectionModel()->selectedIndexes().size() > 0)
    {
        return ui->treeView->selectionModel()->selectedIndexes().front().data().toString();
    }

    return "";
}

QVector<QString> dvs_WidgetBase::getMultiSelectStr() const
{
    if (ui->treeView->selectionModel()->selectedIndexes().size() > 0)
    {
        auto selectedIndices = ui->treeView->selectionModel()->selectedIndexes();

        QVector<QString> strs;
        for (auto index : selectedIndices)

            strs.push_back(index.data().toString());

        return strs;
    }
    else
        return QVector<QString>();
}


void dvs_WidgetBase::createSearchBar()
{
    completer = new QCompleter(listModel, this);


    searchLinePtr = new QLineEdit(this);

    ui->searchBoxLayout->addWidget(searchLinePtr);

    // set the lineEdit to provide data to the completer
    searchLinePtr->setCompleter(completer);

}

void dvs_WidgetBase::createFactionCombo()
{
    ui->factionFilterLayout->addWidget(factionFilter);
}
