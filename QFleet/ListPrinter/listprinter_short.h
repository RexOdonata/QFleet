#ifndef LISTPRINTER_SHORT_H
#define LISTPRINTER_SHORT_H

#include "../ListParts/qfleet_list.h"
#include "NLTemplate.h"


class listPrinter_Short
{

public:
    listPrinter_Short() = delete;

    static std::string getHTML(const QFleet_List&);

private:

    static std::string getTimeStamp();

    static void fillGroupLines(NL::Template::Block&, const QVector<QFleet_Group>&);

    static void fillShipBlocks(NL::Template::Block&, const QVector<QFleet_Ship_Fleet>&);

    static void fillWeaponTable(NL::Template::Block&, const QVector<QFleet_Weapon>&);

    static void fillLaunchTable(NL::Template::Block&, const QVector<QFleet_launchProfile>&);
};

#endif // LISTPRINTER_SHORT_H
