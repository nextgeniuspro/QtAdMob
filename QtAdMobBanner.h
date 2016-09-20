#ifndef QTADMOBBANNER_H
#define QTADMOBBANNER_H

#include "QtAdMobBannerAndroid.h"
#include "QtAdMobBannerIos.h"
#include "QtAdMobBannerDummy.h"

inline IQtAdMobBanner* CreateQtAdMobBanner()
{
#if (__ANDROID_API__ >= 9)
    return new QtAdMobBannerAndroid();
#elif (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    return new QtAdMobBannerIos();
#else
    return new QtAdMobBannerDummy();
#endif
}

class QmlAdMobBanner : public QObject
{
    Q_PROPERTY(QString unitId READ unitId WRITE setUnitId NOTIFY unitIdChanged)
    Q_PROPERTY(Sizes size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(QSize sizeInPixels READ sizeInPixels NOTIFY sizeChanged)
    Q_PROPERTY(int width READ width NOTIFY sizeChanged)
    Q_PROPERTY(int height READ height NOTIFY sizeChanged)
    Q_PROPERTY(QPoint position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(int x READ x WRITE setX NOTIFY positionChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY positionChanged)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(bool isLoaded READ isLoaded NOTIFY loaded)

    Q_OBJECT
public:
    enum Sizes
    {
        Banner = 0,
        FullBanner,
        LargeBanner,
        MediumRectangle,
        SmartBanner,
        WideSkyscraper
    };
    Q_ENUMS(Sizes)

    QmlAdMobBanner();
    ~QmlAdMobBanner();

    /*
     * Call it before loading qml
     */
    static void DeclareQML();

    /*
     * Configure banner id
     */
    void setUnitId(const QString& unitId);

    /*
     * Retrive banner id
     */
    const QString& unitId() const;

    /*
     * Setup preconfigured banner size
     */
    void setSize(Sizes size);

    /*
     * Retrieve banner size
     */
    Sizes size() const;

    /*
     * Get real banner size in pixels
     */
    QSize sizeInPixels();

    /*
     * Get banner width in pixels
     */
    int width();

    /*
     * Get banner height in pixels
     */
    int height();

    /*
     * Setup banner position
     */
    void setPosition(const QPoint& position);

    /*
     * Retrieve banner position
     */
    const QPoint& position() const;

    /*
     * Set X position
     */
    void setX(int x);

    /*
     * Get X position
     */
    int x();

    /*
     * Set Y position
     */
    void setY(int y);

    /*
     * Get Y position
     */
    int y();

    /*
     * Show banner
     */
    void setVisible(bool isVisible);

    /*
     * Is banner showed
     */
    bool visible();

    /*
     * Is banner loaded
     */
    bool isLoaded();

    /*
     * Add test device identifier
     */
    Q_INVOKABLE void addTestDevice(const QString& hashedDeviceId);

signals:
    void unitIdChanged();
    void sizeChanged();
    void positionChanged();
    void visibleChanged();
    void loaded();
    void loading();
    void closed();
    void clicked();

private:
    IQtAdMobBanner* QML() const;

private:
    IQtAdMobBanner* m_Instance;
};

#endif // QTADMOBBANNER_H

