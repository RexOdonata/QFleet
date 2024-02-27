#include "qfp_strategycard.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFP_StrategyCard w;
    w.show();
    return a.exec();
}
