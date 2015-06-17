package org.dreamdev.QtAdMob;

import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.AdListener;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.util.Log;
import org.qtproject.qt5.android.bindings.QtActivity;
import org.qtproject.qt5.android.bindings.QtApplication;
import java.util.ArrayList;
import android.widget.FrameLayout;

public class QtAdMobActivity extends QtActivity
{
    private ViewGroup m_ViewGroup;
    private AdView m_AdView;
    private boolean m_IsShowed = false;
    private boolean m_IsLoaded = false;
    private ArrayList<String> m_TestDevices = new ArrayList<String>();
    private int m_AdWidth = 0;
    private int m_AdHeight = 0;

    public void SetAdUnitId(final String adId)
    {
        runOnUiThread(new Runnable()
        {
            public void run() 
            {
                m_AdView.setAdUnitId(adId);
            }
        });
    }

    public void SetAdSize(final int size)
    {
        final QtAdMobActivity self = this;
        runOnUiThread(new Runnable()
        {
            public void run() 
            {
                AdSize adSize = AdSize.BANNER;
                switch(size)
                {
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
                };

                m_AdView.setAdSize(adSize);
                m_AdWidth = adSize.getWidthInPixels(self);
                m_AdHeight = adSize.getHeightInPixels(self);
            }
        });
    }

    public void SetAdPosition(final int x, final int y)
    {
        runOnUiThread(new Runnable()
        {
            public void run()
            {
                FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.WRAP_CONTENT,
                                                                                     FrameLayout.LayoutParams.WRAP_CONTENT);
                m_AdView.setLayoutParams(layoutParams);
                m_AdView.setX(x);
                m_AdView.setY(y);
            }
        });
    }

    public void AddAdTestDevice(final String deviceId)
    {
        runOnUiThread(new Runnable()
        {
            public void run() 
            {
                m_TestDevices.add(deviceId);
            }
        });
    }

    public boolean IsShowed()
    {
        return m_IsShowed;
    }

    public boolean IsLoaded()
    {
        return m_IsLoaded;
    }

    public int GetAdWidth()
    {
        return m_AdWidth;
    }

    public int GetAdHeight()
    {
        return m_AdHeight;
    }

    public void ShowAd()
    {
        runOnUiThread(new Runnable()
        {
            @Override
            public void run()
            {
                if (IsShowed())
                {
                    return;
                }

                if (!IsLoaded())
                {
                    AdRequest.Builder adRequest = new AdRequest.Builder();
                    adRequest.addTestDevice(AdRequest.DEVICE_ID_EMULATOR);
                    for (String deviceId : m_TestDevices) 
                    {
                        adRequest.addTestDevice(deviceId);
                    }
                    m_AdView.loadAd(adRequest.build());
                }
                m_AdView.setVisibility(View.VISIBLE);
                m_IsShowed = true;
            }
        });
    }

    public void HideAd()
    {
        runOnUiThread(new Runnable()
        {
            @Override
            public void run()
            {
                if (!IsShowed())
                {
                    return;
                }

                m_AdView.setVisibility(View.GONE);
                m_IsShowed = false;
            }
        });
    }

    public void InitializeAd()
    {
        final QtAdMobActivity self = this;
        runOnUiThread(new Runnable()
        {
            public void run() 
            {
                if (m_AdView != null)
                {
                    return;
                }

                m_AdView = new AdView(self);
                m_AdView.setVisibility(View.GONE);

                View view = getWindow().getDecorView().getRootView();
                if (view instanceof ViewGroup)
                {
                    m_ViewGroup = (ViewGroup) view;

                    FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.WRAP_CONTENT,
                                                                                         FrameLayout.LayoutParams.WRAP_CONTENT);
                    m_AdView.setLayoutParams(layoutParams);
                    m_AdView.setX(0);
                    m_AdView.setY(0);
                    m_ViewGroup.addView(m_AdView);

                    m_AdView.setAdListener(new AdListener()
                    {
                        public void onAdLoaded()
                        {
                            m_IsLoaded = true;
                        }
                    });
                }     
            }
        });
    }

    public void ShutdownAd()
    {
        runOnUiThread(new Runnable()
        {
            public void run() 
            {
                if (m_AdView == null)
                {
                    return;
                }

                m_ViewGroup.removeView(m_AdView);
                m_AdView = null;
            }
        });
    }

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
    }

    @Override
    public void onPause()
    {
        super.onPause();
        if (m_AdView != null)
        {
            m_AdView.pause();
        }
    }
    @Override
    public void onResume()
    {
        super.onResume();
        if (m_AdView != null)
        {
            m_AdView.resume();
        }
    }
    @Override
    public void onDestroy()
    {
        super.onDestroy();
        if (m_AdView != null)
        {
            m_AdView.destroy();
        }
    }
}
