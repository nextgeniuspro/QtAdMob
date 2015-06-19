#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "QtAdMob/QtAdMobBanner.h"
#include "QtAdMob/QtAdMobInterstitial.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_Banner(0)
    , m_Switch(false)
{
    ui->setupUi(this);

    m_Banner = CreateQtAdMobBanner();
    m_Banner->Initialize();
    m_Banner->SetAdUnitId("ca-app-pub-7485900711629006/8288667458");
    m_Banner->SetAdSize(IQtAdMobBanner::Banner);
    m_Banner->AddTestDevice("514ED2E95AD8EECE454CC5565326160A");
    m_Banner->ShowAd();

    m_Interstitial = CreateQtAdMobInterstitial();
    m_Interstitial->LoadWithAdUnitId("ca-app-pub-7485900711629006/9462519453");
    m_Interstitial->AddTestDevice("514ED2E95AD8EECE454CC5565326160A");
    m_Interstitial->ShowAd();

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(OnButtonOkClicked()));
}

MainWindow::~MainWindow()
{
    m_Banner->Shutdown();
    delete m_Banner;
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    UNUSED(event);
    QPoint position((width() - m_Banner->GetDimensions().width()) * 0.5f, 50.0f);
    m_Banner->SetPosition(position);
}

void MainWindow::OnButtonOkClicked()
{
    bool isShowed = m_Banner->IsShow();
    if (!isShowed)
    {
        m_Banner->ShowAd();
        ui->okButton->setText("Hide Banner");
    }
    else
    {
        m_Banner->HideAd();
        ui->okButton->setText("Show Banner");
    }
}
