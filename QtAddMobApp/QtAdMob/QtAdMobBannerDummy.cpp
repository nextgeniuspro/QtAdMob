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

void QtAdMobBannerDummy::SetAdUnitId(const QString& unitId)
{
    UNUSED(unitId);
}

void QtAdMobBannerDummy::SetAdSize(IQtAdMobBanner::BannerSize size)
{
    UNUSED(size);
}

void QtAdMobBannerDummy::SetPosition(const QPoint& position)
{
    UNUSED(position);
}

QSize QtAdMobBannerDummy::GetDimensions()
{
    return QSize();
}

bool QtAdMobBannerDummy::IsShowed() const
{
    return false;
}

bool QtAdMobBannerDummy::IsLoaded() const
{
    return false;
}

void QtAdMobBannerDummy::ShowAd()
{
}

void QtAdMobBannerDummy::HideAd()
{
}

void QtAdMobBannerDummy::AddTestDevice(const QString& hashedDeviceId)
{
    UNUSED(hashedDeviceId);
}
