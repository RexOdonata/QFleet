#ifndef CUSTOMSPECIALDIALOG_H
#define CUSTOMSPECIALDIALOG_H

#include <QDialog>

namespace Ui {
class customSpecialDialog;
}

class customSpecialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit customSpecialDialog(QWidget *parent = nullptr);
    ~customSpecialDialog();

    void setReturn(QString *);

private slots:
    void on_pushButton_clicked();

private:
    Ui::customSpecialDialog *ui;

    QString * strPtr = NULL;
};

#endif // CUSTOMSPECIALDIALOG_H
