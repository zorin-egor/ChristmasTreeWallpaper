package ru.testsimpleapps.lifewallpapertree;

import android.opengl.GLSurfaceView;
import android.util.Log;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class WallpaperGLRender implements GLSurfaceView.Renderer {

    private long startTime, endTime, dt;

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        Log.d(WallpaperLib.TAG, this.getClass().toString() + " - onSurfaceCreated");
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        Log.d(WallpaperLib.TAG, this.getClass().toString() + " - onSurfaceChanged");
        startTime = System.currentTimeMillis();
        WallpaperLib.destroyPrevious();
        WallpaperLib.init(  WallpaperApplication.getAppContext().getAssets(),
                            new PNGManager(WallpaperApplication.getAppContext().getAssets()),
                            width,
                            height,
                            WallpaperApplication.getApplication().isQuality());
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        frameLimit();
        WallpaperLib.step();
    }

    void frameLimit(){
        endTime = System.currentTimeMillis();
        dt = endTime - startTime;

        if (dt < 33){
            try {
                Thread.sleep(33 - dt);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        startTime = System.currentTimeMillis();
    }
}