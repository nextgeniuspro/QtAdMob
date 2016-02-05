#include "QtAdMobInterstitialIos.h"

#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)

#include <GoogleMobileAds/GADInterstitial.h>
#include "IQtAdMobBanner.h"

class QtAdMobInterstitialIosProtected
{
public:
    QtAdMobInterstitialIosProtected() {};
    ~QtAdMobInterstitialIosProtected() {};

    static void OnLoaded(QtAdMobInterstitialIos* handler, bool status)
    {
        if (!handler)
        {
            return;
        }

        handler->OnStatusChanged(status);
    }

    static void OnLoading(QtAdMobInterstitialIos* handler)
    {
        if (!handler)
        {
            return;
        }

        handler->OnLoading();
    }

    static void OnWillPresent(QtAdMobInterstitialIos* handler)
    {
        if (!handler)
        {
            return;
        }

        handler->OnWillPresent();
    }

    static void OnClosed(QtAdMobInterstitialIos* handler)
    {
        if (!handler)
        {
            return;
        }

        handler->OnClosed();
    }
};

@interface QtAdMobInterstitialDelegate : NSObject<GADInterstitialDelegate>

@property (nonatomic, strong) GADInterstitial* interstitial;
@property (nonatomic, strong) NSMutableArray* testDevices;
@property (nonatomic, assign) QtAdMobInterstitialIos *handler;

- (id)initWithHandler:(QtAdMobInterstitialIos *)handler
             adUnitId:(NSString *)adUnitId;
- (void)load;

@end

@implementation QtAdMobInterstitialDelegate

- (id)initWithHandler:(QtAdMobInterstitialIos *)handler adUnitId:(NSString *)adUnitId
{
    self = [super init];
    if (self)
    {
        _handler = handler;
        _testDevices = [[NSMutableArray alloc] initWithArray:@[kGADSimulatorID]];
        _interstitial = [[GADInterstitial alloc] initWithAdUnitID:adUnitId];
        _interstitial.delegate = self;
    }
    return self;
}

- (void)dealloc
{
    _interstitial.delegate = nil;
    _handler = nullptr;
}

- (void)load
{
    GADRequest *request = [GADRequest request];
    request.testDevices = _testDevices;
    [_interstitial loadRequest:request];

    QtAdMobInterstitialIosProtected::OnLoading(self.handler);
}

- (void)show
{
    UIApplication *application = [UIApplication sharedApplication];
    UIWindow *window = [[application windows] firstObject];
    UIViewController* rootViewController = [window rootViewController];
    
    [_interstitial presentFromRootViewController:rootViewController];
}

- (void)interstitialDidReceiveAd:(GADInterstitial *)ad
{
    Q_UNUSED(ad);

    NSLog(@"Did success");

    QtAdMobInterstitialIosProtected::OnLoaded(self.handler, true);
}

- (void)interstitial:(GADInterstitial *)ad didFailToReceiveAdWithError:(GADRequestError *)error
{
    Q_UNUSED(ad);
    Q_UNUSED(error);

    NSLog(@"Did fail");
    
    QtAdMobInterstitialIosProtected::OnLoaded(self.handler, false);
}

- (void)interstitialWillPresentScreen:(GADInterstitial *)ad
{
    Q_UNUSED(ad);
    QtAdMobInterstitialIosProtected::OnWillPresent(self.handler);
}

- (void)interstitialDidDismissScreen:(GADInterstitial *)ad
{
    Q_UNUSED(ad);
    QtAdMobInterstitialIosProtected::OnClosed(self.handler);
}

@end

QtAdMobInterstitialIos::QtAdMobInterstitialIos()
    : m_AdMob(nil)
    , m_IsNeedToShow(false)
{
}

QtAdMobInterstitialIos::~QtAdMobInterstitialIos()
{
}

void QtAdMobInterstitialIos::LoadWithUnitId(const QString& unitId)
{
    if (IsValid() &&
        !m_AdMob.interstitial.hasBeenUsed)
    {
        return;
    }
    
    m_IsNeedToShow = false;

    m_AdMob = [[QtAdMobInterstitialDelegate alloc] initWithHandler:this
                    adUnitId:[NSString stringWithUTF8String:unitId.toUtf8().data()]];
    [m_AdMob load];
}

bool QtAdMobInterstitialIos::IsLoaded() const
{
    if (!IsValid())
    {
        return false;
    }

    return m_AdMob.interstitial.isReady;
}

void QtAdMobInterstitialIos::Show()
{    
    if (IsValid() && IsLoaded())
    {
        [m_AdMob show];
    }
    else
    {
        m_IsNeedToShow = true;
    }
}

void QtAdMobInterstitialIos::AddTestDevice(const QString& hashedDeviceId)
{
    NSString *deviceId = [NSString stringWithUTF8String:hashedDeviceId.toUtf8().data()];
    [m_AdMob.testDevices addObject:deviceId];
}

void QtAdMobInterstitialIos::OnStatusChanged(bool status)
{
    if (!status)
    {
        m_AdMob = nil;
    }
    else if (m_IsNeedToShow)
    {
        [m_AdMob show];
    }

    emit OnLoaded();
}

bool QtAdMobInterstitialIos::IsValid() const
{
    return (m_AdMob != nil);
}

#endif // TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
