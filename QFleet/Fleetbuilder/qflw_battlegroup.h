#ifndef QFLW_BATTLEGROUP_H
#define QFLW_BATTLEGROUP_H

#include <QWidget>

#include "../Components/qfleet_bgt.h"
#include "qflw_group.h"
#include "../ListParts/qfleet_cost.h"
#include <QPointer>

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
    void updateCost();

    QFleet_Cost getCost() const;

    // sets constraints based on battlegroup type
    void setType(QFleet_BGT);

    // checks if the BG contains a group of type mandory for it
    bool checkMandatory() const;

    QFleet_BGT getType() const;

public slots:
    // does the grunt work of adding a ship
    void recieveSelectedShip(const QFleet_Ship_Fleet&, QFLW_Battlegroup *);

signals:
    void querySelectedShip(QFLW_Battlegroup *);

private slots:
    void on_addGroupButton_clicked();

    void on_deleteCardButton_clicked();

private:
    Ui::QFLW_Battlegroup *ui;
    // UI

    QVector<QPointer<QFLW_Group>> groups;

    // FXs

    bool canAdd(QFleet_Tonnage) const;

    void flagRemoval(QFLW_Battlegroup *);

    void refreshCostLabels();


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
