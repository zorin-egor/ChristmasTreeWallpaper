package ru.testsimpleapps.lifewallpapertree.managers;

import android.content.Context;
import android.content.SharedPreferences;

public class PreferenceManager {

    public static final String TAG = PreferenceManager.class.getSimpleName();

    private static volatile PreferenceManager sInstance;

    public static PreferenceManager getInstance(Context context) {
        PreferenceManager localInstance = sInstance;
        if (localInstance == null) {
            synchronized (PreferenceManager.class) {
                localInstance = sInstance;
                if (localInstance == null) {
                    sInstance = localInstance = new PreferenceManager(context);
                }
            }
        }
        return localInstance;
    }

    private final SharedPreferences sharedPreferences;

    private final String KEY_1 = "KEY_1";

    public PreferenceManager(Context context) {
        sharedPreferences = context.getSharedPreferences(TAG, Context.MODE_PRIVATE);
    }

    public void setWallpaperQuality(boolean isHighQuality) {
        sharedPreferences.edit().putBoolean(KEY_1, isHighQuality).apply();
    }

    public boolean isWallpaperQuality() {
        return sharedPreferences.getBoolean(KEY_1, false);
    }

}
