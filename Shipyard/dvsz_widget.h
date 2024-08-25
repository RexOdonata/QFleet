#ifndef DVSZ_WIDGET_H
#define DVSZ_WIDGET_H

#include "dvs_widget.h"
#include "../Components/qfleet_faction.h"
#include "../Components/qfleet_ship_shipyard.h"


class dvsz_Widget : public dvsx_Widget<QFleet_Ship_Shipyard>
{
public:

    dvsz_Widget(QWidget *parent = nullptr) : dvsx_Widget<QFleet_Ship_Shipyard>(parent)
    {
        this->setupFilter();
    }

    void manualRefresh()
    {
        this->refresh();
    }

private:

    void refresh()
    {
        std::array<QStandardItem *, 4> shipWeights;
        shipWeights[0] = new QStandardItem("L");
        shipWeights[1] = new QStandardItem("M");
        shipWeights[2] = new QStandardItem("H");
        shipWeights[3] = new QStandardItem("SH");

        this->clearModel();
        resetStringList();

        QFleet_Faction selectedFaction = QFleet_Faction(factionFilter->currentText());

        for (auto& item : this->data)
        {
            if (item.factions.contains(selectedFaction))
            {
                QString str = getStr(item);
                addShip(shipWeights,item);
                populateStringList(str);
            }

        }

        for (auto& ptr : shipWeights)
            this->listModel->appendRow(ptr);

        listModel->setHeaderData(0,Qt::Horizontal, "Data");
        setStringList();
    }

    void addShip(std::array<QStandardItem *, 4>& models, QFleet_Ship_Shipyard& ship)
    {
        QStandardItem * shipItem = new QStandardItem(ship.name);

        auto val = ship.tonnage.getIntValue();

        switch (val)
        {
        case 1://L
            models[0]->appendRow(shipItem);
            break;

        case 2://L
            models[0]->appendRow(shipItem);
            break;

        case 5://M
            models[1]->appendRow(shipItem);
            break;

        case 10://H
            models[2]->appendRow(shipItem);
            break;

        case 15://SH
            models[3]->appendRow(shipItem);
            break;

        case 30://SH
            models[3]->appendRow(shipItem);
            break;

        default:
            // this should NEVER happen, but it handles a possible memory leak
            delete shipItem;
            break;
        }
    }

    void setupFilter()
    {
        this->factionFilter = new QComboBox(this);

        auto fStrs = QFleet_Faction("bork").getEnumStrings();

        for (auto& str : fStrs)
            this->factionFilter->addItem(str);

        this->addFilterWidget(factionFilter);

        connect(this->factionFilter, &QComboBox::currentTextChanged,
                this, &dvsz_Widget::slotFilterChanged);

    }

private slots:

    void slotFilterChanged(const QString& text)
    {
        refresh();
    }

};

#endif // DVSZ_WIDGET_H
