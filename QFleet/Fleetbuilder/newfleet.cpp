#include "newfleet.h"
#include "ui_newfleet.h"

newFleet::newFleet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newFleet)
{
    ui->setupUi(this);
}

newFleet::~newFleet()
{
    delete ui;
}
