# QtAdMob #
QtAdMob it is c++ lib for Qt, which allow to show ads from AdMob on Android and iOS platforms

# How To Integrate #

Look on [QtAdMobTestApp](https://github.com/yevgeniy-logachev/QtAdMobApp) repository for example of using 

### IOS ###

- Place QtAdMob lib to your project dir and include it in .pro file
```
include(QtAdMob/QtAdMob.pri)
```

### Android ###

- Place QtAdMob lib to your project dir and include it in .pro file
```
include(QtAdMob/QtAdMob.pri)
```

- Assign in you .pro file varialble ANDROID_PACKAGE_SOURCE_DIR before include QtAdMob/QtAdMob.pri, for ex.
```
ANDROID_PACKAGE_SOURCE_DIR = $$PWD/platform/android
```

- In AndroidManifest.xml make changes like in picture below:
![](https://github.com/yevgeniy-logachev/QtAdMob/blob/master/AndroidManifest.png)

## If you use Gradle automation build system ##
- Make sure that you have installed Google Repository, Google Play services and Android Support Repository in android sdk

![](https://github.com/yevgeniy-logachev/QtAdMob/blob/master/AndroidSDK.png)

- Add dependencies in build.gradle
```
dependencies {
    compile fileTree(dir: 'libs', include: ['*.jar'])
    compile 'com.google.android.gms:play-services-ads:+'
}
```

## If you use Ant automation build system ##
- Copy google-play-services_lib/ folders from android-sdk/extras/google/google_play_services/libproject/ directory to your AndroidManifest.xml location
- Create project.properties file if not exists in your AndroidManifest.xml location and add to end of it:
```
android.library.reference.1=./google-play-services_lib/
```