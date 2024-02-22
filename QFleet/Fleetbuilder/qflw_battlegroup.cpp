#include "qflw_battlegroup.h"
#include "qmessagebox.h"
#include "ui_qflw_battlegroup.h"

#include "mainwindow.h"

#include "qflw_list.h"

const std::array<unsigned int, 16> QFLW_Battlegroup::groupLimitMatrix =
    {
        3,1,0,0,
        2,3,0,0,
        1,1,2,0,
        1,0,0,2
};

QFLW_Battlegroup::QFLW_Battlegroup(QWidget *parent, std::optional<QFleet_BGT> bgt) :
    QWidget(parent),
    ui(new Ui::QFLW_Battlegroup),
    cost(QFleet_Cost("Card Cost")),
    type(*bgt),
    listWidgetPtr(parent)
{
    ui->setupUi(this);


    QFLW_List * listPtr = (QFLW_List *)listWidgetPtr;
    MainWindow * mainWindowPtr = (MainWindow *) listPtr->getMainWindowPtr();


    QObject::connect(this, &QFLW_Battlegroup::querySelectedShip,
            mainWindowPtr , &MainWindow::slotShipPull);


    QObject::connect(mainWindowPtr , &MainWindow::sendSelectedShip,
            this, &QFLW_Battlegroup::recieveSelectedShip);


    ui->typeLabel->setText(type.toString());

    refreshCostLabels();

    unsigned int index = 0;

    switch (bgt->getVal())
    {
    case bgt::PF:

        index = 0;
        break;

    case bgt::LN:

        index = 1;
        break;

    case bgt::VG:

        index = 2;
        break;
    case bgt::FL:

        index = 3;
        break;
    }

    allowedL = groupLimitMatrix[4*index];
    allowedM = groupLimitMatrix[4*index + 1];
    allowedH = groupLimitMatrix[4*index + 2];
    allowedSH = groupLimitMatrix[4*index + 3];

    this->setAttribute(Qt::WA_DeleteOnClose);
}

QFLW_Battlegroup::~QFLW_Battlegroup()
{
    delete ui;
}

void QFLW_Battlegroup::refreshCostLabels()
{
    ui->pointsLabel->setText(QString::number(cost.points));
    ui->srLabel->setText(QString::number(cost.SR));
}

void QFLW_Battlegroup::updateCost()
{
    cost.zero();

    for (auto groupPtr : groups)
    {
        cost + groupPtr->getCost();
    }

    refreshCostLabels();

    QFLW_List * list = (QFLW_List *) this->parent();

    list->updateCost();
}

QFleet_Cost QFLW_Battlegroup::getCost() const
{
    return cost;
}

// the idea here is that we remove the widgetPtr from the group then let it delelete itself, which will close it.
// sure hope this works
void QFLW_Battlegroup::removeGroup(QFLW_Group * groupPtr)
{
    auto index = 0;
    for (auto group : groups)
    {
        if (group.data() == groupPtr)
        {
            groups.remove(index);
            break;
        }

        index++;
    }

    updateCost();
}

void QFLW_Battlegroup::on_addGroupButton_clicked()
{
    emit querySelectedShip(this);
}

void QFLW_Battlegroup::recieveSelectedShip(const QFleet_Ship_Fleet& ship, QFLW_Battlegroup * cardPtr)
{
    // short circuit if this is not the right card
    if (cardPtr != this)
        return;

    // check if it is possible to add the card
    if (!canAdd(ship.tonnage))
    {
        QMessageBox msg(this);
        msg.setText("Cannot add a group of this type to this Battlegroup");
        msg.exec();
        return;
    }

    QPointer<QFLW_Group> newGroup = new QFLW_Group(this, ship);

    groups.push_back(newGroup);

    ui->groupLayout->addWidget(newGroup.data());

    updateCost();

}

bool QFLW_Battlegroup::canAdd(const QFleet_Tonnage tonnageVal) const
{

    // first, get the type of ship L/M/H/S from its tonnage
    QFleet_BGT shipBGT;

    tonnage groupType = tonnageVal.getVal();

    switch (groupType)
    {
        case tonnage::L:

            shipBGT = QFleet_BGT(bgt::PF);
            break;

        case tonnage::L2:

            shipBGT = QFleet_BGT(bgt::PF);
            break;

        case tonnage::M:

            shipBGT = QFleet_BGT(bgt::LN);
            break;
        case tonnage::H:

            shipBGT = QFleet_BGT(bgt::VG);
            break;
        case tonnage::S:

            shipBGT = QFleet_BGT(bgt::FL);
            break;
        case tonnage::S2:

            shipBGT = QFleet_BGT(bgt::FL);
            break;
    }

    // then use that value to get an index into an array for the appropriate counters
    bgt typeEnum = shipBGT.getVal();

    unsigned int index = 0;

    switch (typeEnum)
    {
    case bgt::PF:

        index = 0;
        break;

    case bgt::LN:

        index = 1;
        break;

    case bgt::VG:

        index = 2;
        break;

    case bgt::FL:

        index = 3;
        break;
    }

    std::array<unsigned int, 4> actual{countL, countM, countH, countSH};
    std::array<unsigned int, 4> limits{allowedL, allowedM, allowedH, allowedSH};

    if (actual[index]+1>limits[index])
        return false;
    else
        return true;
}

bool QFLW_Battlegroup::checkMandatory() const
{

    bgt typeEnum = type.getVal();

    unsigned int index = 0;

    if (typeEnum==bgt::LN)
    {
        index = 1;
    }
    else if (typeEnum == bgt::VG)
    {
        index = 2;
    }
    else if (typeEnum == bgt::FL)
    {
        index = 3;
    }

    std::array<unsigned int, 4> actual{countL, countM, countH, countSH};

    if (actual[index]>0)
        return true;
    else
        return false;

}

QFleet_BGT QFLW_Battlegroup::getType() const
{
    return type;
}

void QFLW_Battlegroup::on_deleteCardButton_clicked()
{
    this->close();

    flagRemoval(this);
}

void QFLW_Battlegroup::flagRemoval(QFLW_Battlegroup * thisPtr)
{
    QFLW_List * list = (QFLW_List *) this->parent();

    list->removeCard(thisPtr);

}

