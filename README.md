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
- Copy src/ and google-play-services_lib/ folders from QtAdMob/platform/android directory to your AndroidManifest.xml location
- In AndroidManifest.xml make changes like in picture below:
![](https://github.com/yevgeniy-logachev/QtAdMob/blob/master/AndroidManifest.png)
- In project file (.pro) add next Qt libs
```
android:QT += androidextras gui-private
```
- Create project.properties file if not exists in your AndroidManifest.xml location and add to end of it:
```
android.library.reference.1=./google-play-services_lib/
```
- Add path to QtAdMobActivity.java in .pro file:
```
android:DISTFILES += <Path_to_manifest_location>/src/org/dreamdev/QtAdMob/QtAdMobActivity.java
```
