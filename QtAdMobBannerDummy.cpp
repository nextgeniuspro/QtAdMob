#include "QtAdMobBannerDummy.h"

QtAdMobBannerDummy::QtAdMobBannerDummy()
{
}

QtAdMobBannerDummy::~QtAdMobBannerDummy()
{
}

void QtAdMobBannerDummy::Initialize()
{
}

void QtAdMobBannerDummy::Shutdown()
{
}

void QtAdMobBannerDummy::SetUnitId(const QString& unitId)
{
    Q_UNUSED(unitId);
}

void QtAdMobBannerDummy::SetSize(IQtAdMobBanner::BannerSize size)
{
    Q_UNUSED(size);
}

QSize QtAdMobBannerDummy::GetSizeInPixels()
{
    return QSize();
}

void QtAdMobBannerDummy::SetPosition(const QPoint& position)
{
    Q_UNUSED(position);
}

bool QtAdMobBannerDummy::IsShow() const
{
    return false;
}

bool QtAdMobBannerDummy::IsLoaded() const
{
    return false;
}

void QtAdMobBannerDummy::Show()
{
}

void QtAdMobBannerDummy::Hide()
{
}

void QtAdMobBannerDummy::AddTestDevice(const QString& hashedDeviceId)
{
    Q_UNUSED(hashedDeviceId);
}
