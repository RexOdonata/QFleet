#ifndef LISTPRINTER_H
#define LISTPRINTER_H

#include "NLTemplate.h"


#include "../ListParts/qfleet_list.h"

class listPrinter
{
public:
    listPrinter() = delete;

    static std::string getHTML(const QFleet_List&);

private:

    static std::string getTimeStamp();

    static void fillGroupBlocks(NL::Template::Node&, const QVector<QFleet_Group>&);

    static void fillWeaponTable(NL::Template::Node&, const QVector<QFleet_Weapon>&);

    static void fillLaunchTable(NL::Template::Node&, const QVector<QFleet_launchProfile>&);

};

#endif // LISTPRINTER_H
