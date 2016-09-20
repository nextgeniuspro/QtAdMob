#include "QtAdMobBannerAndroid.h"

#if (__ANDROID_API__ >= 9)

#include <QAndroidJniObject>
#include <qpa/qplatformnativeinterface.h>
#include <QGuiApplication>

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
        emit beg.value()->loaded();

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
        emit beg.value()->loading();

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
        emit beg.value()->closed();

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
        emit beg.value()->clicked();

        beg++;
    }
}

#ifdef __cplusplus
}
#endif

int QtAdMobBannerAndroid::s_Index = 0;
QtAdMobBannerAndroid::TInstances QtAdMobBannerAndroid::s_Instances;

QtAdMobBannerAndroid::QtAdMobBannerAndroid()
    : m_BannerSize(IQtAdMobBanner::Banner)
    , m_Activity(0)
    , m_Index(s_Index++)
{
    s_Instances[m_Index] = this;

    QPlatformNativeInterface* interface = QGuiApplication::platformNativeInterface();
    jobject activity = (jobject)interface->nativeResourceForIntegration("QtActivity");
    if (activity)
    {
        m_Activity = new QAndroidJniObject(activity);
    }

    m_Activity->callMethod<void>("InitializeAdBanner");
}

QtAdMobBannerAndroid::~QtAdMobBannerAndroid()
{
    s_Instances.remove(m_Index);

    setVisible(false);
    if (isValid())
    {
        m_Activity->callMethod<void>("ShutdownAdBanner");
    }

    if (m_Activity)
    {
        delete m_Activity;
    }
}

void QtAdMobBannerAndroid::setUnitId(const QString& unitId)
{
    if (!isValid())
    {
        return;
    }

    QAndroidJniObject param1 = QAndroidJniObject::fromString(unitId);
    m_Activity->callMethod<void>("SetAdBannerUnitId", "(Ljava/lang/String;)V", param1.object<jstring>());
    m_UnitId = unitId;
}

const QString& QtAdMobBannerAndroid::unitId() const
{
    return m_UnitId;
}

void QtAdMobBannerAndroid::setSize(IQtAdMobBanner::Sizes size)
{
    if (!isValid())
    {
        return;
    }

    m_Activity->callMethod<void>("SetAdBannerSize", "(I)V", (int)size);
    m_BannerSize = size;
}

IQtAdMobBanner::Sizes QtAdMobBannerAndroid::size() const
{
    return m_BannerSize;
}

QSize QtAdMobBannerAndroid::sizeInPixels()
{
    int width = m_Activity->callMethod<int>("GetAdBannerWidth");
    int height = m_Activity->callMethod<int>("GetAdBannerHeight");

    return QSize(width, height);
}

void QtAdMobBannerAndroid::setPosition(const QPoint& position)
{    
    if (!isValid())
    {
        return;
    }

    m_Activity->callMethod<void>("SetAdBannerPosition", "(II)V", position.x(), position.y());
    m_Position = position;
}

const QPoint& QtAdMobBannerAndroid::position() const
{
    return m_Position;
}

void QtAdMobBannerAndroid::setVisible(bool isVisible)
{
    if (!isValid())
    {
        return;
    }

    if (isVisible)
    {
        m_Activity->callMethod<void>("ShowAdBanner");
    }
    else
    {
        m_Activity->callMethod<void>("HideAdBanner");
    }
}

bool QtAdMobBannerAndroid::visible()
{
    if (!isValid())
    {
        return false;
    }

    bool isVisible = m_Activity->callMethod<jboolean>("IsAdBannerShowed", "()Z");
    return isVisible;
}

bool QtAdMobBannerAndroid::isLoaded()
{
    if (!isValid())
    {
        return false;
    }

    bool isLoaded = m_Activity->callMethod<jboolean>("IsAdBannerLoaded", "()Z");
    return isLoaded;
}

void QtAdMobBannerAndroid::addTestDevice(const QString& hashedDeviceId)
{
    if (!isValid())
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

bool QtAdMobBannerAndroid::isValid() const
{
    return (m_Activity != 0 && m_Activity->isValid());
}

#endif // __ANDROID_API__
