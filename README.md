# QtAdMob #
QtAdMob is a C++ lib for Qt with QML support, which allows to show ads from AdMob on Android and iOS platforms

ver. 1.0.0 - QML is supported now!

# How To Use #

### QML ###
If your app uses qml, next steps will explain how to add QtAdMob with qml

- Add QTADMOB_QML flag to DEFINES in proect file
```
DEFINES += QTADMOB_QML
```

- Call DeclareQML() methods for banner and interstitial before loading qml file
```
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QmlAdMobBanner::DeclareQML();			// <== Call it before loading qml
    QmlAdMobInterstitial::DeclareQML();		// <== Call it before loading qml

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
```
- In qml file import com.dreamdev.QtAdMobBanner or com.dreamdev.QtAdMobInterstitial for banner and interstitial support
```
import com.dreamdev.QtAdMobBanner 1.0
import com.dreamdev.QtAdMobInterstitial 1.0
```

- Declare AdMobBanner object in your qml file if you want to see banner. Setup all properties in onCompleted signal
```
AdMobBanner
{
    id: banner

    Component.onCompleted: {
        banner.unitId = "ca-app-pub-7485900711629006/8288667458"
        banner.size = AdMobBanner.Banner
        banner.visible = true
    }
}
```
- Declare AdMobInterstitial object in your qml file if you want to see banner. Setup all properties in onCompleted signal. After interstitial has been showed it must be reinitialized with their unitId, better solution for it is setupping unitId in onClosed signal handler.
```
AdMobInterstitial
{
    id: intertitial

    Component.onCompleted: {
        intertitial.unitId = "ca-app-pub-7485900711629006/9462519453"
    }

    onClosed: {
        intertitial.unitId = "ca-app-pub-7485900711629006/9462519453"
    }
}
```

### Widgets ###
If your app uses qt widgets, next steps will explain how to add QtAdMob with widgets

- Create banner object and setup its parameters
```
IQtAdMobBanner* banner = CreateQtAdMobBanner();
banner->setUnitId("ca-app-pub-7485900711629006/8288667458");
banner->setSize(IQtAdMobBanner::Banner);
banner->addTestDevice("514ED2E95AD8EECE454CC5565326160A");
banner->setVisible(true);
```
- Create interstitial object and setup its parameters
```
IQtAdMobBanner* banner = CreateQtAdMobBanner();
IQtAdMobInterstitial* interstitial = CreateQtAdMobInterstitial();
interstitial->setUnitId("ca-app-pub-7485900711629006/9462519453");
interstitial->addTestDevice("514ED2E95AD8EECE454CC5565326160A");
interstitial->setVisible(true)
```

### Examples ###

Look on [QtAdMobTestApp](https://github.com/yevgeniy-logachev/QtAdMobApp) repository for example of using 

# How To Integrate #

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
- Add QtAdMobActivity.java to list of android DISTFILES in your .pro file
```
android:
{
	DISTFILES += \
    	        $$ANDROID_PACKAGE_SOURCE_DIR/src/org/dreamdev/QtAdMob/QtAdMobActivity.java \
}
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