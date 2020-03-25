package ru.testsimpleapps.lifewallpapertree.views;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.util.AttributeSet;
import android.view.MotionEvent;

import ru.testsimpleapps.lifewallpapertree.WallpaperLib;

public class WallpaperSurface extends GLSurfaceView {

    private int mMinDistance = 50;
    private float mDownX;
    private float mDownY;
    private float mUpX;
    private float mUpY;

    private WallpaperRender mWallpaperRender;

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
        getMove(event);
        return true;
    }

    public void onDestroy() {
        WallpaperLib.destroy(mWallpaperRender.hashCode());
        super.onDetachedFromWindow();
    }

    public void setQuality(boolean isHighQuality) {
        queueEvent(() -> WallpaperLib.quality(isHighQuality));
    }

    private void init() {
        mWallpaperRender = new WallpaperRender(getContext());
        setEGLContextClientVersion(2);
        setRenderer(mWallpaperRender);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
            setPreserveEGLContextOnPause(true);
        }
    }

    public void getMove(final MotionEvent event) {
        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN: {
                mDownX = event.getX();
                mDownY = event.getY();
                break;
            }

            case MotionEvent.ACTION_UP: {
                mUpX = event.getX();
                mUpY = event.getY();
                float deltaX = mDownX - mUpX;
                float deltaY = mDownY - mUpY;

                // Horizontal scroll
                if (Math.abs(deltaX) > Math.abs(deltaY)) {
                    if (Math.abs(deltaX) > mMinDistance) {
                        // Left or right
                        if (deltaX < 0) {
                            WallpaperLib.action(mWallpaperRender.hashCode(), true);
                        } else {
                            WallpaperLib.action(mWallpaperRender.hashCode(), false);
                        }
                    }
                }
                break;
            }
        }
    }
}