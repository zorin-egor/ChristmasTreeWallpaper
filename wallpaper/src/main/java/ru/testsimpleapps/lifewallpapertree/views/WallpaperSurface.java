package ru.testsimpleapps.lifewallpapertree.views;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.util.AttributeSet;
import android.view.MotionEvent;

import ru.testsimpleapps.lifewallpapertree.WallpaperLib;

public class WallpaperSurface extends GLSurfaceView {

    private int minDistance = 50;
    private float downX;
    private float downY;
    private float upX;
    private float upY;

    private WallpaperRender wallpaperRender;

    public WallpaperSurface(Context context) {
        super(context);
        init();
    }

    public WallpaperSurface(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    @Override
    public boolean onTouchEvent(final MotionEvent event) {
        touch(event);
        return true;
    }

    public void onDestroy() {
        WallpaperLib.destroy(wallpaperRender.hashCode());
        super.onDetachedFromWindow();
    }

    public void setQuality(boolean isHighQuality) {
        queueEvent(() -> WallpaperLib.quality(isHighQuality));
    }

    private void init() {
        wallpaperRender = new WallpaperRender(getContext());
        setEGLContextClientVersion(2);
        setRenderer(wallpaperRender);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
            setPreserveEGLContextOnPause(true);
        }
    }

    public void touch(final MotionEvent event) {
        switch (event.getActionMasked()) {
            case MotionEvent.ACTION_DOWN:
            case MotionEvent.ACTION_POINTER_DOWN: {
                downX = event.getX();
                downY = event.getY();
                break;
            }

            case MotionEvent.ACTION_UP:
            case MotionEvent.ACTION_POINTER_UP: {
                upX = event.getX();
                upY = event.getY();
                float deltaX = downX - upX;
                float deltaY = downY - upY;

                // Horizontal scroll
                if (Math.abs(deltaX) > Math.abs(deltaY)) {
                    if (Math.abs(deltaX) > minDistance) {
                        // Left or right
                        if (deltaX < 0) {
                            WallpaperLib.action(wallpaperRender.hashCode(), true);
                        } else {
                            WallpaperLib.action(wallpaperRender.hashCode(), false);
                        }
                    }
                }
                break;
            }
        }
    }
}