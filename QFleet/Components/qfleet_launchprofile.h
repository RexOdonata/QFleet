#ifndef QFLEET_LAUNCHPROFILE_H
#define QFLEET_LAUNCHPROFILE_H

#include "qft_component.h"

// Represents a launch profile element of ship stats.
// Does not contain the actual launch stats

class QFleet_launchProfile : public qft_component<QFleet_launchProfile>
{
    friend class qft_component<QFleet_launchProfile>;

public:
    QFleet_launchProfile(const QString setName, const QString setID);

    QFleet_launchProfile(QJsonObject in);

    void setCount(const unsigned int);

    void setStrike(const bool);

    void setLimited(const unsigned int set);

    void setAssetNames(QVector<QString>&);


    inline bool getStrike() const
    {
        return strike;
    }

    inline unsigned int getCount() const
    {
        return count;
    }

    inline unsigned int getLimited() const
    {
        return limited;
    }

    inline QString getAssetString() const
    {
        return assetNames;
    }

protected:

    // VARS
    unsigned int count = 0;
    bool strike = false;
    unsigned int limited = 0;

    QString assetNames;

    const static QString label;
    const static QString field_count;
    const static QString field_strike;
    const static QString field_limited;
    const static QString field_assets;

     //FXs

    void impl_toJson(QJsonObject& json);

};

#endif // QFLEET_LAUNCHPROFILE_H
