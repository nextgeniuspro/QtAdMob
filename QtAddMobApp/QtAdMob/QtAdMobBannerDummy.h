#ifndef QTADMOBBANNERDUMMY_H
#define QTADMOBBANNERDUMMY_H

#include "IQtAdMobBanner.h"

class QtAdMobBannerDummy : public IQtAdMobBanner
{
public:
    QtAdMobBannerDummy();
    virtual ~QtAdMobBannerDummy();

    virtual void Initialize();
    virtual void Shutdown();

    virtual void SetAdUnitId(const QString& unitId);
    virtual void SetAdSize(BannerSize size);
    virtual void SetPosition(const QPoint& position);
    virtual QSize GetDimensions();
    virtual bool IsShowed() const;
    virtual bool IsLoaded() const;
    virtual void ShowAd();
    virtual void HideAd();

    virtual void AddTestDevice(const QString& hashedDeviceId);
};

#endif // QTADMOBBANNERDUMMY_H
