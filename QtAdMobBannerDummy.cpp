#include "QtAdMobBannerDummy.h"

QtAdMobBannerDummy::QtAdMobBannerDummy()
    : m_BannerSize(IQtAdMobBanner::Banner)
{
}

QtAdMobBannerDummy::~QtAdMobBannerDummy()
{
}

void QtAdMobBannerDummy::setUnitId(const QString& unitId)
{
    m_UnitId = unitId;
}

const QString& QtAdMobBannerDummy::unitId() const
{
    return m_UnitId;
}

void QtAdMobBannerDummy::setSize(IQtAdMobBanner::Sizes size)
{
    m_BannerSize = size;
}

IQtAdMobBanner::Sizes QtAdMobBannerDummy::size() const
{
    return m_BannerSize;
}

QSize QtAdMobBannerDummy::sizeInPixels()
{
    return QSize();
}

void QtAdMobBannerDummy::setPosition(const QPoint& position)
{
    m_Position = position;
}

const QPoint& QtAdMobBannerDummy::position() const
{
    return m_Position;
}

void QtAdMobBannerDummy::setVisible(bool isVisible)
{
    Q_UNUSED(isVisible);
}

bool QtAdMobBannerDummy::visible()
{
    return false;
}

bool QtAdMobBannerDummy::isLoaded()
{
    return false;
}

void QtAdMobBannerDummy::addTestDevice(const QString& hashedDeviceId)
{
    Q_UNUSED(hashedDeviceId);
}
