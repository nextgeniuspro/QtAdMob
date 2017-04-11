#include "QtAdMobBannerIos.h"

#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)

#include <GoogleMobileAds/GADBannerView.h>
#include <GoogleMobileAds/GADAdSize.h>
#include <GoogleMobileAds/GADMobileAds.h>

class QtAdMobBannerIosProtected
{
public:
    QtAdMobBannerIosProtected() {};
    ~QtAdMobBannerIosProtected() {};

    static void OnLoaded(QtAdMobBannerIos* handler, bool status)
    {
        if (!handler)
        {
            return;
        }

        handler->onStatusChanged(status);
    }

    static void OnLoading(QtAdMobBannerIos* handler)
    {
        if (!handler)
        {
            return;
        }

        handler->loading();
    }

    static void OnClosed(QtAdMobBannerIos* handler)
    {
        if (!handler)
        {
            return;
        }

        handler->closed();
    }

    static void OnWillLeaveApplication(QtAdMobBannerIos* handler)
    {
        if (!handler)
        {
            return;
        }

        handler->clicked();
    }
};

@interface QtAdMobBannerDelegate : NSObject<GADBannerViewDelegate>

@property (nonatomic, strong) GADBannerView* bannerView;
@property (nonatomic, strong) NSMutableArray* testDevices;
@property (nonatomic, assign) QtAdMobBannerIos *handler;
@property (nonatomic, strong) GADRequest *request;

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
        NSArray *windows = [application windows];
        UIViewController * __block rootViewController = nil;
        [windows enumerateObjectsUsingBlock:^(UIWindow * _Nonnull window, NSUInteger, BOOL * _Nonnull stop) {
            rootViewController = [window rootViewController];
            *stop = (rootViewController != nil);
        }];
        UIView *view = rootViewController.view;
        
        _bannerView.rootViewController = rootViewController;
        _bannerView.autoloadEnabled = YES;
        [view addSubview:_bannerView];

        _request = [GADRequest request];
    }
    return self;
}

- (void)dealloc
{
    _handler = nil;
}

- (void)load
{
    QtAdMobBannerIosProtected::OnLoading(self.handler);

    _request.testDevices = _testDevices;
    [_bannerView loadRequest:_request];
}

- (void)adViewDidReceiveAd:(GADBannerView *)view
{
    Q_UNUSED(view);
    
    QtAdMobBannerIosProtected::OnLoaded(self.handler, true);
}

- (void)adView:(GADBannerView *)view didFailToReceiveAdWithError:(GADRequestError *)error
{
    Q_UNUSED(view);
    Q_UNUSED(error);

    QtAdMobBannerIosProtected::OnLoaded(self.handler, false);
}

- (void)adViewDidDismissScreen:(GADBannerView *)bannerView
{
    Q_UNUSED(bannerView);

    QtAdMobBannerIosProtected::OnClosed(self.handler);
}

- (void)adViewWillLeaveApplication:(GADBannerView *)bannerView
{
    Q_UNUSED(bannerView);

    QtAdMobBannerIosProtected::OnWillLeaveApplication(self.handler);
}

@end

QtAdMobBannerIos::QtAdMobBannerIos(QObject* parent)
    : IQtAdMobBanner(parent)
    , m_BannerSize(IQtAdMobBanner::Banner)
    , m_LoadingState(Idle)
{
    QtAdMobBannerDelegate *delegate = [[QtAdMobBannerDelegate alloc] initWithHandler:this];
    m_AdMob = (__bridge QtAdMobBannerDelegate*)(__bridge_retained void*)delegate;
}

QtAdMobBannerIos::~QtAdMobBannerIos()
{
    m_AdMob = nil;
}

void QtAdMobBannerIos::setUnitId(const QString& unitId)
{
    if (!isValid())
    {
        return;
    }
    
    m_AdMob.bannerView.adUnitID = [NSString stringWithUTF8String:unitId.toUtf8().data()];
    m_LoadingState = Idle;
}

const QString& QtAdMobBannerIos::unitId() const
{
    return m_UnitId;
}

void QtAdMobBannerIos::setSize(IQtAdMobBanner::Sizes size)
{
    if (!isValid())
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
    m_BannerSize = size;

    if (!CGSizeEqualToSize(m_AdMob.bannerView.adSize.size, newSize.size) ||
        m_AdMob.bannerView.adSize.flags != newSize.flags)
    {
        m_AdMob.bannerView.adSize = newSize;
        m_LoadingState = Idle;
    }
}

IQtAdMobBanner::Sizes QtAdMobBannerIos::size() const
{
    return m_BannerSize;
}

QSize QtAdMobBannerIos::sizeInPixels()
{
    if (!isValid())
    {
        return QSize();
    }

    CGSize size = m_AdMob.bannerView.adSize.size;
    return QSize(size.width, size.height);
}

void QtAdMobBannerIos::setPosition(const QPoint& position)
{
    if (!isValid())
    {
        return;
    }
    
    CGFloat yOffset = [UIApplication sharedApplication].statusBarFrame.size.height;

    CGRect frame = m_AdMob.bannerView.frame;
    frame.origin = CGPointMake(position.x(), position.y() + yOffset);
    m_AdMob.bannerView.frame = frame;

    m_Position = position;
}

const QPoint& QtAdMobBannerIos::position() const
{
    return m_Position;
}

void QtAdMobBannerIos::setVisible(bool isVisible)
{
    if (!isValid())
    {
        return;
    }

    if (m_LoadingState == Idle)
    {
        m_LoadingState = Loading;
        [m_AdMob load];
    }

    m_AdMob.bannerView.hidden = !isVisible;
}

bool QtAdMobBannerIos::visible()
{
    if (!isValid())
    {
        return false;
    }
    
    return !m_AdMob.bannerView.hidden;
}

bool QtAdMobBannerIos::isLoaded()
{
    return (m_LoadingState == Loaded);
}

void QtAdMobBannerIos::addTestDevice(const QString& hashedDeviceId)
{
    NSString *deviceId = [NSString stringWithUTF8String:hashedDeviceId.toUtf8().data()];
    [m_AdMob.testDevices addObject:deviceId];

    m_LoadingState = Idle;
}

void QtAdMobBannerIos::onStatusChanged(bool status)
{
    m_LoadingState = (status ? Loaded : Idle);

    emit loaded();
}

bool QtAdMobBannerIos::isValid() const
{
    return (m_AdMob && m_AdMob.bannerView != nil);
}

#endif // TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
