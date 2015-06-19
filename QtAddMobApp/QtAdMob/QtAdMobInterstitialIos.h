#ifndef QTADMOBINTERSTITIALIOS_H
#define QTADMOBINTERSTITIALIOS_H

#include "IQtAdMobInterstitial.h"

#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)

class QAndroidJniObject;
#if defined(__OBJC__)
@class QtAdMobInterstitialDelegate;
#endif

class QtAdMobInterstitialIos : public IQtAdMobInterstitial
{
public:
    QtAdMobInterstitialIos();
    virtual ~QtAdMobInterstitialIos();

    virtual void LoadWithAdUnitId(const QString& unitId);
    virtual bool IsLoaded() const;
    virtual void ShowAd();

    virtual void AddTestDevice(const QString& hashedDeviceId);

    // For internal purpose only
    void OnLoad(bool status);
    
private:
    bool IsValid() const;

private:
#if defined(__OBJC__)
    QtAdMobInterstitialDelegate* m_Delegate;
#endif
    bool m_IsNeedToShow;
};

#endif // TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR

#endif // QTADMOBINTERSTITIALIOS_H
