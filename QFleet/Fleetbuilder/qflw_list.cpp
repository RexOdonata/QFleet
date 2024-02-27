#include "qflw_list.h"
#include "qmessagebox.h"
#include "ui_qflw_list.h"

QFLW_List::QFLW_List(QWidget *parent, std::optional<QFleet_List> list) :
    QWidget(parent),
    ui(new Ui::QFLW_List),
    cost(QFleet_Cost("List Cost")),
    mainWindowPtr(parent)
{

    ui->setupUi(this);

    setupWidgets();

    if (list)
    {
        ui->fleetNameEdit->setText(list->getName());

        this->setFaction(list->getFaction());
        this->setPointsLimit(list->getPointsLimit());

        auto battlegroups = list->getCards();

        for (auto& battlegroup : battlegroups)
        {
            // add a new battlegroup widget of the current type
            addBGT(battlegroup.getType());

            auto groups = battlegroup.getGroups();

            // get the group widget we just added
            auto bgc = cards.back();

            for (auto& group : groups)
            {
                bgc->addGroupListPart(group);
            }

            cards.back()->updateCost(false);
        }

        updateCost();
    }


    updateListLimits();


}

void QFLW_List::setupWidgets()
{
    pointsStatusWidget = new limitWidget(this);
    ui->pointsLimitLayout->addWidget(pointsStatusWidget);

    launchStatusWidget = new limitWidget(this);
    ui->launchLimitLayout->addWidget(launchStatusWidget);

    pfStatusWidget = new limitWidget(this);
    ui->pfLimitLayout->addWidget(pfStatusWidget);

    lnStatusWidget = new limitWidget(this);
    ui->lnLimitLayout->addWidget(lnStatusWidget);

    vgStatusWidget = new limitWidget(this);
    ui->vgLimitLayout->addWidget(vgStatusWidget);

    flStatusWidget = new limitWidget(this);
    ui->flLimitLayout->addWidget(flStatusWidget);

}

void QFLW_List::updateListLimits()
{
    pointsStatusWidget->setLimit(pointsLimit);
    launchStatusWidget->setLimit(launchLimit);
    pointsStatusWidget->setValue(this->cost.points);
    launchStatusWidget->setValue(this->cost.LC);
}


QFleet_List QFLW_List::createListPart() const
{
    QFleet_List newList(ui->fleetNameEdit->text(), *this->listFaction, this->pointsLimit);

    for (auto& battlegroup : cards)
    {
        auto cardPart = battlegroup->createListPart();
        newList.addCard(cardPart);
    }

    newList.updateCost();

    return newList;
}


void QFLW_List::slotAdmiralSet(QFLW_Group * val)
{
    // when a new ship is replacing another ship with the admiral
    if (admiralGroup && *admiralGroup != val)
            (*admiralGroup)->removeAdmiral();

    // then replace the admiral group ptr
    // its okay if this is replacing A with A.
    admiralGroup = val;
}

// when the group with the admiral is deleted
void QFLW_List::slotAdmiralDeleted()
{
    admiralGroup.reset();
}


QWidget * QFLW_List::getMainWindowPtr() const
{
    return (QWidget *) mainWindowPtr;
}

QFLW_List::~QFLW_List()
{
    delete ui;
}


void QFLW_List::setFaction(QFleet_Faction set)
{
    listFaction = set;

    ui->factionLabel->setText(listFaction.value().toString());
}

void QFLW_List::setPointsLimit(unsigned int set)
{
    pointsLimit = set;

    unsigned int index = 0;

    if (pointsLimit < 1000)
    {
        maxBattleGroups = 4;
        launchLimit=10;

    }
    else if (pointsLimit < 2000)
    {
        maxBattleGroups = 6;
        launchLimit=15;
        index=1;
    }
    else if (pointsLimit < 3001)
    {
        maxBattleGroups = 7;
        launchLimit=20;
        index=2;
    }
    else
    {
        qFatal("List size too big!");
    }

    allowedL=cardLimitMatrix[4*index];
    allowedM=cardLimitMatrix[4*index + 1];
    allowedH=cardLimitMatrix[4*index + 2];
    allowedSH=cardLimitMatrix[4*index + 3];

    pointsStatusWidget->setLimit(pointsLimit);

    launchStatusWidget->setLimit(launchLimit);

    pfStatusWidget->setLimit(allowedL);
    lnStatusWidget->setLimit(allowedM);
    vgStatusWidget->setLimit(allowedH);
    flStatusWidget->setLimit(allowedSH);


}

void QFLW_List::updateHeader()
{
    pfStatusWidget->setValue(countL);
    lnStatusWidget->setValue(countM);
    vgStatusWidget->setValue(countH);
    flStatusWidget->setValue(countSH);

    pointsStatusWidget->setValue(cost.points);

    launchStatusWidget->setValue(cost.LC);
}

const std::array<unsigned int, 12> QFLW_List::cardLimitMatrix =
    {
        2,2,1,0,
        2,3,2,1,
        3,4,3,2
};

void QFLW_List::updateCost()
{
    cost.zero();

    for (auto cardPtr : cards)
    {
        cost + cardPtr->getCost();
    }

    updateHeader();
}

bool QFLW_List::canAdd(QFleet_BGT bgType) const
{
    unsigned int index = bgType.convertToIndex();

    std::array<unsigned int, 4> actual{countL, countM, countH, countSH};
    std::array<unsigned int, 4> limits{allowedL, allowedM, allowedH, allowedSH};

    if (actual[index]+1>limits[index])
        return false;
    else
        return true;
}

unsigned int QFLW_List::getBGN(QFleet_BGT bgType) const
{
    switch (bgType.getVal())
    {
    case bgt::PF:

        return countL;
        break;

    case bgt::LN:

        return countM;
        break;

    case bgt::VG:

        return countH;
        break;

    case bgt::FL:

        return countSH;
        break;
    }

    return 0;
}

void QFLW_List::addBGT(QFleet_BGT type)
{
    if (canAdd(type))
    {
        switch (type.getVal())
        {
            case bgt::PF:
                countL++;
            break;

            case bgt::LN:
                countM++;
            break;

            case bgt::VG:
                countH++;
            break;

            case bgt::FL:
                countSH++;
            break;
        }

            QPointer<QFLW_Battlegroup> newBG = new QFLW_Battlegroup(this, type);

            cards.push_back(newBG.data());

            ui->cardLayout->addWidget(newBG.data());

            updateHeader();
    }
    else
    {
        QMessageBox msg(this);
        msg.setText("Cannot add a Battlegroup of this type");
        msg.exec();
    }
}

void QFLW_List::removeBGT(QFleet_BGT type)
{
    switch (type.getVal())
    {
    case bgt::PF:
        countL--;
        break;

    case bgt::LN:
        countM--;
        break;

    case bgt::VG:
        countH--;
        break;

    case bgt::FL:
        countSH--;
        break;
    }
}

void QFLW_List::on_addPF_Button_clicked()
{
    addBGT(QFleet_BGT(bgt::PF));
}


void QFLW_List::on_addLN_Button_clicked()
{
  addBGT(QFleet_BGT(bgt::LN));
}


void QFLW_List::on_addVG_Button_clicked()
{
    addBGT(QFleet_BGT(bgt::VG));
}


void QFLW_List::on_addFL_Button_clicked()
{
    addBGT(QFleet_BGT(bgt::FL));
}

void QFLW_List::removeCard(QFLW_Battlegroup * cardPtr)
{
    auto index = 0;
    for (auto card : cards)
    {
        if (card.data() == cardPtr)
        {
            cards.remove(index);
            QFleet_BGT type = card->getType();
            removeBGT(type);

        }


        index++;
    }

    updateCost();
}

