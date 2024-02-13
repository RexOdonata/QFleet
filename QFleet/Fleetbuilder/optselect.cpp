#include "optselect.h"
#include "ui_optselect.h"

optSelect::optSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::optSelect)
{
    ui->setupUi(this);
}

optSelect::~optSelect()
{
    delete ui;
}
