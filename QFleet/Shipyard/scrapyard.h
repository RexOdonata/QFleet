#ifndef SCRAPYARD_H
#define SCRAPYARD_H

#include <QDialog>
#include "../Components/qfleet_option.h"
#include "../Components/qfleet_launchasset.h"
#include "../common/dvs_widget.h"

namespace Ui {
class Scrapyard;
}

class Scrapyard : public QDialog
{
    Q_OBJECT

public:
    explicit Scrapyard(QWidget *parent = nullptr, std::shared_ptr<QFleet_Option> optionPtr= NULL, QVector<QFleet_LaunchAsset> * assetVec = NULL);
    ~Scrapyard();

private slots:

    void on_launchAddButton_clicked();

    void on_launchDeleteButton_clicked();

    void on_saveButton_clicked();

    void on_newWeaponButton_clicked();

    void on_deleteWeaponButton_clicked();

    void on_editWeaponbutton_clicked();

    void on_CopyWeaponButton_clicked();

    void on_specialAddButton_clicked();

    void on_specialDeleteButton_clicked();

private:
    Ui::Scrapyard *ui;

    std::shared_ptr<QFleet_Option> option = NULL;

    std::shared_ptr<dvs_Data<QFleet_Weapon, dvs_Widget>> weaponRoster;
    std::shared_ptr<dvs_Widget> weaponWidget;

    std::shared_ptr<dvs_Data<QFleet_LaunchAsset, dvs_Widget>> launchAssetRoster;
    std::shared_ptr<dvs_Widget> launchAssetWidget;

    std::shared_ptr<dvs_Data<QFleet_launchProfile, dvs_Widget>> launchProfileRoster;
    std::shared_ptr<dvs_Widget> launchProfileWidget;

    std::shared_ptr<dvs_Data<QString, dvs_Widget>> specialRoster;
    std::shared_ptr<dvs_Widget> specialWidget;

};

#endif // SCRAPYARD_H
