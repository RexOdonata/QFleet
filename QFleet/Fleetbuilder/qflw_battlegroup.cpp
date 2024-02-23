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

QWidget * QFLW_Battlegroup::getListPtr() const
{
    return (QWidget *)listWidgetPtr;
}

QFLW_Battlegroup::QFLW_Battlegroup(QWidget *parent, std::optional<QFleet_BGT> setType) :
    QWidget(parent),
    ui(new Ui::QFLW_Battlegroup),
    cost(QFleet_Cost("Card Cost")),
    type(*setType),
    listWidgetPtr(parent)
{
    ui->setupUi(this);


    QFLW_List * listPtr = (QFLW_List *)listWidgetPtr;
    MainWindow * mainWindowPtr = (MainWindow *) listPtr->getMainWindowPtr();


    QObject::connect(this, &QFLW_Battlegroup::querySelectedShip,
            mainWindowPtr , &MainWindow::slotShipPull);


    QObject::connect(mainWindowPtr , &MainWindow::sendSelectedShip,
            this, &QFLW_Battlegroup::recieveSelectedShip);


    ui->typeLabel->setText(type.toLongString());

    QString tempName = type.toLongString() + " " + QString::number((listPtr->getBGN(*setType)));

    ui->nameEdit->setText(tempName);

    refreshCostLabels();

    unsigned int index = setType.value().convertToIndex();

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
    QFleet_BGT shipBGT = tonnageVal.convertToBGT();

    // convert to index
    unsigned int index = shipBGT.convertToIndex();

    std::array<unsigned int, 4> actual{countL, countM, countH, countSH};
    std::array<unsigned int, 4> limits{allowedL, allowedM, allowedH, allowedSH};

    if (actual[index]+1>limits[index])
        return false;
    else
        return true;
}

bool QFLW_Battlegroup::checkMandatory() const
{

    unsigned int index = type.convertToIndex();

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

