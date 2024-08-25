#ifndef HANGAR_H
#define HANGAR_H

#include <QMainWindow>

#include "../Components/qfleet_launchasset.h"
#include <QStringListModel>
#include <QComboBox>

#include "../common/dvs_widget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Hangar; }
QT_END_NAMESPACE

class Hangar : public QMainWindow
{
    Q_OBJECT

public:
    Hangar(QWidget *parent = nullptr);
    ~Hangar();

private:
    Ui::Hangar *ui;

    dvsx_Widget<QFleet_LaunchAsset> * rosterWidget;

    dvs_Widget<QString> * specialWidget;

    QFleet_LaunchAsset saveLaunch();

    void setValidFields();

    void setComboBoxSelection(QComboBox&, QString);

private slots:

    void on_saveWeapon_button_clicked();

    void on_loadWeapon_button_clicked();

    void on_deleteWeapon_button_clicked();

    void on_specialAdd_button_clicked();

    void on_specialRemove_button_clicked();

    void on_actionLoad_triggered();

    void on_actionSave_triggered();

    void on_bomber_radio_clicked();

    void on_torpedo_radio_clicked();

    void on_fighter_radio_clicked();

    void on_drop_radio_clicked();
};
#endif // HANGAR_H
