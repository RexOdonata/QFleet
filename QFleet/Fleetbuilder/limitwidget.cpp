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
