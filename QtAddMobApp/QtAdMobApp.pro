#-------------------------------------------------
#
# Project created by QtCreator 2015-06-10T23:28:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtAdMob
TEMPLATE = app
DEFINES += ANDROID TARGET_OS_IPHONE TARGET_IPHONE_SIMULATOR

SOURCES += \
    main.cpp \
    MainWindow.cpp \

HEADERS  += \
    MainWindow.h \

FORMS    += \
    MainWindow.ui

include(QtAdMob/QtAdMob.pri)

QTADMOB_LIB_DIR = $$PWD/QtAdMob

ANDROID:
{
    QT += androidextras gui-private

    ANDROID_PACKAGE_SOURCE_DIR = $$QTADMOB_LIB_DIR/platform/android

    DISTFILES += \
        $$ANDROID_PACKAGE_SOURCE_DIR/AndroidManifest.xml \
        $$ANDROID_PACKAGE_SOURCE_DIR/project.properties \
        $$ANDROID_PACKAGE_SOURCE_DIR/src/org/dreamdev/QtAdMob/QtAdMobActivity.java
}

IOS:
{
    #QT += gui_private

    #IOS_PACKAGE_SOURCE_DIR = $$QTADMOB_LIB_DIR/platform/ios

    #LIBS += -F $$IOS_PACKAGE_SOURCE_DIR/GoogleMobileAds -framework GoogleMobileAds \
    #        -framework AVFoundation \
    #        -framework AudioToolbox \
    #        -framework CoreTelephony \
    #        -framework MessageUI \
    #        -framework SystemConfiguration \
    #        -framework CoreGraphics \
    #        -framework AdSupport \
    #        -framework StoreKit \
    #        -framework EventKit \
    #        -framework EventKitUI \
    #        -framework CoreMedia
}

