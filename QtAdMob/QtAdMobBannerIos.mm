#include "QtAdMobBannerIos.h"

#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)

#include <GoogleMobileAds/GADBannerView.h>
#include <GoogleMobileAds/GADAdSize.h>

@interface QtAdMobBannerDelegate : NSObject<GADBannerViewDelegate>

@property (nonatomic, strong) GADBannerView* bannerView;
@property (nonatomic, strong) NSMutableArray* testDevices;
@property (nonatomic, assign) QtAdMobBannerIos *handler;

- (id)initWithHandler:(QtAdMobBannerIos *)handler;
- (void)load;

@end

@implementation QtAdMobBannerDelegate

- (id)initWithHandler:(QtAdMobBannerIos *)handler
{
    self = [super init];
    if (self)
    {
        _handler = handler;
        _testDevices = [[NSMutableArray alloc] initWithArray:@[kGADSimulatorID]];
        _bannerView = [[GADBannerView alloc] initWithAdSize:kGADAdSizeBanner];
        _bannerView.delegate = self;
        
        UIApplication *application = [UIApplication sharedApplication];
        UIWindow *window = [[application windows] firstObject];
        UIViewController* rootViewController = [window rootViewController];
        UIView *view = rootViewController.view;
        
        _bannerView.rootViewController = rootViewController;
        [view addSubview:_bannerView];
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
    [_bannerView loadRequest:request];
}

- (void)adViewDidReceiveAd:(GADBannerView *)view
{
    UNUSED(view);
    
    if (self.handler)
    {
        self.handler->OnLoad(true);
    }
}

- (void)adView:(GADBannerView *)view didFailToReceiveAdWithError:(GADRequestError *)error
{
    UNUSED(view);
    UNUSED(error);
    
    if (self.handler)
    {
        self.handler->OnLoad(false);
    }
}

@end

QtAdMobBannerIos::QtAdMobBannerIos()
    : m_AdMob(nil)
    , m_LoadingState(Idle)
{
}

QtAdMobBannerIos::~QtAdMobBannerIos()
{
    Shutdown();
}

void QtAdMobBannerIos::Initialize()
{
    if (IsValid())
    {
        return;
    }
    
    
    m_AdMob = [[QtAdMobBannerDelegate alloc] initWithHandler:this];
}

void QtAdMobBannerIos::Shutdown()
{
    if (!IsValid())
    {
        return;
    }
    
    m_AdMob = nil;
}

void QtAdMobBannerIos::SetUnitId(const QString& unitId)
{
    if (!IsValid())
    {
        return;
    }
    
    m_AdMob.bannerView.adUnitID = [NSString stringWithUTF8String:unitId.toUtf8().data()];
    m_LoadingState = Idle;
}

void QtAdMobBannerIos::SetSize(IQtAdMobBanner::BannerSize size)
{
    if (!IsValid())
    {
        return;
    }
    
    GADAdSize newSize = kGADAdSizeBanner;
    switch (size)
    {
        case Banner:
            newSize = kGADAdSizeBanner;
            break;
        case LargeBanner:
            newSize = kGADAdSizeLargeBanner;
            break;
        case MediumRectangle:
            newSize = kGADAdSizeMediumRectangle;
            break;
        case FullBanner:
            newSize = kGADAdSizeFullBanner;
            break;
        case SmartBanner:
            newSize = kGADAdSizeSmartBannerLandscape;
            break;
        case WideSkyscraper:
            newSize = kGADAdSizeSkyscraper;
            break;
    }
    
    if (!CGSizeEqualToSize(m_AdMob.bannerView.adSize.size, newSize.size) ||
        m_AdMob.bannerView.adSize.flags != newSize.flags)
    {
        m_AdMob.bannerView.adSize = newSize;
        m_LoadingState = Idle;
    }
}

QSize QtAdMobBannerIos::GetSizeInPixels()
{
    if (!IsValid())
    {
        return QSize();
    }

    CGSize size = m_AdMob.bannerView.adSize.size;
    return QSize(size.width, size.height);
}

void QtAdMobBannerIos::SetPosition(const QPoint& position)
{
    if (!IsValid())
    {
        return;
    }
    
    CGFloat yOffset = [UIApplication sharedApplication].statusBarFrame.size.height;

    CGRect frame = m_Delegate.bannerView.frame;
    frame.origin = CGPointMake(position.x(), position.y() + yOffset);
    m_Delegate.bannerView.frame = frame;
}

bool QtAdMobBannerIos::IsShow() const
{
    if (!IsValid())
    {
        return false;
    }
    
    return !m_AdMob.bannerView.hidden;
}

bool QtAdMobBannerIos::IsLoaded() const
{
    return (m_LoadingState == Loaded);
}

void QtAdMobBannerIos::Show()
{
    if (!IsValid())
    {
        return;
    }
    
    if (m_LoadingState == Idle)
    {
        [m_AdMob load];
        m_LoadingState = Loading;
    }
    
    m_AdMob.bannerView.hidden = NO;
}

void QtAdMobBannerIos::Hide()
{
    if (!IsValid())
    {
        return;
    }
    
    m_AdMob.bannerView.hidden = YES;
}

void QtAdMobBannerIos::AddTestDevice(const QString& hashedDeviceId)
{
    NSString *deviceId = [NSString stringWithUTF8String:hashedDeviceId.toUtf8().data()];
    [m_AdMob.testDevices addObject:deviceId];
    
    m_LoadingState = Idle;
}

void QtAdMobBannerIos::OnLoad(bool status)
{
    m_LoadingState = (status ? Loaded : Idle);
}

bool QtAdMobBannerIos::IsValid() const
{
    return (m_AdMob && m_AdMob.bannerView != nil);
}

#endif // TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
