#include "QtAdMobInterstitialIos.h"

#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)

#include <GoogleMobileAds/GADInterstitial.h>
#include "IQtAdMobBanner.h"

@interface QtAdMobInterstitialDelegate : NSObject<GADInterstitialDelegate>

@property (nonatomic, strong) GADInterstitial* interstitial;
@property (nonatomic, strong) NSMutableArray* testDevices;
@property (nonatomic, assign) QtAdMobInterstitialIos *handler;

- (id)initWithHandler:(QtAdMobInterstitialIos *)handler
             adUnitId:(NSString *)adUnitId;

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
    _handler = nil;
}

- (void)interstitialDidReceiveAd:(GADInterstitial *)ad
{
    UNUSED(ad);
    
    if (self.handler)
    {
        self.handler->OnLoad(true);
    }
}

- (void)interstitial:(GADInterstitial *)ad didFailToReceiveAdWithError:(GADRequestError *)error
{
    UNUSED(ad);
    UNUSED(error);
    
    if (self.handler)
    {
        self.handler->OnLoad(false);
    }
}

@end

QtAdMobInterstitialIos::QtAdMobInterstitialIos()
    : m_Delegate(nil)
    , m_IsNeedToShow(false)
{
}

QtAdMobInterstitialIos::~QtAdMobInterstitialIos()
{
}

void QtAdMobInterstitialIos::LoadWithAdUnitId(const QString& unitId)
{
    if (IsValid() &&
        !m_Delegate.interstitial.hasBeenUsed)
    {
        return;
    }
    
    m_IsNeedToShow = false;

    m_Delegate = [[QtAdMobInterstitialDelegate alloc] initWithHandler:this
                    adUnitId:[NSString stringWithUTF8String:unitId.toUtf8().data()]];

    GADRequest *request = [GADRequest request];
    request.testDevices = m_Delegate.testDevices;
    [m_Delegate.interstitial loadRequest:request];
}

bool QtAdMobInterstitialIos::IsLoaded() const
{
    if (!IsValid())
    {
        return false;
    }

    return m_Delegate.interstitial.isReady;
}

void QtAdMobInterstitialIos::ShowAd()
{    
    if (IsValid() && IsLoaded())
    {
        UIApplication *application = [UIApplication sharedApplication];
        UIWindow *window = [[application windows] firstObject];
        UIViewController* rootViewController = [window rootViewController];

        [m_Delegate.interstitial presentFromRootViewController:rootViewController];
    }
    else
    {
        m_IsNeedToShow = true;
    }
}

void QtAdMobInterstitialIos::AddTestDevice(const QString& hashedDeviceId)
{
    NSString *deviceId = [NSString stringWithUTF8String:hashedDeviceId.toUtf8().data()];
    [m_Delegate.testDevices addObject:deviceId];
}

void QtAdMobInterstitialIos::OnLoad(bool status)
{
    if (!status)
    {
        m_Delegate = nil;
    }
    else if (m_IsNeedToShow)
    {
        UIApplication *application = [UIApplication sharedApplication];
        UIWindow *window = [[application windows] firstObject];
        UIViewController* rootViewController = [window rootViewController];

        [m_Delegate.interstitial presentFromRootViewController:rootViewController];
    }
}

bool QtAdMobInterstitialIos::IsValid() const
{
    return (m_Delegate != nil);
}

#endif // TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
