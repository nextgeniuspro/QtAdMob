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
    friend class QtAdMobBannerIosProtected;
public:
    QtAdMobBannerIos(QObject* parent = 0);
    virtual ~QtAdMobBannerIos();

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
    
private:
    void onStatusChanged(bool status);
    bool isValid() const;

private:
    QString m_UnitId;
    IQtAdMobBanner::Sizes m_BannerSize;
    QPoint m_Position;
#if defined(__OBJC__)
    __unsafe_unretained QtAdMobBannerDelegate* m_AdMob;
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
