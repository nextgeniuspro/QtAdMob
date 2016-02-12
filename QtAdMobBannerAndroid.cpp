#include "QtAdMobBannerAndroid.h"

#if (__ANDROID_API__ >= 9)

#include <QAndroidJniObject>
#include <qpa/qplatformnativeinterface.h>
#include <QApplication>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_org_dreamdev_QtAdMob_QtAdMobActivity_onBannerLoaded(JNIEnv *env, jobject thiz)
{
    Q_UNUSED(env)
    Q_UNUSED(thiz)

    const QtAdMobBannerAndroid::TInstances& instances = QtAdMobBannerAndroid::Instances();
    QtAdMobBannerAndroid::TInstances::ConstIterator beg = instances.begin();
    QtAdMobBannerAndroid::TInstances::ConstIterator end = instances.end();
    while(beg != end)
    {
        emit beg.value()->OnLoaded();

        beg++;
    }
}

JNIEXPORT void JNICALL Java_org_dreamdev_QtAdMob_QtAdMobActivity_onBannerLoading(JNIEnv *env, jobject thiz)
{
    Q_UNUSED(env)
    Q_UNUSED(thiz)

    const QtAdMobBannerAndroid::TInstances& instances = QtAdMobBannerAndroid::Instances();
    QtAdMobBannerAndroid::TInstances::ConstIterator beg = instances.begin();
    QtAdMobBannerAndroid::TInstances::ConstIterator end = instances.end();
    while(beg != end)
    {
        emit beg.value()->OnLoading();

        beg++;
    }
}

JNIEXPORT void JNICALL Java_org_dreamdev_QtAdMob_QtAdMobActivity_onBannerClosed(JNIEnv *env, jobject thiz)
{
    Q_UNUSED(env)
    Q_UNUSED(thiz)

    const QtAdMobBannerAndroid::TInstances& instances = QtAdMobBannerAndroid::Instances();
    QtAdMobBannerAndroid::TInstances::ConstIterator beg = instances.begin();
    QtAdMobBannerAndroid::TInstances::ConstIterator end = instances.end();
    while(beg != end)
    {
        emit beg.value()->OnClosed();

        beg++;
    }
}

JNIEXPORT void JNICALL Java_org_dreamdev_QtAdMob_QtAdMobActivity_onBannerClicked(JNIEnv *env, jobject thiz)
{
    Q_UNUSED(env)
    Q_UNUSED(thiz)

    const QtAdMobBannerAndroid::TInstances& instances = QtAdMobBannerAndroid::Instances();
    QtAdMobBannerAndroid::TInstances::ConstIterator beg = instances.begin();
    QtAdMobBannerAndroid::TInstances::ConstIterator end = instances.end();
    while(beg != end)
    {
        emit beg.value()->OnClicked();

        beg++;
    }
}

#ifdef __cplusplus
}
#endif

int QtAdMobBannerAndroid::s_Index = 0;
QtAdMobBannerAndroid::TInstances QtAdMobBannerAndroid::s_Instances;

QtAdMobBannerAndroid::QtAdMobBannerAndroid()
    : m_Activity(0)
    , m_Index(s_Index++)
{
    s_Instances[m_Index] = this;

    QPlatformNativeInterface* interface = QApplication::platformNativeInterface();
    jobject activity = (jobject)interface->nativeResourceForIntegration("QtActivity");
    if (activity)
    {
        m_Activity = new QAndroidJniObject(activity);
    }
}

QtAdMobBannerAndroid::~QtAdMobBannerAndroid()
{
    s_Instances.remove(m_Index);

    Hide();
    Shutdown();
    if (m_Activity)
    {
        delete m_Activity;
    }
}

void QtAdMobBannerAndroid::Initialize()
{
    if (!IsValid())
    {
        return;
    }

    m_Activity->callMethod<void>("InitializeAdBanner");
}

void QtAdMobBannerAndroid::Shutdown()
{
    if (!IsValid())
    {
        return;
    }

    m_Activity->callMethod<void>("ShutdownAdBanner");
}

void QtAdMobBannerAndroid::SetUnitId(const QString& unitId)
{
    if (!IsValid())
    {
        return;
    }

    QAndroidJniObject param1 = QAndroidJniObject::fromString(unitId);
    m_Activity->callMethod<void>("SetAdBannerUnitId", "(Ljava/lang/String;)V", param1.object<jstring>());
}

void QtAdMobBannerAndroid::SetSize(IQtAdMobBanner::BannerSize size)
{
    if (!IsValid())
    {
        return;
    }

    m_Activity->callMethod<void>("SetAdBannerSize", "(I)V", (int)size);
}

QSize QtAdMobBannerAndroid::GetSizeInPixels()
{
    int width = m_Activity->callMethod<int>("GetAdBannerWidth");
    int height = m_Activity->callMethod<int>("GetAdBannerHeight");

    return QSize(width, height);
}

void QtAdMobBannerAndroid::SetPosition(const QPoint& position)
{    
    if (!IsValid())
    {
        return;
    }

    m_Activity->callMethod<void>("SetAdBannerPosition", "(II)V", position.x(), position.y());
}

bool QtAdMobBannerAndroid::IsShow() const
{
    if (!IsValid())
    {
        return false;
    }

    bool isShow = m_Activity->callMethod<jboolean>("IsAdBannerShowed", "()Z");
    return isShow;
}

bool QtAdMobBannerAndroid::IsLoaded() const
{
    if (!IsValid())
    {
        return false;
    }

    bool isLoaded = m_Activity->callMethod<jboolean>("IsAdBannerLoaded", "()Z");
    return isLoaded;
}

void QtAdMobBannerAndroid::Show()
{
    if (!IsValid())
    {
        return;
    }

    m_Activity->callMethod<void>("ShowAdBanner");
}

void QtAdMobBannerAndroid::Hide()
{
    if (!IsValid())
    {
        return;
    }

    m_Activity->callMethod<void>("HideAdBanner");
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

const QtAdMobBannerAndroid::TInstances& QtAdMobBannerAndroid::Instances()
{
    return s_Instances;
}

bool QtAdMobBannerAndroid::IsValid() const
{
    return (m_Activity != 0 && m_Activity->isValid());
}

#endif // __ANDROID_API__
