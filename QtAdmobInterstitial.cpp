#include "QtAdMobInterstitial.h"
#ifdef QTADMOB_QML
#include <QtQml>
#endif

QmlAdMobInterstitial::QmlAdMobInterstitial()
{
    m_Instance = CreateQtAdMobInterstitial();

    connect(m_Instance, SIGNAL(loaded()), this, SIGNAL(loaded()));
    connect(m_Instance, SIGNAL(loading()), this, SIGNAL(loading()));
    connect(m_Instance, SIGNAL(willPresent()), this, SIGNAL(willPresent()));
    connect(m_Instance, SIGNAL(closed()), this, SIGNAL(closed()));
    connect(m_Instance, SIGNAL(clicked()), this, SIGNAL(clicked()));
}

QmlAdMobInterstitial::~QmlAdMobInterstitial()
{
    delete m_Instance;
}

void QmlAdMobInterstitial::DeclareQML()
{
#ifdef QTADMOB_QML
    qmlRegisterType<QmlAdMobInterstitial>("com.dreamdev.QtAdMobInterstitial", 1, 0, "AdMobInterstitial");
#endif
}

void QmlAdMobInterstitial::setUnitId(const QString& unitId)
{
    QML()->setUnitId(unitId);

    emit unitIdChanged();
}

const QString& QmlAdMobInterstitial::unitId() const
{
    return QML()->unitId();
}

void QmlAdMobInterstitial::setVisible(bool isVisible)
{
    QML()->setVisible(isVisible);

    emit visibleChanged();
}

bool QmlAdMobInterstitial::visible()
{
    return QML()->visible();
}

bool QmlAdMobInterstitial::isLoaded()
{
    return QML()->isLoaded();
}

void QmlAdMobInterstitial::addTestDevice(const QString& hashedDeviceId)
{
    QML()->addTestDevice(hashedDeviceId);
}

IQtAdMobInterstitial* QmlAdMobInterstitial::QML() const
{
    return m_Instance;
}
