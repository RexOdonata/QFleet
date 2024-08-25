#include "hangar.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Hangar w;
    w.show();
    return a.exec();
}
