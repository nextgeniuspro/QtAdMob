package org.dreamdev.QtAdMob;

import android.os.Bundle;

import org.qtproject.qt5.android.bindings.QtActivity;

public class QtAdMobActivity extends QtActivity implements  AdMobInterface
{
    private AdMobAnd mAdmob = null;

    @Override
    public void AddAdTestDevice(String deviceId) {
        if(mAdmob != null){
            mAdmob.AddAdTestDevice(deviceId);
        }
    }

    @Override
    public void SetAdBannerUnitId(String adId) {
        if(mAdmob != null){
            mAdmob.SetAdBannerUnitId(adId);
        }
    }

    @Override
    public void SetAdBannerSize(int size) {
        if(mAdmob != null){
            mAdmob.SetAdBannerSize(size);
        }
    }

    @Override
    public void SetAdBannerPosition(int x, int y) {
        if(mAdmob != null){
            mAdmob.SetAdBannerPosition(x,y);
        }
    }

    @Override
    public int GetAdBannerWidth() {
        if(mAdmob != null){
            return mAdmob.GetAdBannerWidth();
        }
        return 0;
    }

    @Override
    public int GetAdBannerHeight() {
        if(mAdmob != null){
            return mAdmob.GetAdBannerHeight();
        }
        return 0;
    }

    @Override
    public boolean IsAdBannerShowed() {
        if(mAdmob != null){
            return mAdmob.IsAdBannerShowed();
        }
        return false;
    }

    @Override
    public boolean IsAdBannerLoaded() {
        if(mAdmob != null){
            return mAdmob.IsAdBannerLoaded();
        }
        return false;
    }

    @Override
    public void ShowAdBanner() {
        if(mAdmob != null){
            mAdmob.ShowAdBanner();
        }
    }

    @Override
    public void HideAdBanner() {
        if(mAdmob != null){
            mAdmob.HideAdBanner();
        }
    }

    @Override
    public void InitializeAdBanner() {
        if(mAdmob != null){
            mAdmob.InitializeAdBanner();
        }
    }

    @Override
    public void ShutdownAdBanner() {
        if(mAdmob != null){
            mAdmob.ShutdownAdBanner();
        }
    }

    @Override
    public void LoadAdInterstitialWithUnitId(String adId) {
        if(mAdmob != null){
            mAdmob.LoadAdInterstitialWithUnitId(adId);
        }
    }

    @Override
    public boolean IsAdInterstitialLoaded() {
        if(mAdmob != null){
            return mAdmob.IsAdInterstitialLoaded();
        }
        return false;
    }

    @Override
    public void ShowAdInterstitial() {
        if(mAdmob != null){
            mAdmob.ShowAdInterstitial();
        }
    }

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        mAdmob = new AdMobAnd((QtActivity) this);
    }

    @Override
    public void onPause()
    {
        super.onPause();
        if(mAdmob != null){
            mAdmob.pauseBanner();
        }
    }
    @Override
    public void onResume()
    {
        super.onResume();
        if(mAdmob != null) {
            mAdmob.resumeBanner();
        }
    }
    @Override
    public void onDestroy()
    {
        super.onDestroy();
        if(mAdmob != null){
            mAdmob.destroyBanner();
        }
    }

}
