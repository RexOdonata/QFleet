#ifndef OPTSELECT_H
#define OPTSELECT_H

#include <QDialog>

#include "../Components/qfleet_ship_shipyard.h"


#include "../common/dvs_widget.h"

namespace Ui {
class optSelect;
}

class optSelect : public QDialog
{
    Q_OBJECT

public:
    explicit optSelect(QWidget *parent = nullptr, const QFleet_Ship_Shipyard * refShip = NULL , QVector<QFleet_Option> * setOptionList = NULL);
    ~optSelect();

private slots:
    void on_addOptionButton_clicked();

    void on_removeOptionButton_clicked();

    void on_saveOptionsButton_clicked();

private:
    Ui::optSelect *ui;

    dvs_Data<QFleet_Option, dvs_Widget> * selectOptionsRoster;
    dvs_Widget * selectedOptionWidget;

    QVector<QFleet_Option> * optionList = NULL;

    // stores all options passed in from the source ship, used to get the options from the string that comes back from the table select
    QMap<QString, QFleet_Option> optMap;

    bool checkAdd(const QFleet_Option&, QString&);

    void updateCounts();

    unsigned int broadsideLimit;
    unsigned int broadsideCount;
    unsigned int minOptions;
    unsigned int maxOptions;

};

#endif // OPTSELECT_H
