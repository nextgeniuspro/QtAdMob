#include "QtAdMobBanner.h"
#ifdef QTADMOB_QML
#include <QtQml>
#endif

QmlAdMobBanner::QmlAdMobBanner()
{
    m_Instance = CreateQtAdMobBanner();

    connect(m_Instance, SIGNAL(loaded()), this, SIGNAL(loaded()));
    connect(m_Instance, SIGNAL(loading()), this, SIGNAL(loading()));
    connect(m_Instance, SIGNAL(closed()), this, SIGNAL(closed()));
    connect(m_Instance, SIGNAL(clicked()), this, SIGNAL(clicked()));
}

QmlAdMobBanner::~QmlAdMobBanner()
{
    delete m_Instance;
}

void QmlAdMobBanner::DeclareQML()
{
#ifdef QTADMOB_QML
    qmlRegisterType<QmlAdMobBanner>("com.dreamdev.QtAdMobBanner", 1, 0, "AdMobBanner");
#endif
}

void QmlAdMobBanner::setUnitId(const QString& unitId)
{
    QML()->setUnitId(unitId);

    emit unitIdChanged();
}

const QString& QmlAdMobBanner::unitId() const
{
    return QML()->unitId();
}

void QmlAdMobBanner::setSize(QmlAdMobBanner::Sizes size)
{
    QML()->setSize((IQtAdMobBanner::Sizes)size);

    emit sizeChanged();
}

QmlAdMobBanner::Sizes QmlAdMobBanner::size() const
{
    return (QmlAdMobBanner::Sizes)QML()->size();
}

QSize QmlAdMobBanner::sizeInPixels()
{
    return QML()->sizeInPixels();
}

int QmlAdMobBanner::width()
{
    return sizeInPixels().width();
}

int QmlAdMobBanner::height()
{
    return sizeInPixels().height();
}

void QmlAdMobBanner::setPosition(const QPoint& position)
{
    QML()->setPosition(position);

    emit positionChanged();
}

const QPoint& QmlAdMobBanner::position() const
{
    return QML()->position();
}

void QmlAdMobBanner::setX(int x)
{
    QML()->setPosition(QPoint(x, y()));

    emit positionChanged();
}

int QmlAdMobBanner::x()
{
    return QML()->position().x();
}

void QmlAdMobBanner::setY(int y)
{
    QML()->setPosition(QPoint(x(), y));

    emit positionChanged();
}

int QmlAdMobBanner::y()
{
    return QML()->position().y();
}

void QmlAdMobBanner::setVisible(bool isVisible)
{
    QML()->setVisible(isVisible);

    emit visibleChanged();
}

bool QmlAdMobBanner::visible()
{
    return QML()->visible();
}

bool QmlAdMobBanner::isLoaded()
{
    return QML()->isLoaded();
}

void QmlAdMobBanner::addTestDevice(const QString& hashedDeviceId)
{
    QML()->addTestDevice(hashedDeviceId);
}

IQtAdMobBanner* QmlAdMobBanner::QML() const
{
    return m_Instance;
}
