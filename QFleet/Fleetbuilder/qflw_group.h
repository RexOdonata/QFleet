#ifndef QFLW_GROUP_H
#define QFLW_GROUP_H

#include <QWidget>

#include "../Components/qfleet_ship_fleet.h"
#include "../ListParts/qfleet_cost.h"

#include <QCheckBox>
#include <QLabel>

struct admiralVals
{
    unsigned int level = 0;
    unsigned int cost = 0;
};

namespace Ui {
class QFLW_Group;
}

class QFLW_Group : public QWidget
{
    Q_OBJECT

public:
    explicit QFLW_Group(QWidget *parent = nullptr, std::optional<QFleet_Ship_Fleet> = {});
    ~QFLW_Group();

    QFleet_Cost getCost() const;

    void removeAdmiral();

signals:

    void signalSetAdmiral(QFLW_Group *);

    void signalAdmiralDeleted();

public slots:

    void slotAdmiralValues(admiralVals);

private slots:
    void on_viewShipButton_clicked();

    void on_setAdmiralButton_clicked();

    void on_deleteGroupButton_clicked();

    void on_numSpin_valueChanged(int arg1);

private:
    Ui::QFLW_Group *ui;

    QLabel * admiralLevelLabel;
    QCheckBox * admiralPresenceCheck;

    // DATA

    const QWidget * cardWidgetPtr;

    QFleet_Ship_Fleet ship;

    QFleet_Cost cost;

    unsigned int num = 0;

    std::optional<admiralVals> admiral = {};

    // FX

    void admiralIndicatorVisibility(const bool);

    // send a signal up to parent card to update cost
    void updateCost();

    // send a signal up to parent card to remove from container
    void flagRemoval(QFLW_Group *);

    QFleet_Cost getShipGroupCost(const unsigned int) const;

};

#endif // QFLW_GROUP_H
