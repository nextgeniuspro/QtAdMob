#ifndef QTADMOBBANNERANDROID_H
#define QTADMOBBANNERANDROID_H

#include "IQtAdMobBanner.h"

#if (__ANDROID_API__ >= 9)

class QAndroidJniObject;

class QtAdMobBannerAndroid : public IQtAdMobBanner
{
public:
    QtAdMobBannerAndroid();
    virtual ~QtAdMobBannerAndroid();

    /*
     * Configure banner id
     */
    virtual void setUnitId(const QString& unitId);

    /*
     * Retrive banner id
     */
    virtual const QString& unitId() const;

    /*
     * Setup preconfigured banner size
     */
    virtual void setSize(Sizes size);

    /*
     * Retrieve banner size
     */
    virtual Sizes size() const;

    /*
     * Get real banner size in pixels
     */
    virtual QSize sizeInPixels();

    /*
     * Setup banner position
     */
    virtual void setPosition(const QPoint& position);

    /*
     * Retrieve banner position
     */
    virtual const QPoint& position() const;

    /*
     * Show banner
     */
    virtual void setVisible(bool isVisible);

    /*
     * Is banner showed
     */
    virtual bool visible();

    /*
     * Is banner loaded
     */
    virtual bool isLoaded();

    /*
     * Add test device identifier
     */
    void addTestDevice(const QString& hashedDeviceId);

    /*
     * For internal purpose only
     */
    typedef QMap<uint32_t, QtAdMobBannerAndroid*> TInstances;
    static const TInstances& Instances();

private:
    bool isValid() const;

private:
    QString m_UnitId;
    IQtAdMobBanner::Sizes m_BannerSize;
    QPoint m_Position;
    QAndroidJniObject* m_Activity;
    int m_Index;
    static int s_Index;
    static TInstances s_Instances;
};

#endif // __ANDROID_API__

#endif // QTADMOBBANNERANDROID_H
