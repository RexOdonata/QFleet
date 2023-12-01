#ifndef QFLEET_COST_H
#define QFLEET_COST_H

#include "../Components/qft_component.h"

class QFleet_Cost : public qft_component<QFleet_Cost>
{

    friend class qft_component<QFleet_Cost>;

public:
    QFleet_Cost(QJsonObject);

    QFleet_Cost(const QString);

    unsigned int SR;
    unsigned int points;
    unsigned int LC;

    void operator+(QFleet_Cost const&);

protected:

    void impl_toJson(QJsonObject&);

    const static QString label;
    const static QString field_SR;
    const static QString field_points;
    const static QString field_LC;

};

#endif // QFLEET_COST_H
