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

    virtual void SetUnitId(const QString& unitId);
    virtual void SetSize(BannerSize size);
    virtual QSize GetSizeInPixels();
    virtual void SetPosition(const QPoint& position);
    virtual bool IsShow() const;
    virtual bool IsLoaded() const;
    virtual void Show();
    virtual void Hide();

    virtual void AddTestDevice(const QString& hashedDeviceId);
};

#endif // QTADMOBBANNERDUMMY_H
