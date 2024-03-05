#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "shipselect.h"

#include "../Components/qfleet_ship_shipyard.h"

#include <QPointer>

#include "qflw_list.h"
#include "qflw_battlegroup.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



public slots:
    void slotShipPull(QFLW_Battlegroup *);



signals:
    void sendSelectedShip(const QFleet_Ship_Fleet&, QFLW_Battlegroup *);    

private slots:
    void on_actionNew_triggered();

    void on_actionLoad_Launch_triggered();

    void on_actionLoad_Ships_triggered();

    void on_selectShipsButton_clicked();

    void on_actionLoad_triggered();

    void on_shipMenuButton_clicked();

    void on_actionSave_triggered();

    void on_actionStrategy_Cards_triggered();

    void on_actionSimple_List_triggered();

    void on_actionFleet_List_triggered();

private:
    Ui::MainWindow *ui;

    // UI ELEMENTS
    QPointer<shipSelect> shipSelectDialog;


    QPointer<QFLW_List> listWidget;


    // VARS

    std::optional<QFleet_Faction> faction;

    unsigned int pointsLimit;

    QMap<QString,QFleet_Ship_Shipyard> allShipData;

    // FXs


    void drawGUIFromListPart(const QFleet_List&);

    // UTILITY FXs

    void loadShipData();

    void loadMapFromJsonFile(QWidget * parentWindow, QMap<QString, QFleet_Ship_Shipyard>& data);

    bool loadListFromFile();

    bool saveListToFile();

    bool drawStrategycards();

    bool writeHTML();



};
#endif // MAINWINDOW_H
