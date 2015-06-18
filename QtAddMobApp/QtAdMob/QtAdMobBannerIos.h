#ifndef QTADMOBBANNERIOS_H
#define QTADMOBBANNERIOS_H

#include "IQtAdMobBanner.h"

#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)

#include <QStringList>

class QAndroidJniObject;
#if defined(__OBJC__)
@class QtAdMobBannerDelegate;
#endif

class QtAdMobBannerIos : public IQtAdMobBanner
{
public:
    QtAdMobBannerIos();
    virtual ~QtAdMobBannerIos();

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

    // For internal purpose only
    void OnLoad(bool status);
    
private:
    bool IsValid() const;

private:
#if defined(__OBJC__)
    QtAdMobBannerDelegate* m_Delegate;
#endif
    enum LoadingState
    {
        Idle = 0,
        Loading,
        Loaded
    };
    
    LoadingState m_LoadingState;
};

#endif // TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR

#endif // QTADMOBBANNERIOS_H
