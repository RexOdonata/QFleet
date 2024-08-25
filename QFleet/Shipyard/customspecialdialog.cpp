#include "customspecialdialog.h"
#include "ui_customspecialdialog.h"

customSpecialDialog::customSpecialDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::customSpecialDialog)
{
    ui->setupUi(this);
}

void customSpecialDialog::setReturn(QString * setPtr)
{
    strPtr = setPtr;
}

customSpecialDialog::~customSpecialDialog()
{
    delete ui;
}

void customSpecialDialog::on_pushButton_clicked()
{
    if (!ui->lineEdit->text().isEmpty() && strPtr != NULL)
    {
        *strPtr = ui->lineEdit->text();
        this->done(QDialog::Accepted);
    }
    else
    {
        this->done(QDialog::Rejected);
    }
}

