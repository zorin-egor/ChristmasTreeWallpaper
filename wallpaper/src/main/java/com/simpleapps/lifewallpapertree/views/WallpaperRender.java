package com.simpleapps.lifewallpapertree.views;

import android.content.Context;
import android.opengl.GLSurfaceView;

import com.simpleapps.lifewallpapertree.WallpaperLib;
import com.simpleapps.lifewallpapertree.managers.BitmapManager;
import com.simpleapps.lifewallpapertree.managers.PreferenceManager;

import java.lang.ref.WeakReference;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class WallpaperRender implements GLSurfaceView.Renderer {

    private final WeakReference<Context> context;

    public WallpaperRender(Context context) {
        this.context = new WeakReference<>(context);
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        final Context context = this.context.get();
        if (context != null) {
            WallpaperLib.init(hashCode(), context.getAssets(), new BitmapManager(context.getAssets()));
            WallpaperLib.quality(PreferenceManager.getInstance(context).isWallpaperQuality());
        } else {
            throw new IllegalStateException("Context must be set!");
        }
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        WallpaperLib.screen(hashCode(), width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        WallpaperLib.step(hashCode());
    }

}