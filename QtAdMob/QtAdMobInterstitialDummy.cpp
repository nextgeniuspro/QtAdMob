#include "QtAdMobInterstitialDummy.h"
#include "IQtAdMobBanner.h"

QtAdMobInterstitialDummy::QtAdMobInterstitialDummy()
{
}

QtAdMobInterstitialDummy::~QtAdMobInterstitialDummy()
{
}

void QtAdMobInterstitialDummy::LoadWithUnitId(const QString& unitId)
{
    UNUSED(unitId);
}

bool QtAdMobInterstitialDummy::IsLoaded() const
{
    return false;
}

void QtAdMobInterstitialDummy::Show()
{    
}

void QtAdMobInterstitialDummy::AddTestDevice(const QString& hashedDeviceId)
{
    UNUSED(hashedDeviceId);
}
