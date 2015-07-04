#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "QtAdMob/QtAdMobBanner.h"
#include "QtAdMob/QtAdMobInterstitial.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_Switch(false)
{
    ui->setupUi(this);

    m_Banner = CreateQtAdMobBanner();
    m_Banner->Initialize();
    m_Banner->SetUnitId("ca-app-pub-7485900711629006/8288667458");
    m_Banner->SetSize(IQtAdMobBanner::Banner);
    m_Banner->AddTestDevice("514ED2E95AD8EECE454CC5565326160A");
    m_Banner->Show();

    m_Interstitial = CreateQtAdMobInterstitial();
    m_Interstitial->LoadWithUnitId("ca-app-pub-7485900711629006/9462519453");
    m_Interstitial->AddTestDevice("514ED2E95AD8EECE454CC5565326160A");
    m_Interstitial->Show();

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(OnButtonOkClicked()));
}

MainWindow::~MainWindow()
{
    delete m_Banner;
    delete m_Interstitial;
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    UNUSED(event);
    QPoint position((width() - m_Banner->GetSizeInPixels().width()) * 0.5f, 0.0f);
    m_Banner->SetPosition(position);
}

void MainWindow::OnButtonOkClicked()
{
    bool isShowed = m_Banner->IsShow();
    if (!isShowed)
    {
        m_Banner->Show();
        ui->okButton->setText("Hide Banner");
    }
    else
    {
        m_Banner->Hide();
        ui->okButton->setText("Show Banner");
    }
}
