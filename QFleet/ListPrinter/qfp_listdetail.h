#ifndef QFP_LISTDETAIL_H
#define QFP_LISTDETAIL_H

#include <QDialog>

namespace Ui {
class QFP_ListDetail;
}

class QFP_ListDetail : public QDialog
{
    Q_OBJECT

public:
    explicit QFP_ListDetail(QWidget *parent = nullptr);
    ~QFP_ListDetail();

private:
    Ui::QFP_ListDetail *ui;
};

#endif // QFP_LISTDETAIL_H
