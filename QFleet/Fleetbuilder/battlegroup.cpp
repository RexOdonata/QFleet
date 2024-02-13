#include "battlegroup.h"
#include "ui_battlegroup.h"

battlegroup::battlegroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::battlegroup)
{
    ui->setupUi(this);
}

battlegroup::~battlegroup()
{
    delete ui;
}
