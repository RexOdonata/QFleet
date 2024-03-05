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

        listTemplate.block("battleGroup")[cardIndex].set("sr",QString::number(card.getCost().SR).toStdString());

        // get a reference to to the current group block
        auto groupProfiles = listTemplate.block("battleGroup")[cardIndex];

        auto groups = card.getGroups();

        // fill out the groups within the battlegroup
        fillGroupBlocks(groupProfiles, groups);

    }

    std::stringbuf buffer;

    std::ostream sout(&buffer);

    listTemplate.render(sout);

    std::ostringstream oss;

    oss << buffer.str();

    return oss.str();
}

void listPrinter::fillGroupBlocks(NL::Template::Block& blockRef, const QVector<QFleet_Group>& groups)
{
    blockRef.block("group").repeat(groups.size());

    for (int groupIndex = 0; groupIndex < groups.size(); groupIndex++)
    {
        auto group = groups.at(groupIndex);

        blockRef.block("group")[groupIndex].set("count", QString::number(group.getNumber()).toStdString());

        std::string admiralStr = "";

        if (group.getAdmiral())
        {
            admiralStr = "Lvl ";
            admiralStr.append(QString::number(group.getAdmiral()).toStdString());
            admiralStr.append(" Admiral");
        }

        blockRef.block("group")[groupIndex].set("admiral", admiralStr);


        auto ship = group.getShip();

        blockRef.block("group")[groupIndex].set("shipName", ship.name.toStdString());

        blockRef.block("group")[groupIndex].set("scan", QString::number(ship.scan).toStdString());

        blockRef.block("group")[groupIndex].set("signature", ship.getSigString().toStdString());

        blockRef.block("group")[groupIndex].set("thrust", QString::number(ship.thrust).toStdString());

        blockRef.block("group")[groupIndex].set("hull", QString::number(ship.hull).toStdString());

        blockRef.block("group")[groupIndex].set("armor", ship.getArmorString().toStdString());

        blockRef.block("group")[groupIndex].set("pd", QString::number(ship.PD).toStdString());

        blockRef.block("group")[groupIndex].set("armor", ship.getGroupString().toStdString());

        blockRef.block("group")[groupIndex].set("tonnage", ship.tonnage.toString().toStdString());

        blockRef.block("group")[groupIndex].set("armor", ship.getSpecialString().toStdString());

        NL::Template::Node& groupRef = blockRef.block("group")[groupIndex];

        fillWeaponTable(groupRef, ship.weapons);

        fillLaunchTable(groupRef, ship.launch);
    }
}

void listPrinter::fillWeaponTable(NL::Template::Block& blockRef, const QVector<QFleet_Weapon>& weapons)
{
    blockRef.block("weaponRow").repeat(weapons.size());

    for (int weaponIndex = 0; weaponIndex < weapons.size(); weaponIndex++)
    {
        auto weapon = weapons.at(weaponIndex);

        blockRef.block("weaponRow").set("weaponName",weapon.name.toStdString());

        blockRef.block("weaponRow").set("weaponArc",weapon.facing.toString().toStdString());

        blockRef.block("weaponRow").set("weaponDamage",weapon.damage.toStdString());

        blockRef.block("weaponRow").set("weaponAttack",weapon.attacks.toStdString());

        blockRef.block("weaponRow").set("weaponLock",weapon.lock.toString().toStdString());

        blockRef.block("weaponRow").set("weaponSpecial", weapon.getSpecialString().toStdString());
    }
}

void listPrinter::fillLaunchTable(NL::Template::Block& blockRef, const QVector<QFleet_launchProfile>& launch)
{
    if (launch.size() == 0)
    {
        blockRef.block("launchTable").disable();
    }
    else
    {
        NL::Template::Node& lTableBlock = blockRef.block("launchTable");
        lTableBlock.block("launchRow").repeat(launch.size());

        for (int launchIndex = 0; launchIndex < launch.size(); launchIndex++)
        {
            auto lp = launch.at(launchIndex);

            lTableBlock.block("launchRow").set("launchName",lp.name.toStdString());

            lTableBlock.block("launchRow").set("launchCount",QString::number(lp.getCount()).toStdString());

            std::string limStr = "-";

            if (lp.getLimited())
                limStr = QString::number(lp.getLimited()).toStdString();
            lTableBlock.block("launchRow").set("launchName",limStr);
        }
    }


}
