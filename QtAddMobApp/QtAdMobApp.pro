#-------------------------------------------------
#
# Project created by QtCreator 2015-06-10T23:28:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtAdMob
VERSION = 0.0.1
TEMPLATE = app

SOURCES += \
    main.cpp \
    MainWindow.cpp \

HEADERS  += \
    MainWindow.h \

FORMS    += \
    MainWindow.ui

include(QtAdMob/QtAdMob.pri)

QTADMOB_LIB_DIR = $$PWD/QtAdMob

android:
{
    ANDROID_PACKAGE_SOURCE_DIR = $$QTADMOB_LIB_DIR/platform/android
    android:QT += androidextras gui-private
    android:DISTFILES += \
            $$ANDROID_PACKAGE_SOURCE_DIR/AndroidManifest.xml \
            $$ANDROID_PACKAGE_SOURCE_DIR/project.properties \
            $$ANDROID_PACKAGE_SOURCE_DIR/src/org/dreamdev/QtAdMob/QtAdMobActivity.java
}

ios:
{
    IOS_PACKAGE_SOURCE_DIR = $$QTADMOB_LIB_DIR/platform/ios
    ios:QMAKE_INFO_PLIST = $$IOS_PACKAGE_SOURCE_DIR/Info.plist
    ios:QMAKE_CXXFLAGS += -fobjc-arc
    ios:QMAKE_LFLAGS += -ObjC
    ios:QT += gui_private
    ios:LIBS += -F $$IOS_PACKAGE_SOURCE_DIR/GoogleMobileAds -framework GoogleMobileAds \
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

