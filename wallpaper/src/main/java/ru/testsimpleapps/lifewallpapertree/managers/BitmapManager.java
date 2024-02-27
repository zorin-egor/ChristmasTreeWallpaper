package ru.testsimpleapps.lifewallpapertree.managers;

import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

public class BitmapManager {

    private final AssetManager assetManager;

    public BitmapManager(AssetManager manager) {
        assetManager = manager;
    }

    public Bitmap open(String path) {
        try {
            return BitmapFactory.decodeStream(assetManager.open(path));
        } catch (Exception e) {
            return null;
        }
    }

    public int getWidth(Bitmap bitmap) {
        return bitmap.getWidth();
    }

    public int getHeight(Bitmap bitmap) {
        return bitmap.getHeight();
    }

    public void getPixels(Bitmap bitmap, int[] pixels) {
        int width = bitmap.getWidth();
        int height = bitmap.getHeight();
        bitmap.getPixels(pixels, 0, width, 0, 0, width, height);
    }

    public void close(Bitmap bitmap) {
        bitmap.recycle();
    }
}