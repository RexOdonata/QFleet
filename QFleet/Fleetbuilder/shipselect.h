#ifndef SHIPSELECT_H
#define SHIPSELECT_H

#include <QDialog>
#include "../Components/qfleet_ship_shipyard.h"
#include <QTreeView>
#include "../ShipView/shipview.h"
#include <array>


namespace Ui {
class shipSelect;
}

class shipSelect : public QDialog
{
    Q_OBJECT

public:
    explicit shipSelect(QWidget *parent = nullptr, const QMap<QString, QFleet_Ship_Shipyard> * shipData = NULL);
    ~shipSelect();

    std::optional<QFleet_Ship_Fleet> getSelectedShip() const;

private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_treeView_activated(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_selectOptionsButton_clicked();

private:
    Ui::shipSelect *ui;

    // VARS AND LINKS

    const QMap<QString, QFleet_Ship_Shipyard> * shipData;

    QStandardItemModel * shipTreeModel;

    // DATA

    QFleet_Ship_Fleet ship;

    bool valid = false;

    // UI ELEMENTS

    shipView * shipViewWidget;

    // FXs

    void insertShip(std::array<QStandardItem *,5> model, const QString);

    bool checkMinOpts(const QFleet_Ship_Shipyard&);

    // take a ship from source and convert into a fleet ship.
    QFleet_Ship_Fleet createShip(const QFleet_Ship_Shipyard&, QVector<QFleet_Option>&);
};

#endif // SHIPSELECT_H
