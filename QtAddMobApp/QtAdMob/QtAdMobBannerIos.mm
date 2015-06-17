#include "QtAdMobBannerIos.h"

#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)

#include <GoogleMobileAds/GADBannerView.h>
#include <GoogleMobileAds/GADAdSize.h>
#include <QWidget>

@interface QtAdMobBannerDelegate : NSObject<GADBannerViewDelegate>

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
    }
    return self;
}

- (void)dealloc
{
    _handler = nil;
    [super dealloc];
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

QtAdMobBannerIos::QtAdMobBannerIos(QWidget* parent)
    : m_BannerView(0)
    , m_Delegate(0)
    , m_TestDevices(0)
    , m_Parent(parent)
    , m_IsLoaded(false)
{
    m_TestDevices = [[NSMutableArray alloc] initWithArray:@[kGADSimulatorID]];
}

QtAdMobBannerIos::~QtAdMobBannerIos()
{
    [m_TestDevices release];
    
    Shutdown();
}

void QtAdMobBannerIos::Initialize()
{
    if (IsValid())
    {
        return;
    }

    UIWindow *window = [[[UIApplication sharedApplication] windows] firstObject];
    UIViewController* rootViewController = [window rootViewController];
    
    UIView *view = rootViewController.view;//reinterpret_cast<UIView *>(m_Parent->winId());
    //UIViewController *qtController = [[view window] rootViewController];
    
    m_Delegate = [[QtAdMobBannerDelegate alloc] initWithHandler:this];
    
    m_BannerView = [[GADBannerView alloc] initWithAdSize:kGADAdSizeBanner];
    m_BannerView.rootViewController = rootViewController;
    m_BannerView.delegate = m_Delegate;

    [view addSubview:m_BannerView];
}

void QtAdMobBannerIos::Shutdown()
{
    if (!IsValid())
    {
        return;
    }
    
    m_BannerView.delegate = nil;
    [m_BannerView removeFromSuperview];
    [m_BannerView release];
    [m_Delegate release];
}

void QtAdMobBannerIos::SetAdUnitId(const QString& unitId)
{
    if (!IsValid())
    {
        return;
    }
    
    m_BannerView.adUnitID = [NSString stringWithUTF8String:unitId.toUtf8().data()];
    m_IsLoaded = false;
}

void QtAdMobBannerIos::SetAdSize(IQtAdMobBanner::BannerSize size)
{
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
        /*case 6:
            newSize = kGADAdSizeSmartBannerPortrait;
            break;
        case 7:
            newSize = kGADAdSizeLeaderboard;
            break;
        case 8:
            newSize = kGADAdSizeInvalid;
            break;*/
            
        default:
            break;
    }
    
    if (!CGSizeEqualToSize(m_BannerView.adSize.size, newSize.size) ||
        m_BannerView.adSize.flags != newSize.flags)
    {
        m_BannerView.adSize = newSize;
        m_IsLoaded = false;
    }
}

void QtAdMobBannerIos::SetPosition(const QPoint& position)
{
    if (!IsValid())
    {
        return;
    }
    
    CGRect frame = m_BannerView.frame;
    frame.origin = CGPointMake(position.x(), position.y());
    m_BannerView.frame = frame;
}

QSize QtAdMobBannerIos::GetDimensions()
{
    if (!IsValid())
    {
        return QSize();
    }
    
    CGSize size = m_BannerView.adSize.size;
    return QSize(size.width, size.height);
}

bool QtAdMobBannerIos::IsShowed() const
{
    if (!IsValid())
    {
        return false;
    }
    
    return !m_BannerView.hidden;
}

bool QtAdMobBannerIos::IsLoaded() const
{
    return m_IsLoaded;
}

void QtAdMobBannerIos::ShowAd()
{
    if (!IsValid())
    {
        return;
    }
    
    if (!IsLoaded())
    {
        GADRequest *request = [GADRequest request];
        request.testDevices = m_TestDevices;
        [m_BannerView loadRequest:request];
    }
    
    m_BannerView.hidden = NO;
}

void QtAdMobBannerIos::HideAd()
{
    if (!IsValid())
    {
        return;
    }
    
    m_BannerView.hidden = YES;
}

void QtAdMobBannerIos::AddTestDevice(const QString& hashedDeviceId)
{
    NSString *deviceId = [NSString stringWithUTF8String:hashedDeviceId.toUtf8().data()];
    [m_TestDevices addObject:deviceId];
    
    m_IsLoaded = false;
}

void QtAdMobBannerIos::OnLoad(bool status)
{
    m_IsLoaded = status;
}

bool QtAdMobBannerIos::IsValid() const
{
    return (m_BannerView != nil);
}

#endif // TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
