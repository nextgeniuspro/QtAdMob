#ifndef QMLREWARDEDVIDEOAD_H
#define QMLREWARDEDVIDEOAD_H

#include <QObject>
#include <QGuiApplication>
#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
#include <QtAndroid>
#include <qpa/qplatformnativeinterface.h>
#endif

#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
class QtAdmobRewardVideoDelegateImpl;
#endif

class QtAdMobRewardedVideoAndroid : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString unitId WRITE setUnitId)
    Q_PROPERTY(QString testDeviceId WRITE setTestDeviceId)
public:
    QtAdMobRewardedVideoAndroid();
    static QtAdMobRewardedVideoAndroid* Instances();

    static void DeclareQML();
    void setUnitId(const QString& unitId);
    void setTestDeviceId(const QString &testDeviceId);

signals:
    void rewarded();
    void rewardedVideoAdClosed();
    void rewardedVideoAdFailedToLoad(int errorCode);
    void rewardedVideoAdLeftApplication();
    void rewardedVideoAdLoaded();
    void rewardedVideoAdOpened();
    void rewardedVideoCompleted();
    void rewardedVideoStarted();

public slots:
    void loadRewardedVideoAd();
    void show();

private:
#ifdef Q_OS_ANDROID
    QAndroidJniObject* m_Activity;
#endif

#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    QtAdmobRewardVideoDelegateImpl* m_QtAdmobRewardVideo;
#endif
};

#endif // QMLREWARDEDVIDEOAD_H
