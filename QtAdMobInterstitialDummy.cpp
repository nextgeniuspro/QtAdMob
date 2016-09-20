#include "QtAdMobInterstitialDummy.h"
#include "IQtAdMobBanner.h"

QtAdMobInterstitialDummy::QtAdMobInterstitialDummy()
{
}

QtAdMobInterstitialDummy::~QtAdMobInterstitialDummy()
{
}

void QtAdMobInterstitialDummy::setUnitId(const QString& unitId)
{
    m_UnitId = unitId;
}

const QString& QtAdMobInterstitialDummy::unitId() const
{
    return m_UnitId;
}

void QtAdMobInterstitialDummy::setVisible(bool isVisible)
{
    Q_UNUSED(isVisible);
}

bool QtAdMobInterstitialDummy::visible()
{
    return false;
}

bool QtAdMobInterstitialDummy::isLoaded()
{
    return false;
}

void QtAdMobInterstitialDummy::addTestDevice(const QString& hashedDeviceId)
{
    Q_UNUSED(hashedDeviceId);
}
