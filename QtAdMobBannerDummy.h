#ifndef QTADMOBBANNERDUMMY_H
#define QTADMOBBANNERDUMMY_H

#include "IQtAdMobBanner.h"

class QtAdMobBannerDummy : public IQtAdMobBanner
{
public:
    QtAdMobBannerDummy();
    virtual ~QtAdMobBannerDummy();

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
    QString m_UnitId;
    IQtAdMobBanner::Sizes m_BannerSize;
    QPoint m_Position;
};

#endif // QTADMOBBANNERDUMMY_H
