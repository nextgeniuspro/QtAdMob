#-------------------------------------------------
#
# Project created by QtCreator 2015-06-10T23:28:49
#
#-------------------------------------------------

SOURCES += \
    $$PWD/QtAdMobBannerAndroid.cpp \
    $$PWD/QtAdMobBannerDummy.cpp \
    $$PWD/QtAdMobInterstitialAndroid.cpp \
    $$PWD/QtAdMobInterstitialDummy.cpp

OBJECTIVE_SOURCES += \
    $$PWD/QtAdMobBannerIos.mm \
    $$PWD/QtAdMobInterstitialIos.mm

HEADERS  += \
    $$PWD/IQtAdMobBanner.h \
    $$PWD/QtAdMobBannerAndroid.h \
    $$PWD/QtAdMobBannerIos.h \
    $$PWD/QtAdMobBannerDummy.h \
    $$PWD/QtAdMobBanner.h \
    $$PWD/IQtAdMobInterstitial.h \
    $$PWD/QtAdMobInterstitial.h \
    $$PWD/QtAdMobInterstitialIos.h \
    $$PWD/QtAdMobInterstitialAndroid.h \
    $$PWD/QtAdMobInterstitialDummy.h

ios {
    ios:QMAKE_CXXFLAGS += -fobjc-arc
    ios:QMAKE_LFLAGS += -ObjC
    ios:QT += gui_private
    ios:LIBS += -F $$PWD/platform/ios/GoogleMobileAds -framework GoogleMobileAds \
                -framework AVFoundation \
                -framework AudioToolbox \
                -framework CoreTelephony \
                -framework MessageUI \
                -framework SystemConfiguration \
                -framework CoreGraphics \
                -framework AdSupport \
                -framework StoreKit \
                -framework EventKit \
                -framework EventKitUI \
                -framework CoreMedia
}
