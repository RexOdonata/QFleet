#include "limitwidget.h"
#include "ui_limitwidget.h"

limitWidget::limitWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::limitWidget)
{
    ui->setupUi(this);
}

limitWidget::~limitWidget()
{
    delete ui;
}

void limitWidget::setLimit(unsigned int set)
{
    limit = set;
    ui->maxLabel->setText(QString::number(set));
}

void limitWidget::setValue(unsigned int set)
{
    value = set;
    ui->numLabel->setText(QString::number(set));
}

bool limitWidget::isValid() const
{
    if (value < limit)
        return true;
    else
        return false;
}
