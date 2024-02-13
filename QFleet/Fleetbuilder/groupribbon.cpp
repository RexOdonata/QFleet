#include "groupribbon.h"
#include "ui_groupribbon.h"

groupRibbon::groupRibbon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::groupRibbon)
{
    ui->setupUi(this);
}

groupRibbon::~groupRibbon()
{
    delete ui;
}
