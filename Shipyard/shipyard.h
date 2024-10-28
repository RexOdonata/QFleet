#ifndef SHIPYARD_H
#define SHIPYARD_H

#include <QMainWindow>
#include "../common/dvs_widget.h"
#include "../Components/qfleet_weapon.h"
#include "../Components/qfleet_ship_shipyard.h"
#include "../Components/qfleet_launchasset.h"
#include "dvsz_widget.h"


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

    void on_tonnageCombo_currentIndexChanged(int index);

    void on_clearWeaponsButton_clicked();

    void on_deleteShipButton_clicked();

    void on_customSpecialRuleButton_clicked();

    void on_actionSave_Uncompressed_triggered();

private:
    Ui::Shipyard *ui;


    dvsx_Widget<QFleet_Weapon> * weaponWidget;

    dvsz_Widget * shipWidget;

    dvsx_Widget<QFleet_Option> * optionWidget;

    dvs_Widget<QString> * specialWidget;

    dvs_Widget<QFleet_LaunchProfile> * launchWidget;

    dvs_Widget<QFleet_LaunchAsset> * launchSelectWidget;


};
#endif // SHIPYARD_H
