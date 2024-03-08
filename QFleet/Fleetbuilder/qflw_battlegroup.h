#ifndef QFLW_BATTLEGROUP_H
#define QFLW_BATTLEGROUP_H

#include <QWidget>

#include "../Components/qfleet_bgt.h"
#include "qflw_group.h"
#include "../ListParts/qfleet_cost.h"
#include <QPointer>

#include "../ListParts/qfleet_battlegroup.h"

namespace Ui {
class QFLW_Battlegroup;
}

class QFLW_Battlegroup : public QWidget
{
    Q_OBJECT

public:
    explicit QFLW_Battlegroup(QWidget *parent = nullptr, std::optional<QFleet_BGT> bgt = {});
    ~QFLW_Battlegroup();

    void removeGroup(QFLW_Group *);
    void updateCost(bool = true);

    QFleet_Cost getCost() const;

    // sets constraints based on battlegroup type
    void setType(QFleet_BGT);

    // checks if the BG contains a group of type mandory for it
    bool checkMandatory() const;

    QFleet_BGT getType() const;

    // gets a pointer to the parent object, ie the list object - maybe should be private?
    QWidget * getListPtr() const;

    // create a save/print representation of
    QFleet_Battlegroup createListPart() const;

    // used during loading
    void addGroupListPart(const QFleet_Group&);

    // does the grunt work of adding a ship, emitted from main window I think?
    void recieveSelectedShip(const QFleet_Ship_Fleet&);

    // GROUP DRAG-DROP
    void dragEnterEvent(QDragEnterEvent *);

    void dropEvent(QDropEvent *);


signals:
    // get the currently selected ship from the select dialog
    void querySelectedShip(QFLW_Battlegroup *);

private slots:
    // starts the process to add the selected ship as a child group
    void on_addGroupButton_clicked();

    // delete self and inform parent
    void on_deleteCardButton_clicked();

private:
    Ui::QFLW_Battlegroup *ui;
    // UI

    // stores child group widgets
    QVector<QPointer<QFLW_Group>> groups;

    // FXs

    // check if it is legal to add a group of given type
    bool canAdd(QFleet_Tonnage) const;

    // send a signal up to the list widget to delete this widget
    void flagRemoval(QFLW_Battlegroup *);

    // update UI text labels
    void refreshCostLabels();

    // true +, false -
    // call when adding/removing a ship to update the typeCounts
    void changeTypeCounters(const QFleet_Tonnage, const bool);


    // DATA

    const QWidget * listWidgetPtr;

    QFleet_BGT type;

    QFleet_Cost cost;

    unsigned int allowedL=0;
    unsigned int allowedM=0;
    unsigned int allowedH=0;
    unsigned int allowedSH=0;

    unsigned int countL=0;
    unsigned int countM=0;
    unsigned int countH=0;
    unsigned int countSH=0;

    const static std::array<unsigned int, 16> groupLimitMatrix;
};

#endif // QFLW_BATTLEGROUP_H
