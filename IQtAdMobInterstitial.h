#ifndef IQTADMOBINTERSTITIAL_H
#define IQTADMOBINTERSTITIAL_H

#include <QObject>
#include <QString>
#include <QSize>
#include <QPoint>

class IQtAdMobInterstitial : public QObject
{
    Q_OBJECT
public:
    IQtAdMobInterstitial() {}
    virtual ~IQtAdMobInterstitial() {}

    /*
     * Setup unit id and start caching interstitial for that id
     */
    virtual void setUnitId(const QString& unitId) = 0;

    /*
     * Retrive interstitial id
     */
    virtual const QString& unitId() const = 0;

    /*
     * If interstitial has already loaded it will be presented, another
     * case it will be showed after loading finished
     */
    virtual void setVisible(bool isVisible) = 0;

    /*
     * Is interstitial visible
     */
    virtual bool visible() = 0;

    /*
     * Check if interstitial loaded
     */
    virtual bool isLoaded() = 0;

    /*
     * Add test device identifier. Device identifier you can find in output log, on Android
     * it will looks like 'Ads : Use AdRequest.Builder.addTestDevice("device id") to get test ads on this device.'
     * iOS: // TODO:
     */
    virtual void addTestDevice(const QString& hashedDeviceId) = 0;

signals:
    void loaded();
    void loading();
    void willPresent();
    void closed();
    void clicked();
};

#endif // IQTADMOBINTERSTITIAL_H

