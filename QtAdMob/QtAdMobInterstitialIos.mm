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
    _handler = nil;
}

- (void)load
{
    GADRequest *request = [GADRequest request];
    request.testDevices = _testDevices;
    [_interstitial loadRequest:request];
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

void QtAdMobInterstitialIos::OnLoad(bool status)
{
    if (!status)
    {
        m_AdMob = nil;
    }
    else if (m_IsNeedToShow)
    {
        [m_AdMob show];
    }
}

bool QtAdMobInterstitialIos::IsValid() const
{
    return (m_AdMob != nil);
}

#endif // TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
