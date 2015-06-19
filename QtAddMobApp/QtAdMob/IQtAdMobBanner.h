#ifndef IQTADMOBBANNER_H
#define IQTADMOBBANNER_H

#include <QString>
#include <QSize>
#include <QPoint>

#define UNUSED(x) (void)(x)

class IQtAdMobBanner
{
public:
    enum BannerSize
    {
        Banner = 0,
        FullBanner,
        LargeBanner,
        MediumRectangle,
        SmartBanner,
        WideSkyscraper
    };

public:
    IQtAdMobBanner() {}
    virtual ~IQtAdMobBanner() {}

    virtual void Initialize() = 0;
    virtual void Shutdown() = 0;

    virtual void SetUnitId(const QString& unitId) = 0;
    virtual void SetSize(BannerSize size) = 0;
    virtual QSize GetSizeInPixels() = 0;
    virtual void SetPosition(const QPoint& position) = 0;
    virtual bool IsShow() const = 0;
    virtual bool IsLoaded() const = 0;
    virtual void Show() = 0;
    virtual void Hide() = 0;

    virtual void AddTestDevice(const QString& hashedDeviceId) = 0;
};

#endif // IQTADMOBBANNER_H

