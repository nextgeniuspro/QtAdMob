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

    virtual void SetUnitId(const QString& unitId);
    virtual void SetSize(BannerSize size);
    virtual QSize GetSizeInPixels();
    virtual void SetPosition(const QPoint& position);
    virtual bool IsShow() const;
    virtual bool IsLoaded() const;
    virtual void Show();
    virtual void Hide();

    virtual void AddTestDevice(const QString& hashedDeviceId);

    // For internal purpose only
    void OnLoad(bool status);
    
private:
    bool IsValid() const;

private:
#if defined(__OBJC__)
    QtAdMobBannerDelegate* m_AdMob;
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
