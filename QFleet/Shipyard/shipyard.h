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

    std::shared_ptr<dvs_Data<QFleet_Weapon, dvsx_Widget>> weaponRoster;
    std::shared_ptr<dvsx_Widget> weaponWidget;

    std::shared_ptr<dvs_Data<QFleet_Ship_Shipyard, dvsx_Widget>> shipRoster;
    std::shared_ptr<dvsx_Widget> shipWidget;

    std::shared_ptr<dvs_Data<QFleet_Option, dvsx_Widget>> optionRoster;
    std::shared_ptr<dvsx_Widget> optionWidget;

    std::shared_ptr<dvs_Data<QString, dvs_Widget>> specialRoster;
    std::shared_ptr<dvs_Widget> specialWidget;

    std::shared_ptr<dvs_Data<QFleet_launchProfile, dvs_Widget>> launchRoster;
    std::shared_ptr<dvs_Widget> launchWidget;

    std::shared_ptr<dvs_Data<QFleet_LaunchAsset, dvs_Widget>> launchSelect;
    std::shared_ptr<dvs_Widget> launchSelectWidget;


};
#endif // SHIPYARD_H
