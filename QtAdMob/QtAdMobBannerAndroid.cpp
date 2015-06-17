#include "QtAdMobBannerAndroid.h"

#ifdef __ANDROID_API__

#include <QAndroidJniObject>
#include <QPA/QPlatformNativeInterface.h>
#include <QApplication>

QtAdMobBannerAndroid::QtAdMobBannerAndroid()
    : m_Activity(0)
{
    QPlatformNativeInterface* interface = QApplication::platformNativeInterface();
    jobject activity = (jobject)interface->nativeResourceForIntegration("QtActivity");
    if (activity)
    {
        m_Activity = new QAndroidJniObject(activity);
    }
}

QtAdMobBannerAndroid::~QtAdMobBannerAndroid()
{
    if (IsValid())
    {
        HideAd();
        delete m_Activity;
    }
}

void QtAdMobBannerAndroid::Initialize()
{
    if (!IsValid())
    {
        return;
    }

    m_Activity->callMethod<void>("InitializeAd");
}

void QtAdMobBannerAndroid::Shutdown()
{
    if (!IsValid())
    {
        return;
    }

    m_Activity->callMethod<void>("ShutdownAd");
}

void QtAdMobBannerAndroid::SetAdUnitId(const QString& unitId)
{
    if (!IsValid())
    {
        return;
    }

    QAndroidJniObject param1 = QAndroidJniObject::fromString(unitId);
    m_Activity->callMethod<void>("SetAdUnitId", "(Ljava/lang/String;)V", param1.object<jstring>());
}

void QtAdMobBannerAndroid::SetAdSize(IQtAdMobBanner::BannerSize size)
{
    if (!IsValid())
    {
        return;
    }

    m_Activity->callMethod<void>("SetAdSize", "(I)V", (int)size);
}

void QtAdMobBannerAndroid::SetPosition(const QPoint& position)
{    
    if (!IsValid())
    {
        return;
    }

    m_Activity->callMethod<void>("SetAdPosition", "(II)V", position.x(), position.y());
}

QSize QtAdMobBannerAndroid::GetDimensions()
{
    int width = m_Activity->callMethod<int>("GetAdWidth");
    int height = m_Activity->callMethod<int>("GetAdHeight");

    return QSize(width, height);
}

bool QtAdMobBannerAndroid::IsShowed() const
{
    if (!IsValid())
    {
        return false;
    }

    bool isShowed = m_Activity->callMethod<jboolean>("IsShowed", "()Z");
    return isShowed;
}

bool QtAdMobBannerAndroid::IsLoaded() const
{
    if (!IsValid())
    {
        return false;
    }

    bool isLoaded = m_Activity->callMethod<jboolean>("IsLoaded", "()Z");
    return isLoaded;
}

void QtAdMobBannerAndroid::ShowAd()
{
    if (!IsValid())
    {
        return;
    }

    m_Activity->callMethod<void>("ShowAd");
}

void QtAdMobBannerAndroid::HideAd()
{
    if (!IsValid())
    {
        return;
    }

    m_Activity->callMethod<void>("HideAd");
}

void QtAdMobBannerAndroid::AddTestDevice(const QString& hashedDeviceId)
{
    if (!IsValid())
    {
        return;
    }

    QAndroidJniObject param1 = QAndroidJniObject::fromString(hashedDeviceId);
    m_Activity->callMethod<void>("AddAdTestDevice", "(Ljava/lang/String;)V", param1.object<jstring>());
}

bool QtAdMobBannerAndroid::IsValid() const
{
    return (m_Activity != 0);
}

#endif // __ANDROID_API__
