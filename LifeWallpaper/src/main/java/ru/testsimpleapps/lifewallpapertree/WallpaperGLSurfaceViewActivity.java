package ru.testsimpleapps.lifewallpapertree;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;

public class WallpaperGLSurfaceViewActivity extends GLSurfaceView {

    private static int minDistance = 50;
    private static float downX, downY, upX, upY;

    public WallpaperGLSurfaceViewActivity(Context context, AttributeSet attrs){
        super(context, attrs);
    }

    @Override
    public boolean onTouchEvent(final MotionEvent event) {
        //Log.d(WallpaperLib.TAG, this.getClass().toString() + " - onTouchEvent; GetX: " + event.getX(event.getActionIndex()) + "; GetY: " + event.getY(event.getActionIndex()));
        getMove(event);
        return true;
    }

    public static void getMove(final MotionEvent event){
        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN : {
                downX = event.getX();
                downY = event.getY();
                break;
            }

            case MotionEvent.ACTION_UP : {
                upX = event.getX();
                upY = event.getY();
                float deltaX = downX - upX;
                float deltaY = downY - upY;

                //HORIZONTAL SCROLL
                if(Math.abs(deltaX) > Math.abs(deltaY)){
                    if(Math.abs(deltaX) > minDistance){
                        // left or right
                        if(deltaX < 0){
                            WallpaperLib.action(true);
                        } else {
                            WallpaperLib.action(false);
                        }
                    }
                }
                break;
            }
        }
    }
}