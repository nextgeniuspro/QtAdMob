#ifndef QTADMOBINTERSTITIAL_H
#define QTADMOBINTERSTITIAL_H

#include "QtAdMobInterstitialAndroid.h"
#include "QtAdMobInterstitialDummy.h"
#include "QtAdMobInterstitialIos.h"

inline IQtAdMobInterstitial* CreateQtAdMobInterstitial()
{
#if (__ANDROID_API__ >= 9)
    return new QtAdMobInterstitialAndroid();
#elif (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    return new QtAdMobInterstitialIos();
#else
    return new QtAdMobInterstitialDummy();
#endif
}

class QmlAdMobInterstitial : public QObject
{
    Q_PROPERTY(QString unitId READ unitId WRITE setUnitId NOTIFY unitIdChanged)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(bool isLoaded READ isLoaded NOTIFY loaded)

    Q_OBJECT
public:
    QmlAdMobInterstitial();
    ~QmlAdMobInterstitial();

    /*
     * Call it before loading qml
     */
    static void DeclareQML();

    /*
     * Setup unit id and start caching interstitial for that id
     */
    void setUnitId(const QString& unitId);

    /*
     * Retrive interstitial id
     */
    const QString& unitId() const;

    /*
     * If interstitial has already loaded it will be presented, another
     * case it will be showed after loading finished
     */
    void setVisible(bool isVisible);

    /*
     * Is interstitial visible
     */
    bool visible();

    /*
     * Check if interstitial loaded
     */
    bool isLoaded();

    /*
     * Add test device identifier. Device identifier you can find in output log, on Android
     * it will looks like 'Ads : Use AdRequest.Builder.addTestDevice("device id") to get test ads on this device.'
     * iOS: // TODO:
     */
    Q_INVOKABLE void addTestDevice(const QString& hashedDeviceId);

signals:
    void unitIdChanged();
    void visibleChanged();
    void loaded();
    void loading();
    void willPresent();
    void closed();
    void clicked();

private:
    IQtAdMobInterstitial* QML() const;

private:
    IQtAdMobInterstitial* m_Instance;
};

#endif // QTADMOBINTERSTITIAL_H

