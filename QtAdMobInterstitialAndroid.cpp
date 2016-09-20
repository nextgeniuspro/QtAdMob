#include "QtAdMobInterstitialAndroid.h"

#if (__ANDROID_API__ >= 9)

#include <QAndroidJniObject>
#include <qpa/qplatformnativeinterface.h>
#include <QGuiApplication>
#include "IQtAdMobBanner.h"
#include <QAndroidJniEnvironment>
#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_org_dreamdev_QtAdMob_QtAdMobActivity_onInterstitialLoaded(JNIEnv *env, jobject thiz)
{
    Q_UNUSED(env)
    Q_UNUSED(thiz)

    const QtAdMobInterstitialAndroid::TInstances& instances = QtAdMobInterstitialAndroid::Instances();
    QtAdMobInterstitialAndroid::TInstances::ConstIterator beg = instances.begin();
    QtAdMobInterstitialAndroid::TInstances::ConstIterator end = instances.end();
    while(beg != end)
    {
        emit beg.value()->loaded();

        beg++;
    }
}

JNIEXPORT void JNICALL Java_org_dreamdev_QtAdMob_QtAdMobActivity_onInterstitialLoading(JNIEnv *env, jobject thiz)
{
    Q_UNUSED(env)
    Q_UNUSED(thiz)

    const QtAdMobInterstitialAndroid::TInstances& instances = QtAdMobInterstitialAndroid::Instances();
    QtAdMobInterstitialAndroid::TInstances::ConstIterator beg = instances.begin();
    QtAdMobInterstitialAndroid::TInstances::ConstIterator end = instances.end();
    while(beg != end)
    {
        emit beg.value()->loading();

        beg++;
    }
}

JNIEXPORT void JNICALL Java_org_dreamdev_QtAdMob_QtAdMobActivity_onInterstitialWillPresent(JNIEnv *env, jobject thiz)
{
    Q_UNUSED(env)
    Q_UNUSED(thiz)

    const QtAdMobInterstitialAndroid::TInstances& instances = QtAdMobInterstitialAndroid::Instances();
    QtAdMobInterstitialAndroid::TInstances::ConstIterator beg = instances.begin();
    QtAdMobInterstitialAndroid::TInstances::ConstIterator end = instances.end();
    while(beg != end)
    {
        emit beg.value()->willPresent();

        beg++;
    }
}

JNIEXPORT void JNICALL Java_org_dreamdev_QtAdMob_QtAdMobActivity_onInterstitialClicked(JNIEnv *env, jobject thiz)
{
    Q_UNUSED(env)
    Q_UNUSED(thiz)

    const QtAdMobInterstitialAndroid::TInstances& instances = QtAdMobInterstitialAndroid::Instances();
    QtAdMobInterstitialAndroid::TInstances::ConstIterator beg = instances.begin();
    QtAdMobInterstitialAndroid::TInstances::ConstIterator end = instances.end();
    while(beg != end)
    {
        emit beg.value()->clicked();

        beg++;
    }
}

JNIEXPORT void JNICALL Java_org_dreamdev_QtAdMob_QtAdMobActivity_onInterstitialClosed(JNIEnv *env, jobject thiz)
{
    Q_UNUSED(env)
    Q_UNUSED(thiz)

    const QtAdMobInterstitialAndroid::TInstances& instances = QtAdMobInterstitialAndroid::Instances();
    QtAdMobInterstitialAndroid::TInstances::ConstIterator beg = instances.begin();
    QtAdMobInterstitialAndroid::TInstances::ConstIterator end = instances.end();
    while(beg != end)
    {
        emit beg.value()->closed();

        beg++;
    }
}

#ifdef __cplusplus
}
#endif

int QtAdMobInterstitialAndroid::s_Index = 0;
QtAdMobInterstitialAndroid::TInstances QtAdMobInterstitialAndroid::s_Instances;

QtAdMobInterstitialAndroid::QtAdMobInterstitialAndroid()
    : m_Activity(0)
    , m_Index(s_Index++)
{
    s_Instances[m_Index] = this;

    QPlatformNativeInterface* interface = QGuiApplication::platformNativeInterface();
    jobject activity = (jobject)interface->nativeResourceForIntegration("QtActivity");
    if (activity)
    {
        m_Activity = new QAndroidJniObject(activity);
    }
}

QtAdMobInterstitialAndroid::~QtAdMobInterstitialAndroid()
{
    s_Instances.remove(m_Index);

    if (m_Activity)
    {
        delete m_Activity;
    }
}

void QtAdMobInterstitialAndroid::setUnitId(const QString& unitId)
{
    if (!isValid())
    {
        return;
    }

    QAndroidJniObject param1 = QAndroidJniObject::fromString(unitId);
    m_Activity->callMethod<void>("LoadAdInterstitialWithUnitId", "(Ljava/lang/String;)V", param1.object<jstring>());

    m_UnitId = unitId;
}

const QString& QtAdMobInterstitialAndroid::unitId() const
{
    return m_UnitId;
}

void QtAdMobInterstitialAndroid::setVisible(bool isVisible)
{
    if (!isValid())
    {
        return;
    }
    // TODO: implement hide
    m_Activity->callMethod<void>("ShowAdInterstitial");
}

bool QtAdMobInterstitialAndroid::visible()
{
    return false; // TODO: implement retrieve visibility
}

bool QtAdMobInterstitialAndroid::isLoaded()
{
    if (!isValid())
    {
        return false;
    }

    bool isLoaded = m_Activity->callMethod<jboolean>("IsAdInterstitialLoaded", "()Z");
    return isLoaded;
}

void QtAdMobInterstitialAndroid::addTestDevice(const QString& hashedDeviceId)
{
    if (!isValid())
    {
        return;
    }

    QAndroidJniObject param1 = QAndroidJniObject::fromString(hashedDeviceId);
    m_Activity->callMethod<void>("AddAdTestDevice", "(Ljava/lang/String;)V", param1.object<jstring>());
}

const QtAdMobInterstitialAndroid::TInstances& QtAdMobInterstitialAndroid::Instances()
{
    return s_Instances;
}

bool QtAdMobInterstitialAndroid::isValid() const
{
    return (m_Activity != 0 && m_Activity->isValid());
}

#endif // __ANDROID_API__
