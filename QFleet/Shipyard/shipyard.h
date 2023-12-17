#ifndef SHIPYARD_H
#define SHIPYARD_H

#include <QMainWindow>
#include "../common/dvs_widget.h"
#include "../Components/qfleet_weapon.h"
#include "../Components/qfleet_ship_shipyard.h"
#include "../Components/qfleet_launchasset.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Shipyard; }
QT_END_NAMESPACE

class Shipyard : public QMainWindow
{
    Q_OBJECT

public:
    Shipyard(QWidget *parent = nullptr);
    ~Shipyard();

private slots:
    void on_newWeaponButton_clicked();

    void on_copyWeaponButton_clicked();

    void on_editWeaponButton_clicked();

    void on_deleteWeaponButton_clicked();

    void on_actionLoad_triggered();

    void on_actionSave_triggered();

    void on_launchAddButton_clicked();

    void on_launchDeleteButton_clicked();

    void on_addSpecialButton_clicked();

    void on_deleteSpecialCombo_clicked();

    void on_newOptionButton_clicked();

    void on_editOptionButton_clicked();

    void on_deleteOptionButton_clicked();

    void on_saveShipButton_clicked();

    void on_loadShipButton_clicked();

    void on_loadLaunchAssetsButton_clicked();


private:
    Ui::Shipyard *ui;

    dvs_Data<QFleet_Weapon, dvsx_Widget> * weaponRoster;
    dvsx_Widget * weaponWidget;

    dvs_Data<QFleet_Ship_Shipyard, dvsx_Widget> * shipRoster;
    dvsx_Widget * shipWidget;

    dvs_Data<QFleet_Option, dvsx_Widget> * optionRoster;
    dvsx_Widget * optionWidget;

    dvs_Data<QString, dvs_Widget> * specialRoster;
    dvs_Widget * specialWidget;

    dvs_Data<QFleet_launchProfile, dvs_Widget> * launchRoster;
    dvs_Widget * launchWidget;

    dvs_Data<QFleet_LaunchAsset, dvs_Widget> * launchSelect;
    dvs_Widget * launchSelectWidget;


};
#endif // SHIPYARD_H
