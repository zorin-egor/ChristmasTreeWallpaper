package ru.testsimpleapps.lifewallpapertree;

import android.content.res.AssetManager;

public class WallpaperLib {
    public static String TAG = "SimpleWallpaper";

    static{
        System.loadLibrary("SimpleWallpaper");
    }

    public static native void init(AssetManager assetManager, PNGManager pngManager);
    public static native void onChange(int width, int height, boolean isQuality);
    public static native void step();
    public static native void destroyPrevious();
    public static native void action(boolean isLeftOrRight);
    public static native void exit();
}
