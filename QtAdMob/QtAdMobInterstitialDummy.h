#ifndef QTADMOBINTERSTITIALDUMMY_H
#define QTADMOBINTERSTITIALDUMMY_H

#include "IQtAdMobInterstitial.h"

class QtAdMobInterstitialDummy : public IQtAdMobInterstitial
{
public:
    QtAdMobInterstitialDummy();
    virtual ~QtAdMobInterstitialDummy();

    virtual void LoadWithUnitId(const QString& unitId);
    virtual bool IsLoaded() const;
    virtual void Show();

    virtual void AddTestDevice(const QString& hashedDeviceId);
};

#endif // QTADMOBINTERSTITIALDUMMY_H
