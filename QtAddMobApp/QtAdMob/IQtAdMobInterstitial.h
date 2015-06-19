#ifndef IQTADMOBINTERSTITIAL_H
#define IQTADMOBINTERSTITIAL_H

#include <QString>
#include <QSize>
#include <QPoint>

class IQtAdMobInterstitial
{
public:
    IQtAdMobInterstitial() {}
    virtual ~IQtAdMobInterstitial() {}

    virtual void LoadWithUnitId(const QString& unitId) = 0;
    virtual bool IsLoaded() const = 0;
    virtual void Show() = 0;

    virtual void AddTestDevice(const QString& hashedDeviceId) = 0;
};

#endif // IQTADMOBINTERSTITIAL_H

