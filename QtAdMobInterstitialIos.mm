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

        handler->onStatusChanged(status);
    }

    static void OnLoading(QtAdMobInterstitialIos* handler)
    {
        if (!handler)
        {
            return;
        }

        handler->loading();
    }

    static void OnWillPresent(QtAdMobInterstitialIos* handler)
    {
        if (!handler)
        {
            return;
        }

        handler->willPresent();
    }

    static void OnClosed(QtAdMobInterstitialIos* handler)
    {
        if (!handler)
        {
            return;
        }

        handler->closed();
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
    NSArray *windows = [application windows];
    UIViewController * __block rootViewController = nil;
    [windows enumerateObjectsUsingBlock:^(UIWindow * _Nonnull window, NSUInteger, BOOL * _Nonnull stop) {
        rootViewController = [window rootViewController];
        *stop = (rootViewController != nil);
    }];
    
    [_interstitial presentFromRootViewController:rootViewController];
}

- (void)interstitialDidReceiveAd:(GADInterstitial *)ad
{
    Q_UNUSED(ad);

    QtAdMobInterstitialIosProtected::OnLoaded(self.handler, true);
}

- (void)interstitial:(GADInterstitial *)ad didFailToReceiveAdWithError:(GADRequestError *)error
{
    Q_UNUSED(ad);
    Q_UNUSED(error);
    
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

void QtAdMobInterstitialIos::setUnitId(const QString& unitId)
{
    if (isValid() &&
        !m_AdMob.interstitial.hasBeenUsed)
    {
        return;
    }
    
    m_IsNeedToShow = false;

    QtAdMobInterstitialDelegate *delegate = [[QtAdMobInterstitialDelegate alloc] initWithHandler:this
                                                        adUnitId:[NSString stringWithUTF8String:unitId.toUtf8().data()]];
    m_AdMob = (__bridge QtAdMobInterstitialDelegate*)(__bridge_retained void*)delegate;
    [m_AdMob load];
    m_UnitId = unitId;
}

const QString& QtAdMobInterstitialIos::unitId() const
{
    return m_UnitId;
}

void QtAdMobInterstitialIos::setVisible(bool isVisible)
{
    if (!isVisible)
    {
        return; // TODO: implement hide
    }

    if (isValid() && isLoaded())
    {
        [m_AdMob show];
    }
    else
    {
        m_IsNeedToShow = true;
    }
}

bool QtAdMobInterstitialIos::visible()
{
    return false; // TODO: add implemention
}

bool QtAdMobInterstitialIos::isLoaded()
{
    if (!isValid())
    {
        return false;
    }

    return m_AdMob.interstitial.isReady;
}

void QtAdMobInterstitialIos::addTestDevice(const QString& hashedDeviceId)
{
    NSString *deviceId = [NSString stringWithUTF8String:hashedDeviceId.toUtf8().data()];
    [m_AdMob.testDevices addObject:deviceId];
}

void QtAdMobInterstitialIos::onStatusChanged(bool status)
{
    if (!status)
    {
        m_AdMob = nil;
    }
    else if (m_IsNeedToShow)
    {
        [m_AdMob show];
    }

    emit loaded();
}

bool QtAdMobInterstitialIos::isValid() const
{
    return (m_AdMob != nil);
}

#endif // TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
