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
    UNUSED(unitId);
}

void QtAdMobBannerDummy::SetSize(IQtAdMobBanner::BannerSize size)
{
    UNUSED(size);
}

QSize QtAdMobBannerDummy::GetSizeInPixels()
{
    return QSize();
}

void QtAdMobBannerDummy::SetPosition(const QPoint& position)
{
    UNUSED(position);
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
    UNUSED(hashedDeviceId);
}
