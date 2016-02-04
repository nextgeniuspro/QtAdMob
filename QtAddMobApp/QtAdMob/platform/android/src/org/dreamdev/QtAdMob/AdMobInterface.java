package org.dreamdev.QtAdMob;


/**
 * Created by moisex on 9/4/15.
 *
 * Note: This interface represents the methods called from CPP in the admobapp.
 */
public interface AdMobInterface {

    public void AddAdTestDevice(final String deviceId);

    public void SetAdBannerUnitId(final String adId);

    public void SetAdBannerSize(final int size);

    public void SetAdBannerPosition(final int x, final int y);

    public int GetAdBannerWidth();

    public int GetAdBannerHeight();

    public boolean IsAdBannerShowed();

    public boolean IsAdBannerLoaded();

    public void ShowAdBanner();

    public void HideAdBanner();

    public void InitializeAdBanner();

    public void ShutdownAdBanner();

    public void LoadAdInterstitialWithUnitId(final String adId);

    public boolean IsAdInterstitialLoaded();

    public void ShowAdInterstitial();



}
