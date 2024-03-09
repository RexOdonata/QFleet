#ifndef LISTPRINTER_LEGACY_H
#define LISTPRINTER_LEGACY_H

#include "NLTemplate.h"


#include "../ListParts/qfleet_list.h"

class listPrinter_Legacy
{
public:
    listPrinter_Legacy() = delete;

    static std::string getHTML(const QFleet_List&);

private:

    static std::string getTimeStamp();

    static void fillGroupBlocks(NL::Template::Block&, const QVector<QFleet_Group>&);

    static void fillWeaponTable(NL::Template::Block&, const QVector<QFleet_Weapon>&);

    static void fillLaunchTable(NL::Template::Block&, const QVector<QFleet_launchProfile>&);

};

#endif // LISTPRINTER_LEGACY_H
