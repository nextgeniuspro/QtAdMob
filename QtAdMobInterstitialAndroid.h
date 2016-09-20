#ifndef QTADMOBINTERSTITIALANDROID_H
#define QTADMOBINTERSTITIALANDROID_H

#include "IQtAdMobInterstitial.h"

#if (__ANDROID_API__ >= 9)

class QAndroidJniObject;

class QtAdMobInterstitialAndroid : public IQtAdMobInterstitial
{
public:
    QtAdMobInterstitialAndroid();
    virtual ~QtAdMobInterstitialAndroid();

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
    
    /*
     * For internal purpose only
     */
    typedef QMap<uint32_t, QtAdMobInterstitialAndroid*> TInstances;
    static const TInstances& Instances();

private:
    bool isValid() const;

private:
    QString m_UnitId;
    QAndroidJniObject* m_Activity;
    int m_Index;
    static int s_Index;
    static TInstances s_Instances;
};

#endif // __ANDROID_API__

#endif // QTADMOBINTERSTITIALANDROID_H
