package ru.testsimpleapps.lifewallpapertree;

import android.app.Application;
import android.content.Context;
import android.content.SharedPreferences;
import android.util.Log;

import org.acra.ACRA;
import org.acra.ReportingInteractionMode;
import org.acra.annotation.ReportsCrashes;

import static org.acra.ReportField.ANDROID_VERSION;
import static org.acra.ReportField.APP_VERSION_CODE;
import static org.acra.ReportField.PHONE_MODEL;
import static org.acra.ReportField.STACK_TRACE;


@ReportsCrashes(customReportContent = { APP_VERSION_CODE, ANDROID_VERSION, PHONE_MODEL, STACK_TRACE },
        mailTo = "testsimpleapps@gmail.com",
        mode = ReportingInteractionMode.DIALOG,
        resToastText = R.string.acra_crush_title,
        resDialogText = R.string.acra_crush_message_text,
        resDialogIcon = android.R.drawable.ic_dialog_info,
        resDialogTitle = R.string.acra_crush_title,
        resDialogCommentPrompt = R.string.acra_crush_message_comment,
        resDialogOkToast = R.string.acra_crush_ok)
public class WallpaperApplication extends Application {

    public static final String PREFERENCES = "PREFERENCES";
    public static final String QUALITY = "QUALITY";
    private static boolean IS_QUALITY;

    private static Context context;
    private static WallpaperApplication wallpaperApplication;
    private SharedPreferences sharedPreferences;

    public void onCreate() {
        super.onCreate();
        ACRA.init(this);
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