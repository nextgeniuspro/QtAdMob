#include "QtAdMobBannerIos.h"

#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)

#include <GoogleMobileAds/GADBannerView.h>
#include <GoogleMobileAds/GADAdSize.h>

@interface QtAdMobBannerDelegate : NSObject<GADBannerViewDelegate>

@property (nonatomic, strong) GADBannerView* bannerView;
@property (nonatomic, strong) NSMutableArray* testDevices;
@property (nonatomic, assign) QtAdMobBannerIos *handler;

- (id)initWithHandler:(QtAdMobBannerIos *)handler;

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
    }
    return self;
}

- (void)dealloc
{
    _handler = nil;
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
    : m_Delegate(nil)
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

    UIApplication *application = [UIApplication sharedApplication];
    UIWindow *window = [[application windows] firstObject];
    UIViewController* rootViewController = [window rootViewController];
    UIView *view = rootViewController.view;
    
    m_Delegate = [[QtAdMobBannerDelegate alloc] initWithHandler:this];
    m_Delegate.bannerView.rootViewController = rootViewController;

    [view addSubview:m_Delegate.bannerView];
}

void QtAdMobBannerIos::Shutdown()
{
    if (!IsValid())
    {
        return;
    }
    
    [m_Delegate.bannerView removeFromSuperview];
    m_Delegate = nil;
}

void QtAdMobBannerIos::SetAdUnitId(const QString& unitId)
{
    if (!IsValid())
    {
        return;
    }
    
    m_Delegate.bannerView.adUnitID = [NSString stringWithUTF8String:unitId.toUtf8().data()];
    m_LoadingState = Idle;
}

void QtAdMobBannerIos::SetAdSize(IQtAdMobBanner::BannerSize size)
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
    
    if (!CGSizeEqualToSize(m_Delegate.bannerView.adSize.size, newSize.size) ||
        m_Delegate.bannerView.adSize.flags != newSize.flags)
    {
        m_Delegate.bannerView.adSize = newSize;
        m_LoadingState = Idle;
    }
}

void QtAdMobBannerIos::SetPosition(const QPoint& position)
{
    if (!IsValid())
    {
        return;
    }
    
    CGRect frame = m_Delegate.bannerView.frame;
    frame.origin = CGPointMake(position.x(), position.y());
    m_Delegate.bannerView.frame = frame;
}

QSize QtAdMobBannerIos::GetDimensions()
{
    if (!IsValid())
    {
        return QSize();
    }
    
    CGSize size = m_Delegate.bannerView.adSize.size;
    return QSize(size.width, size.height);
}

bool QtAdMobBannerIos::IsShow() const
{
    if (!IsValid())
    {
        return false;
    }
    
    return !m_Delegate.bannerView.hidden;
}

bool QtAdMobBannerIos::IsLoaded() const
{
    return (m_LoadingState == Loaded);
}

void QtAdMobBannerIos::ShowAd()
{
    if (!IsValid())
    {
        return;
    }
    
    if (m_LoadingState == Idle)
    {
        GADRequest *request = [GADRequest request];
        request.testDevices = m_Delegate.testDevices;
        [m_Delegate.bannerView loadRequest:request];
        m_LoadingState = Loading;
    }
    
    m_Delegate.bannerView.hidden = NO;
}

void QtAdMobBannerIos::HideAd()
{
    if (!IsValid())
    {
        return;
    }
    
    m_Delegate.bannerView.hidden = YES;
}

void QtAdMobBannerIos::AddTestDevice(const QString& hashedDeviceId)
{
    NSString *deviceId = [NSString stringWithUTF8String:hashedDeviceId.toUtf8().data()];
    [m_Delegate.testDevices addObject:deviceId];
    
    m_LoadingState = Idle;
}

void QtAdMobBannerIos::OnLoad(bool status)
{
    m_LoadingState = (status ? Loaded : Idle);
}

bool QtAdMobBannerIos::IsValid() const
{
    return (m_Delegate && m_Delegate.bannerView != nil);
}

#endif // TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
