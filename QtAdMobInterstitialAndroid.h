#ifndef QTADMOBINTERSTITIALANDROID_H
#define QTADMOBINTERSTITIALANDROID_H

#include "IQtAdMobInterstitial.h"

#if (__ANDROID_API__ >= 9)

class QAndroidJniObject;

class QtAdMobInterstitialAndroid : public IQtAdMobInterstitial
{
public:
    typedef QMap<uint32_t, QtAdMobInterstitialAndroid*> TInstances;

    QtAdMobInterstitialAndroid();
    virtual ~QtAdMobInterstitialAndroid();

    virtual void LoadWithUnitId(const QString& unitId);
    virtual bool IsLoaded() const;
    virtual void Show();

    virtual void AddTestDevice(const QString& hashedDeviceId);
    
    static const TInstances& Instances();

private:
    bool IsValid() const;

private:
    QAndroidJniObject* m_Activity;
    int m_Index;
    static int s_Index;
    static TInstances s_Instances;
};

#endif // __ANDROID_API__

#endif // QTADMOBINTERSTITIALANDROID_H
