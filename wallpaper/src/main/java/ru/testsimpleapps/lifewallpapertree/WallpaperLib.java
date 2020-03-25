package ru.testsimpleapps.lifewallpapertree;

import android.content.res.AssetManager;

import ru.testsimpleapps.lifewallpapertree.managers.BitmapManager;

public class WallpaperLib {

    static {
        System.loadLibrary(BuildConfig.LIB_WALLPAPER);
    }

    public static native void init(int id, AssetManager assetManager, BitmapManager bitmapManager);

    public static native void destroy(int id);

    public static native void screen(int id, int width, int height);

    public static native void step(int id);

    public static native void action(int id, boolean isLeftOrRight);

    public static native void quality(boolean isHighQuality);

}
