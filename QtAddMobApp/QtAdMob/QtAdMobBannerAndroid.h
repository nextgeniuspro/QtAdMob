#ifndef QTADMOBBANNERANDROID_H
#define QTADMOBBANNERANDROID_H

#include "IQtAdMobBanner.h"

#if (__ANDROID_API__ >= 9)

class QAndroidJniObject;

class QtAdMobBannerAndroid : public IQtAdMobBanner
{
public:
    QtAdMobBannerAndroid();
    virtual ~QtAdMobBannerAndroid();

    virtual void Initialize();
    virtual void Shutdown();

    virtual void SetUnitId(const QString& unitId);
    virtual void SetSize(BannerSize size);
    virtual QSize GetSizeInPixels();
    virtual void SetPosition(const QPoint& position);
    virtual bool IsShow() const;
    virtual bool IsLoaded() const;
    virtual void Show();
    virtual void Hide();

    virtual void AddTestDevice(const QString& hashedDeviceId);

private:
    bool IsValid() const;

private:
    QAndroidJniObject* m_Activity;
};

#endif // __ANDROID_API__

#endif // QTADMOBBANNERANDROID_H
