#ifndef QTADMOBINTERSTITIAL_H
#define QTADMOBINTERSTITIAL_H

#include "QtAdMobInterstitialIos.h"

inline IQtAdMobInterstitial* CreateQtAdMobInterstitial()
{
#if (__ANDROID_API__ >= 9)
    return 0;
#elif (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    return new QtAdMobInterstitialIos();
#else
    return 0;
#endif
}

#endif // QTADMOBINTERSTITIAL_H

