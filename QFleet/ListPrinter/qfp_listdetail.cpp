#include "qfp_listdetail.h"
#include "ui_qfp_listdetail.h"

QFP_ListDetail::QFP_ListDetail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QFP_ListDetail)
{
    ui->setupUi(this);
}

QFP_ListDetail::~QFP_ListDetail()
{
    delete ui;
}
