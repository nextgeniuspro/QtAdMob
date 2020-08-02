#include "QtAdMobRewardedVideo.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef Q_OS_ANDROID
// Listener when Java calls Rewarded() signal
JNIEXPORT void JNICALL Java_org_dreamdev_QtAdMob_QtAdMobActivity_Rewarded(JNIEnv *env, jobject thiz)
{
    Q_UNUSED(env)
    Q_UNUSED(thiz)

    // Emit to QML app by calling Rewarded signal
    emit QmlRewardedVideoAd::Instances()->rewarded();
}
// Listener when Java calls RewardedVideoAdClosed() signal
JNIEXPORT void JNICALL Java_org_dreamdev_QtAdMob_QtAdMobActivity_RewardedVideoAdClosed(JNIEnv *env, jobject thiz)
{
    Q_UNUSED(env)
    Q_UNUSED(thiz)

    // Emit to QML app by calling RewardedVideoAdClosed signal
    emit QmlRewardedVideoAd::Instances()->rewardedVideoAdClosed();
}
// Listener when Java calls RewardedVideoAdFailedToLoad() signal
JNIEXPORT void JNICALL Java_org_dreamdev_QtAdMob_QtAdMobActivity_RewardedVideoAdFailedToLoad(JNIEnv *env, jobject thiz, jint errorCode)
{
    Q_UNUSED(env)
    Q_UNUSED(thiz)

    // Emit to QML app by calling RewardedVideoAdFailedToLoad signal
    emit QmlRewardedVideoAd::Instances()->rewardedVideoAdFailedToLoad(errorCode);
}
// Listener when Java calls RewardedVideoAdLeftApplication() signal
JNIEXPORT void JNICALL Java_org_dreamdev_QtAdMob_QtAdMobActivity_RewardedVideoAdLeftApplication(JNIEnv *env, jobject thiz)
{
    Q_UNUSED(env)
    Q_UNUSED(thiz)

    // Emit to QML app by calling RewardedVideoAdLeftApplication signal
    emit QmlRewardedVideoAd::Instances()->rewardedVideoAdLeftApplication();
}
// Listener when Java calls RewardedVideoAdLoaded() signal
JNIEXPORT void JNICALL Java_org_dreamdev_QtAdMob_QtAdMobActivity_RewardedVideoAdLoaded(JNIEnv *env, jobject thiz)
{
    Q_UNUSED(env)
    Q_UNUSED(thiz)

    // Emit to QML app by calling RewardedVideoAdLoaded signal
    emit QmlRewardedVideoAd::Instances()->rewardedVideoAdLoaded();
}
// Listener when Java calls RewardedVideoAdOpened() signal
JNIEXPORT void JNICALL Java_org_dreamdev_QtAdMob_QtAdMobActivity_RewardedVideoAdOpened(JNIEnv *env, jobject thiz)
{
    Q_UNUSED(env)
    Q_UNUSED(thiz)

    // Emit to QML app by calling RewardedVideoAdOpened signal
    emit QmlRewardedVideoAd::Instances()->rewardedVideoAdOpened();
}
// Listener when Java calls RewardedVideoCompleted() signal
JNIEXPORT void JNICALL Java_com_gmail_manhcuong5993_QtAdMobActivity_RewardedVideoCompleted(JNIEnv *env, jobject thiz)
{
    Q_UNUSED(env)
    Q_UNUSED(thiz)

    // Emit to QML app by calling RewardedVideoCompleted signal
    emit QmlRewardedVideoAd::Instances()->rewardedVideoCompleted();
}
// Listener when Java calls RewardedVideoStarted() signal
JNIEXPORT void JNICALL Java_org_dreamdev_QtAdMob_QtAdMobActivity_RewardedVideoStarted(JNIEnv *env, jobject thiz)
{
    Q_UNUSED(env)
    Q_UNUSED(thiz)

    // Emit to QML app by calling RewardedVideoStarted signal
    emit QmlRewardedVideoAd::Instances()->rewardedVideoStarted();
}
#endif

#ifdef __cplusplus
}
#endif

// Global variable to keep instance of class
static QtAdMobRewardedVideoAndroid *mQmlRewardedVideoAd = nullptr;

QtAdMobRewardedVideoAndroid::QtAdMobRewardedVideoAndroid()
{
#ifdef Q_OS_ANDROID
    // Update global instance
    mQmlRewardedVideoAd = this;

    // Create Android Activity on Qt
    QPlatformNativeInterface* interface = QGuiApplication::platformNativeInterface();
    jobject activity = (jobject)interface->nativeResourceForIntegration("QtActivity");
    if (activity)
    {
        m_Activity = new QAndroidJniObject(activity);
    }

    // Call InitializeBanner method of Java
    m_Activity->callMethod<void>("InitializeRewardedVideoAd");
#endif

#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    m_QtAdmobRewardVideo = new QtAdmobRewardVideoDelegateImpl();
    m_QtAdmobRewardVideo->setQtAdmobRewardVideoIos(this);
#endif
}

QtAdMobRewardedVideoAndroid *QtAdMobRewardedVideoAndroid::Instances()
{
    return mQmlRewardedVideoAd;
}

void QtAdMobRewardedVideoAndroid::setUnitId(const QString &unitId)
{
#ifdef Q_OS_ANDROID
    if(m_Activity != nullptr)
    {
        QAndroidJniObject param1 = QAndroidJniObject::fromString(unitId);
        // Call SetBannerUnitId method of Java
        m_Activity->callMethod<void>("SetRewardedVideoAdUnitId", "(Ljava/lang/String;)V", param1.object<jstring>());
    }
#elif _WIN32
    Q_UNUSED(unitId)
#endif

#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
   m_QtAdmobRewardVideo->setUnitId(unitId);
#endif
}

void QtAdMobRewardedVideoAndroid::setTestDeviceId(const QString &testDeviceId)
{
#ifdef Q_OS_ANDROID
    if(m_Activity != nullptr)
    {
        QAndroidJniObject param1 = QAndroidJniObject::fromString(testDeviceId);
        // Call SetBannerUnitId method of Java
        m_Activity->callMethod<void>("SetRewardedVideoTestDeviceId", "(Ljava/lang/String;)V", param1.object<jstring>());
    }
#elif _WIN32
    Q_UNUSED(testDeviceId)
#endif

#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
   m_QtAdmobRewardVideo->setTestDeviceId(testDeviceId);
#endif
}

void QtAdMobRewardedVideoAndroid::loadRewardedVideoAd()
{
#ifdef Q_OS_ANDROID
    if(m_Activity != nullptr)
    {
        // Call LoadBanner method of Java
        m_Activity->callMethod<void>("LoadRewardedVideoAd");
    }
#endif

#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
   m_QtAdmobRewardVideo->loadRewardedVideoAd();
#endif
}

void QtAdMobRewardedVideoAndroid::show()
{
#ifdef Q_OS_ANDROID
    if(m_Activity != nullptr)
    {
        // Call LoadBanner method of Java
        m_Activity->callMethod<void>("ShowRewardedVideoAd");
    }
#endif

#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
   m_QtAdmobRewardVideo->show();
#endif
}
