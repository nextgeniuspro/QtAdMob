#include "QtAdMobInterstitialAndroid.h"

#if (__ANDROID_API__ >= 9)

#include <QAndroidJniObject>
#include <QPA/QPlatformNativeInterface.h>
#include <QApplication>
#include "IQtAdMobBanner.h"

QtAdMobInterstitialAndroid::QtAdMobInterstitialAndroid()
    : m_Activity(0)
{
    QPlatformNativeInterface* interface = QApplication::platformNativeInterface();
    jobject activity = (jobject)interface->nativeResourceForIntegration("QtActivity");
    if (activity)
    {
        m_Activity = new QAndroidJniObject(activity);
    }
}

QtAdMobInterstitialAndroid::~QtAdMobInterstitialAndroid()
{
    if (m_Activity)
    {
        delete m_Activity;
    }
}

void QtAdMobInterstitialAndroid::LoadWithUnitId(const QString& unitId)
{
    if (!IsValid())
    {
        return;
    }

    QAndroidJniObject param1 = QAndroidJniObject::fromString(unitId);
    m_Activity->callMethod<void>("LoadAdInterstitialWithUnitId", "(Ljava/lang/String;)V", param1.object<jstring>());
}

bool QtAdMobInterstitialAndroid::IsLoaded() const
{
    if (!IsValid())
    {
        return false;
    }

    bool isLoaded = m_Activity->callMethod<jboolean>("IsAdInterstitialLoaded", "()Z");
    return isLoaded;
}

void QtAdMobInterstitialAndroid::Show()
{    
    if (!IsValid())
    {
        return;
    }

    m_Activity->callMethod<void>("ShowAdInterstitial");
}

void QtAdMobInterstitialAndroid::AddTestDevice(const QString& hashedDeviceId)
{
    if (!IsValid())
    {
        return;
    }

    QAndroidJniObject param1 = QAndroidJniObject::fromString(hashedDeviceId);
    m_Activity->callMethod<void>("AddAdTestDevice", "(Ljava/lang/String;)V", param1.object<jstring>());
}

bool QtAdMobInterstitialAndroid::IsValid() const
{
    return (m_Activity != 0 && m_Activity->isValid());
}

#endif // __ANDROID_API__
