#ifndef ARSENAL_H
#define ARSENAL_H

#include <QMainWindow>

#include "../Components/qfleet_weapon.h"
#include "../common/dvs_widget.h"

namespace Ui {
class Arsenal;
}

class Arsenal : public QDialog
{
    Q_OBJECT

public:
    explicit Arsenal(QWidget *parent = nullptr, std::shared_ptr<QFleet_Weapon> weaponPtr = NULL);
    ~Arsenal();



private slots:
    void on_addSpecialButton_clicked();

    void on_deleteSpecialButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::Arsenal *ui;

    std::shared_ptr<QFleet_Weapon> weapon = NULL;

    dvs_Widget<QString> * specialWidget;
};

#endif // ARSENAL_H
