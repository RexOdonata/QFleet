#include "listprinter_short.h"

#include <iomanip>
#include <ctime>

std::string listPrinter_Short::getTimeStamp()
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;

    oss<<std::put_time(&tm, "%d-%m-%Y %H-%M-%S");

    return oss.str();
}

std::string listPrinter_Short::getHTML(const QFleet_List& listObj)
{

    NL::Template::LoaderFile templateLoader;

    NL::Template::Template listTemplate(templateLoader);

    listTemplate.load("htmlTemplates/listDetailShort.txt");

    // set list name in header

    listTemplate.set("listName",listObj.name.toStdString());

    // set points fraction in header

    std::string pointsStr = QString::number(listObj.getCost().points).toStdString() + "/" + QString::number(listObj.getPointsLimit()).toStdString();

    listTemplate.set("listPoints",pointsStr);

    // set launch fraction in header

    std::string launchStr = QString::number(listObj.getCost().LC).toStdString() + "/" + QString::number(listObj.getLaunchLimit()).toStdString();

    listTemplate.set("listLaunch",launchStr);

    // set faction in header

    std::string factionStr = QFleet_Faction(listObj.getFaction()).toString().toStdString();

    listTemplate.set("listFaction",factionStr);

    // set creation time

    std::string timestampStr = listPrinter_Short::getTimeStamp();

    listTemplate.set("listCreated",timestampStr);

    // set Validity Tag (NEEDS WORK!)

    listTemplate.set("listvalid","?");


    // start drawing battlegroups

    auto battlegroupsCount = listObj.getCards().size();

    listTemplate.block("battlegroup").repeat(battlegroupsCount);

    auto cards = listObj.getCards();

    QMap<QString, QFleet_Ship_Fleet> shipMap;

    // draw the list tree
    for (int cardIndex = 0; cardIndex < cards.size(); cardIndex++)
    {
        auto card = cards.at(cardIndex);

        listTemplate.block("battlegroup")[cardIndex].set("cardName",card.name.toStdString());
        listTemplate.block("battlegroup")[cardIndex].set("SR",QString::number(card.getCost().SR).toStdString());

        if (card.hasMultigroup())
            card.reduceGroups();

        auto groups = card.getGroups();

        NL::Template::Block& groupBlockRef = listTemplate.block("battlegroup")[cardIndex].block("group");

        fillGroupLines(groupBlockRef, groups);

        // build present groups
        for (auto& group : groups)
            if (!shipMap.contains(group.getShip().name))
                shipMap.insert(group.name, group.getShip());

    }

    // print all present ships
    NL::Template::Block& shipBlock = listTemplate.block("ship");

    QVector<QFleet_Ship_Fleet> shipsVec;
    shipsVec.reserve(shipMap.size());

    for (auto& ship : shipMap)
        shipsVec.push_back(ship);

    fillShipBlocks(shipBlock, shipsVec);

    std::stringbuf buffer;

    std::ostream sout(&buffer);

    listTemplate.render(sout);

    std::ostringstream oss;

    oss << buffer.str();

    return oss.str();
}

void listPrinter_Short::fillShipBlocks(NL::Template::Block& block, const QVector<QFleet_Ship_Fleet> &shipVec)
{
    block.repeat(shipVec.size());


    for (auto index = 0; index < shipVec.size(); index++)
    {
        auto ship = shipVec[index];

        block[index].set("shipCost", QString::number(ship.points).toStdString());

        block[index].set("cost", QString::number(ship.points).toStdString());

        block[index].set("shipName", ship.name.toStdString());

        block[index].set("scan", QString::number(ship.scan).toStdString());

        block[index].set("signature", ship.getSigString().toStdString());

        block[index].set("thrust", QString::number(ship.thrust).toStdString());

        block[index].set("hull", QString::number(ship.hull).toStdString());

        block[index].set("armor", ship.getArmorString().toStdString());

        block[index].set("pd", QString::number(ship.PD).toStdString());

        block[index].set("group", ship.getGroupString().toStdString());

        block[index].set("tonnage", ship.tonnage.toString().toStdString());

        block[index].set("special", ship.getSpecialString().toStdString());

        NL::Template::Block& weaponRowBlock = block[index].block("weaponRow");

        NL::Template::Block& launchTableBlock = block[index].block("launchTable");

        fillWeaponTable(weaponRowBlock, ship.weapons);

        fillLaunchTable(launchTableBlock, ship.launch);

    }


}

void listPrinter_Short::fillWeaponTable(NL::Template::Block& weaponRowBlock, const QVector<QFleet_Weapon>& weapons)
{
    weaponRowBlock.repeat(weapons.size());

    for (int weaponIndex = 0; weaponIndex < weapons.size(); weaponIndex++)
    {
        auto weapon = weapons.at(weaponIndex);

        weaponRowBlock[weaponIndex].set("weaponName",weapon.name.toStdString());

        weaponRowBlock[weaponIndex].set("weaponArc",weapon.facing.toString().toStdString());

        weaponRowBlock[weaponIndex].set("weaponDamage",weapon.damage.toStdString());

        weaponRowBlock[weaponIndex].set("weaponAttack",weapon.attacks.toStdString());

        weaponRowBlock[weaponIndex].set("weaponLock",weapon.lock.toString().toStdString());

        weaponRowBlock[weaponIndex].set("weaponSpecial", weapon.getSpecialString().toStdString());
    }
}

void listPrinter_Short::fillLaunchTable(NL::Template::Block& launchTableBlock, const QVector<QFleet_launchProfile>& launch)
{
    if (launch.size() == 0)
    {
        launchTableBlock.disable();
        launchTableBlock.block("launchRow").disable();
    }
    else
    {

        launchTableBlock.block("launchRow").repeat(launch.size());

        for (int launchIndex = 0; launchIndex < launch.size(); launchIndex++)
        {
            auto lp = launch.at(launchIndex);

            launchTableBlock.block("launchRow")[launchIndex].set("launchName",lp.getAssetString().toStdString());

            launchTableBlock.block("launchRow")[launchIndex].set("launchCount",QString::number(lp.getCount()).toStdString());

            std::string limStr = "-";

            if (lp.getLimited())
                limStr = QString::number(lp.getLimited()).toStdString();

            launchTableBlock.block("launchRow")[launchIndex].set("launchLimited",limStr);
        }
    }

}

void listPrinter_Short::fillGroupLines(NL::Template::Block& block, const QVector<QFleet_Group>& groups)
{
    block.repeat(groups.size());

    for (int i = 0; i<groups.size(); i++)
    {
        auto group = groups.at(i);
        block[i].set("count",QString::number(group.getNumber()).toStdString());
        block[i].set("shipName",group.name.toStdString());

        QString admStr = "";

        if (group.getAdmiral())
            admStr=QString(" + Lv%1 admiral").arg(QString::number(group.getAdmiral()));

        block[i].set("admiral",admStr.toStdString());
    }
}
