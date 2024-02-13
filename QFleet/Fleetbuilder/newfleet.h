#ifndef NEWFLEET_H
#define NEWFLEET_H

#include <QDialog>

namespace Ui {
class newFleet;
}

class newFleet : public QDialog
{
    Q_OBJECT

public:
    explicit newFleet(QWidget *parent = nullptr);
    ~newFleet();

private:
    Ui::newFleet *ui;
};

#endif // NEWFLEET_H
