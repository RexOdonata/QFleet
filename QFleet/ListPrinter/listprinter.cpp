#include "listprinter.h"

#include "NLTemplate.h"

#include <iomanip>
#include <ctime>


std::string listPrinter::getTimeStamp()
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;

    oss<<std::put_time(&tm, "%d-%m-%Y %H-%M-%S");

    return oss.str();
}

std::string listPrinter::getHTML(const QFleet_List& listObj)
{

    NL::Template::LoaderFile templateLoader;

    NL::Template::Template listTemplate(templateLoader);

    listTemplate.load("htmlTemplates/listDetail.txt");

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

    std::string timestampStr = listPrinter::getTimeStamp();

    listTemplate.set("listCreated",timestampStr);

    // set Validity Tag (NEEDS WORK!)

    listTemplate.set("listvalid","?");


    // start drawing battlegroups

    auto battlegroupsCount = listObj.getCards().size();

    listTemplate.block("battleGroup").repeat(battlegroupsCount);

    auto cards = listObj.getCards();

    for (int cardIndex = 0; cardIndex < cards.size(); cardIndex++)
    {
        auto card = cards.at(cardIndex);

        // set header info for the battlegroup

        listTemplate.block("battleGroup")[cardIndex].set("cardName",card.name.toStdString());

        listTemplate.block("battleGroup")[cardIndex].set("cardSR",QString::number(card.getCost().SR).toStdString());

        // get a reference to to the current group block
        NL::Template::Block& groupProfiles = listTemplate.block("battleGroup")[cardIndex].block("group");

        auto groups = card.getGroups();

        // fill out the group
        fillGroupBlocks(groupProfiles, groups);

    }

    std::stringbuf buffer;

    std::ostream sout(&buffer);

    listTemplate.render(sout);

    std::ostringstream oss;

    oss << buffer.str();

    return oss.str();
}

void listPrinter::fillGroupBlocks(NL::Template::Block& groupBlockRef, const QVector<QFleet_Group>& groups)
{
    groupBlockRef.repeat(groups.size());

    for (int groupIndex = 0; groupIndex < groups.size(); groupIndex++)
    {
        auto group = groups.at(groupIndex);

        groupBlockRef[groupIndex].set("count", QString::number(group.getNumber()).toStdString());

        std::string admiralStr = "";

        if (group.getAdmiral())
        {
            admiralStr = "Lvl ";
            admiralStr.append(QString::number(group.getAdmiral()).toStdString());
            admiralStr.append(" Admiral");
        }

        auto ship = group.getShip();

        groupBlockRef[groupIndex].set("shipCost", QString::number(ship.points).toStdString());

        groupBlockRef[groupIndex].set("cost", QString::number(group.getCost().points).toStdString());

        groupBlockRef[groupIndex].set("admiral", admiralStr);

        groupBlockRef[groupIndex].set("shipName", ship.name.toStdString());

        groupBlockRef[groupIndex].set("scan", QString::number(ship.scan).toStdString());

        groupBlockRef[groupIndex].set("signature", ship.getSigString().toStdString());

        groupBlockRef[groupIndex].set("thrust", QString::number(ship.thrust).toStdString());

        groupBlockRef[groupIndex].set("hull", QString::number(ship.hull).toStdString());

        groupBlockRef[groupIndex].set("armor", ship.getArmorString().toStdString());

        groupBlockRef[groupIndex].set("pd", QString::number(ship.PD).toStdString());

        groupBlockRef[groupIndex].set("group", ship.getGroupString().toStdString());

        groupBlockRef[groupIndex].set("tonnage", ship.tonnage.toString().toStdString());

        groupBlockRef[groupIndex].set("special", ship.getSpecialString().toStdString());

        NL::Template::Block& weaponRowBlock = groupBlockRef[groupIndex].block("weaponRow");

        NL::Template::Block& launchTableBlock = groupBlockRef[groupIndex].block("launchTable");

        fillWeaponTable(weaponRowBlock, ship.weapons);

        fillLaunchTable(launchTableBlock, ship.launch);
    }
}

void listPrinter::fillWeaponTable(NL::Template::Block& weaponRowBlock, const QVector<QFleet_Weapon>& weapons)
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

void listPrinter::fillLaunchTable(NL::Template::Block& launchTableBlock, const QVector<QFleet_launchProfile>& launch)
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

            launchTableBlock.block("launchRow")[launchIndex].set("launchName",lp.name.toStdString());

            launchTableBlock.block("launchRow")[launchIndex].set("launchCount",QString::number(lp.getCount()).toStdString());

            std::string limStr = "-";

            if (lp.getLimited())
                limStr = QString::number(lp.getLimited()).toStdString();

            launchTableBlock.block("launchRow")[launchIndex].set("launchLimited",limStr);
        }
    }


}
