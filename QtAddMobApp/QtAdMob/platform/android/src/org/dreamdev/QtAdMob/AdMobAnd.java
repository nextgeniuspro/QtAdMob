package org.dreamdev.QtAdMob;

import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;

import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.InterstitialAd;

import org.qtproject.qt5.android.bindings.QtActivity;

import java.util.ArrayList;

/**
 * Created by moisex on 9/7/15.
 */
public class AdMobAnd
{
    private QtActivity m_AdMobActivity = null;
    private ViewGroup m_ViewGroup;
    private AdView m_AdBannerView;
    private InterstitialAd m_AdInterstitial;
    private boolean m_IsAdBannerShowed = false;
    private boolean m_IsAdInterstitiaNeedToShow = false;
    private boolean m_IsAdBannerLoaded = false;
    private boolean m_IsAdInterstitialLoaded = false;
    private ArrayList<String> m_TestDevices = new ArrayList<String>();
    private int m_AdBannerWidth = 0;
    private int m_AdBannerHeight = 0;
    private int m_StatusBarHeight = 0;

    public AdMobAnd(QtActivity qtAct)
    {
        m_AdMobActivity = qtAct;
    }

    private int GetStatusBarHeight()
    {
        int result = 0;
        int resourceId = m_AdMobActivity.getResources().getIdentifier("status_bar_height", "dimen", "android");
        if (resourceId > 0) {
            result = m_AdMobActivity.getResources().getDimensionPixelSize(resourceId);
        }
        return result;
    }

    public void SetAdBannerUnitId(final String adId)
    {
        m_AdMobActivity.runOnUiThread(new Runnable() {
            public void run() {
                m_AdBannerView.setAdUnitId(adId);
            }
        });
    }

    public void SetAdBannerSize(final int size)
    {
        final QtActivity self = m_AdMobActivity;
        self.runOnUiThread(new Runnable() {
            public void run() {
                AdSize adSize = AdSize.BANNER;
                switch (size) {
                    case 0:
                        adSize = AdSize.BANNER;
                        break;
                    case 1:
                        adSize = AdSize.FULL_BANNER;
                        break;
                    case 2:
                        adSize = AdSize.LARGE_BANNER;
                        break;
                    case 3:
                        adSize = AdSize.MEDIUM_RECTANGLE;
                        break;
                    case 4:
                        adSize = AdSize.SMART_BANNER;
                        break;
                    case 5:
                        adSize = AdSize.WIDE_SKYSCRAPER;
                        break;
                }
                ;

                m_AdBannerView.setAdSize(adSize);
                m_AdBannerWidth = adSize.getWidthInPixels(self);
                m_AdBannerHeight = adSize.getHeightInPixels(self);
            }
        });
    }

    public void SetAdBannerPosition(final int x, final int y)
    {
        m_AdMobActivity.runOnUiThread(new Runnable() {
            public void run() {
                FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.WRAP_CONTENT,
                        FrameLayout.LayoutParams.WRAP_CONTENT);
                m_AdBannerView.setLayoutParams(layoutParams);
                m_AdBannerView.setX(x);
                m_AdBannerView.setY(y + m_StatusBarHeight);
            }
        });
    }

    public void AddAdTestDevice(final String deviceId)
    {
        m_AdMobActivity.runOnUiThread(new Runnable() {
            public void run() {
                m_TestDevices.add(deviceId);
            }
        });
    }

    public boolean IsAdBannerShowed()
    {
        return m_IsAdBannerShowed;
    }

    public boolean IsAdBannerLoaded()
    {
        return m_IsAdBannerLoaded;
    }

    public int GetAdBannerWidth()
    {
        return m_AdBannerWidth;
    }

    public int GetAdBannerHeight()
    {
        return m_AdBannerHeight;
    }

    public void ShowAdBanner()
    {
        m_AdMobActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (IsAdBannerShowed()) {
                    return;
                }

                if (!IsAdBannerLoaded()) {
                    AdRequest.Builder adRequest = new AdRequest.Builder();
                    adRequest.addTestDevice(AdRequest.DEVICE_ID_EMULATOR);
                    for (String deviceId : m_TestDevices) {
                        adRequest.addTestDevice(deviceId);
                    }
                    m_AdBannerView.loadAd(adRequest.build());
                }
                m_AdBannerView.setVisibility(View.VISIBLE);
                m_IsAdBannerShowed = true;
            }
        });
    }

    public void HideAdBanner()
    {
        m_AdMobActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (!IsAdBannerShowed()) {
                    return;
                }

                m_AdBannerView.setVisibility(View.GONE);
                m_IsAdBannerShowed = false;
            }
        });
    }

    public void InitializeAdBanner()
    {
        final QtActivity self = m_AdMobActivity;
        m_AdMobActivity.runOnUiThread(new Runnable() {
            public void run() {
                if (m_AdBannerView != null) {
                    return;
                }

                m_StatusBarHeight = GetStatusBarHeight();

                m_AdBannerView = new AdView(self);
                m_AdBannerView.setVisibility(View.GONE);

                View view = m_AdMobActivity.getWindow().getDecorView().getRootView();
                if (view instanceof ViewGroup) {
                    m_ViewGroup = (ViewGroup) view;

                    FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.WRAP_CONTENT,
                            FrameLayout.LayoutParams.WRAP_CONTENT);
                    m_AdBannerView.setLayoutParams(layoutParams);
                    m_AdBannerView.setX(0);
                    m_AdBannerView.setY(m_StatusBarHeight);
                    m_ViewGroup.addView(m_AdBannerView);

                    m_AdBannerView.setAdListener(new AdListener() {
                        public void onAdLoaded() {
                            m_IsAdBannerLoaded = true;
                        }
                    });
                }
            }
        });
    }

    public void ShutdownAdBanner()
    {
        m_AdMobActivity.runOnUiThread(new Runnable() {
            public void run() {
                if (m_AdBannerView == null) {
                    return;
                }

                m_IsAdBannerShowed = false;
                m_ViewGroup.removeView(m_AdBannerView);
                m_AdBannerView = null;
            }
        });
    }

    public void LoadAdInterstitialWithUnitId(final String adId)
    {
        final QtActivity self = m_AdMobActivity;
        m_AdMobActivity.runOnUiThread(new Runnable() {
            public void run() {
                m_IsAdInterstitialLoaded = false;
                m_IsAdInterstitiaNeedToShow = false;

                m_AdInterstitial = new InterstitialAd(self);
                m_AdInterstitial.setAdUnitId(adId);
                m_AdInterstitial.setAdListener(new AdListener() {
                    public void onAdLoaded() {
                        m_IsAdInterstitialLoaded = true;
                        ShowAdInterstitial();
                    }
                });

                AdRequest.Builder adRequest = new AdRequest.Builder();
                adRequest.addTestDevice(AdRequest.DEVICE_ID_EMULATOR);
                for (String deviceId : m_TestDevices) {
                    adRequest.addTestDevice(deviceId);
                }
                m_AdInterstitial.loadAd(adRequest.build());
            }
        });
    }

    public boolean IsAdInterstitialLoaded()
    {
        return m_IsAdInterstitialLoaded;
    }

    public void ShowAdInterstitial()
    {
        m_AdMobActivity.runOnUiThread(new Runnable()
        {
            public void run()
            {
                if (m_IsAdInterstitialLoaded)
                {
                    m_AdInterstitial.show();
                    m_IsAdInterstitialLoaded = false; // Ad might be presented only once, need reload
                }
                else
                {
                    m_IsAdInterstitiaNeedToShow = true;
                }
            }
        });
    }

    public void createBanner()
    {

    }


    public void pauseBanner()
    {
        if (m_AdBannerView != null)
        {
            m_AdBannerView.pause();
        }
    }

    public void resumeBanner()
    {
        if (m_AdBannerView != null)
        {
            m_AdBannerView.resume();
        }
    }

    public void destroyBanner()
    {
        if (m_AdBannerView != null)
        {
            m_AdBannerView.destroy();
        }
    }
}

