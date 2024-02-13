#ifndef OPTSELECT_H
#define OPTSELECT_H

#include <QDialog>

namespace Ui {
class optSelect;
}

class optSelect : public QDialog
{
    Q_OBJECT

public:
    explicit optSelect(QWidget *parent = nullptr);
    ~optSelect();

private:
    Ui::optSelect *ui;
};

#endif // OPTSELECT_H
