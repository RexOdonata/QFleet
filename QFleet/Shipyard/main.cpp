#include "shipyard.h"

#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Shipyard w;
    w.show();
    return a.exec();
}
