#ifndef QTADMOBBANNER
#define QTADMOBBANNER

#include "QtAdMobBannerAndroid.h"
#include "QtAdMobBannerIos.h"
#include "QtAdMobBannerDummy.h"

class QWidget;

inline IQtAdMobBanner* CreateQtAdMobBanner(QWidget* parent = 0)
{
    UNUSED(parent);
#if ANDROID
    return new QtAdMobBannerAndroid();
#elif defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
    return new QtAdMobBannerIos(parent);
#else
    return new QtAdMobBannerDummy();
#endif
}

#endif // QTADMOBBANNER

