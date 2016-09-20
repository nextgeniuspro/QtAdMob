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
    friend class QtAdMobInterstitialIosProtected;
public:
    QtAdMobInterstitialIos();
    virtual ~QtAdMobInterstitialIos();

    /*
     * Setup unit id and start caching interstitial for that id
     */
    virtual void setUnitId(const QString& unitId);

    /*
     * Retrive interstitial id
     */
    virtual const QString& unitId() const;

    /*
     * If interstitial has already loaded it will be presented, another
     * case it will be showed after loading finished
     */
    virtual void setVisible(bool isVisible);

    /*
     * Is interstitial visible
     */
    virtual bool visible();

    /*
     * Check if interstitial loaded
     */
    virtual bool isLoaded();

    /*
     * Add test device identifier. Device identifier you can find in output log, on Android
     * it will looks like 'Ads : Use AdRequest.Builder.addTestDevice("device id") to get test ads on this device.'
     * iOS: // TODO:
     */
    virtual void addTestDevice(const QString& hashedDeviceId);

private:
    void onStatusChanged(bool status);
    bool isValid() const;

private:
    QString m_UnitId;
#if defined(__OBJC__)
    __unsafe_unretained QtAdMobInterstitialDelegate* m_AdMob;
#endif
    bool m_IsNeedToShow;
};

#endif // TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR

#endif // QTADMOBINTERSTITIALIOS_H
