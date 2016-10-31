package ru.testsimpleapps.lifewallpapertree;

import android.app.Application;
import android.content.Context;
import android.content.SharedPreferences;
import android.util.Log;

public class WallpaperApplication extends Application {

    public static final String PREFERENCES = "PREFERENCES";
    public static final String QUALITY = "QUALITY";
    private static boolean IS_QUALITY;

    private static Context context;
    private static WallpaperApplication wallpaperApplication;
    private SharedPreferences sharedPreferences;

    public void onCreate() {
        super.onCreate();
        WallpaperApplication.context = getApplicationContext();
        WallpaperApplication.wallpaperApplication = this;
        loadPreferences();
    }

    private void loadPreferences() {
        Log.d(WallpaperLib.TAG, this.getClass().getName().toString() + " - loadPreferences");
        sharedPreferences = getSharedPreferences(PREFERENCES, MODE_PRIVATE);
        setIsQuality(sharedPreferences.getBoolean(QUALITY, true));
    }

    public void savePreferences() {
        Log.d(WallpaperLib.TAG, this.getClass().getName().toString() + " - savePreferences");
        sharedPreferences.edit().putBoolean(QUALITY, isQuality()).commit();
    }

    public static Context getAppContext() {
        return WallpaperApplication.context;
    }

    public static WallpaperApplication getApplication() {
        return WallpaperApplication.wallpaperApplication;
    }

    public static boolean isQuality() {
        return IS_QUALITY;
    }

    public static void setIsQuality(boolean isQuality) {
        WallpaperApplication.IS_QUALITY = isQuality;
    }
}