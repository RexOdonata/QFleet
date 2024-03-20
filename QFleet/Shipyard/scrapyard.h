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


    dvs_Widget<QFleet_Weapon> * weaponWidget;

    dvs_Widget<QFleet_LaunchAsset> * launchAssetWidget;

    dvs_Widget<QFleet_LaunchProfile> * launchProfileWidget;

    dvs_Widget<QString> * specialWidget;

};

#endif // SCRAPYARD_H
