#ifndef QTADMOBBANNERIOS_H
#define QTADMOBBANNERIOS_H

#include "IQtAdMobBanner.h"

#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)

#include <QStringList>

class QWidget;
class QAndroidJniObject;
#if defined(__OBJC__)
@class GADBannerView;
@class QtAdMobBannerDelegate;
@class NSMutableArray;
#endif

class QtAdMobBannerIos : public IQtAdMobBanner
{
public:
    QtAdMobBannerIos(QWidget* parent = 0);
    virtual ~QtAdMobBannerIos();

    virtual void Initialize();
    virtual void Shutdown();

    virtual void SetAdUnitId(const QString& unitId);
    virtual void SetAdSize(BannerSize size);
    virtual void SetPosition(const QPoint& position);
    virtual QSize GetDimensions();
    virtual bool IsShowed() const;
    virtual bool IsLoaded() const;
    virtual void ShowAd();
    virtual void HideAd();

    virtual void AddTestDevice(const QString& hashedDeviceId);

    // For internal purpose only
    void OnLoad(bool status);
    
private:
    bool IsValid() const;

private:
#if defined(__OBJC__)
    GADBannerView* m_BannerView;
    QtAdMobBannerDelegate* m_Delegate;
    NSMutableArray* m_TestDevices;
#endif
    QWidget* m_Parent;
    bool m_IsLoaded;
};

#endif // TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR

#endif // QTADMOBBANNERIOS_H
