#include "group.h"
#include "ui_group.h"

group::group(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::group)
{
    ui->setupUi(this);
}

group::~group()
{
    delete ui;
}
