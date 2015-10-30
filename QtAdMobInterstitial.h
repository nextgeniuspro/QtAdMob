#ifndef QTADMOBINTERSTITIAL_H
#define QTADMOBINTERSTITIAL_H

#include "QtAdMobInterstitialAndroid.h"
#include "QtAdMobInterstitialDummy.h"
#include "QtAdMobInterstitialIos.h"

inline IQtAdMobInterstitial* CreateQtAdMobInterstitial()
{
#if (__ANDROID_API__ >= 9)
    return new QtAdMobInterstitialAndroid();
#elif (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    return new QtAdMobInterstitialIos();
#else
    return new QtAdMobInterstitialDummy();
#endif
}

#endif // QTADMOBINTERSTITIAL_H

