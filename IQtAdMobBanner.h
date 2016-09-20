#ifndef IQTADMOBBANNER_H
#define IQTADMOBBANNER_H

#include <QObject>
#include <QString>
#include <QSize>
#include <QPoint>

class IQtAdMobBanner : public QObject
{
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

    IQtAdMobBanner(QObject* parent = 0) : QObject(parent) {}
    virtual ~IQtAdMobBanner() {}

    /*
     * Configure banner id
     */
    virtual void setUnitId(const QString& unitId) = 0;

    /*
     * Retrive banner id
     */
    virtual const QString& unitId() const = 0;

    /*
     * Setup preconfigured banner size
     */
    virtual void setSize(Sizes size) = 0;

    /*
     * Retrieve banner size
     */
    virtual Sizes size() const = 0;

    /*
     * Get real banner size in pixels
     */
    virtual QSize sizeInPixels() = 0;

    /*
     * Setup banner position
     */
    virtual void setPosition(const QPoint& position) = 0;

    /*
     * Retrieve banner position
     */
    virtual const QPoint& position() const = 0;

    /*
     * Show banner
     */
    virtual void setVisible(bool isVisible) = 0;

    /*
     * Is banner showed
     */
    virtual bool visible() = 0;

    /*
     * Is banner loaded
     */
    virtual bool isLoaded() = 0;

    /*
     * Add test device identifier
     */
    virtual void addTestDevice(const QString& hashedDeviceId) = 0;

signals:
    void loaded();
    void loading();
    void closed();
    void clicked();
};

#endif // IQTADMOBBANNER_H

