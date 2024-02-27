package ru.testsimpleapps.lifewallpapertree.services;

import android.service.wallpaper.WallpaperService;
import android.view.MotionEvent;
import android.view.SurfaceHolder;

import ru.testsimpleapps.lifewallpapertree.views.WallpaperSurface;

public class WallpaperGLService extends WallpaperService {

    @Override
    public Engine onCreateEngine() {
        return new GLWallpaperEngine();
    }

    public class GLWallpaperEngine extends Engine {

        WallpaperSurface wallpaperSurface;

        @Override
        public void onCreate(SurfaceHolder surfaceHolder) {
            super.onCreate(surfaceHolder);
            wallpaperSurface = new WallpaperSurface(getApplicationContext()) {
                @Override
                public SurfaceHolder getHolder() {
                    return GLWallpaperEngine.this.getSurfaceHolder();
                }
            };
        }

        @Override
        public void onDestroy() {
            super.onDestroy();
            wallpaperSurface.onDestroy();
        }

        @Override
        public void onVisibilityChanged(boolean visible) {
            super.onVisibilityChanged(visible);
            if (visible) {
                wallpaperSurface.onResume();
            } else {
                wallpaperSurface.onPause();
            }
        }

        @Override
        public void onTouchEvent(final MotionEvent event) {
            wallpaperSurface.touch(event);
        }
    }
}
