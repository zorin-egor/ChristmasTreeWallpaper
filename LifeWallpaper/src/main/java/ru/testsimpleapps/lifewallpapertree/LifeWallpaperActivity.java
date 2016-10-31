package ru.testsimpleapps.lifewallpapertree;

import android.app.Activity;
import android.app.ActivityManager;
import android.app.WallpaperManager;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ConfigurationInfo;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class LifeWallpaperActivity extends Activity implements Button.OnClickListener{
    // Hold a reference to our GLSurfaceView
    private WallpaperGLSurfaceViewActivity wallpaperGLSurfaceViewActivity;
    private Button installFull;
    private Button installLight;
    private Button exit;
    private Toast toast;

    @Override
    public void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.life_wallpaper_activity);
        // Surface
        wallpaperGLSurfaceViewActivity = (WallpaperGLSurfaceViewActivity) findViewById(R.id.gl_surfaces_view);
        // Buttons
        installFull = (Button) findViewById(R.id.button_install_full);
        installFull.setOnClickListener(this);
        installLight = (Button) findViewById(R.id.button_install_light);
        installLight.setOnClickListener(this);
        exit = (Button) findViewById(R.id.button_exit);
        exit.setOnClickListener(this);
        // Advice
        toast = Toast.makeText(this, "Life Wallpaper", Toast.LENGTH_SHORT);

        // Check if the system supports OpenGL ES 2.0.
        final ActivityManager activityManager = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
        final ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();
        final boolean supportsEs2 = configurationInfo.reqGlEsVersion >= 0x20000;

        if (supportsEs2){
            // Request an OpenGL ES 2.0 compatible context.
            wallpaperGLSurfaceViewActivity.setEGLContextClientVersion(2);
            // Set the renderer to our wallpaper, defined below.
            wallpaperGLSurfaceViewActivity.setRenderer(new WallpaperGLRender());
        } else {
            // This is where you could create an OpenGL ES 1.x compatible
            // renderer if you wanted to support both ES 1 and ES 2.
            return;
        }
    }

    @Override
    protected void onResume(){
        // The activity must call the GL surface view's onResume() on activity onResume().
        super.onResume();
        Log.d(WallpaperLib.TAG, this.getClass().toString() + " - onResume");
        wallpaperGLSurfaceViewActivity.onResume();
    }

    @Override
    protected void onPause(){
        // The activity must call the GL surface view's onPause() on activity onPause().
        super.onPause();
        Log.d(WallpaperLib.TAG, this.getClass().toString() + " - onPause");
        wallpaperGLSurfaceViewActivity.onPause();
    }

    @Override
    protected void onStop() {
        super.onStop();
        Log.d(WallpaperLib.TAG, this.getClass().toString() + " - onPause");
        if(!GLWallpaperOpenService.isWallpaperSet())
            WallpaperLib.exit();
        WallpaperApplication.getApplication().savePreferences();
    }

    @Override
    public void onClick(View view) {
        switch (view.getId()){
            case R.id.button_install_full :
                WallpaperApplication.getApplication().setIsQuality(true);
                setWallpaper();
                toast.setText(getResources().getString(R.string.message_button_full));
                toast.show();
                break;
            case R.id.button_install_light :
                WallpaperApplication.getApplication().setIsQuality(false);
                setWallpaper();
                toast.setText(getResources().getString(R.string.message_button_light));
                toast.show();
                break;
            case R.id.button_exit :
                toast.setText(getResources().getString(R.string.message_button_exit));
                toast.show();
                finish();
                break;
        }
    }

    private void setWallpaper(){
        Intent intent = new Intent();
        if(Build.VERSION.SDK_INT > 15){
            intent.setAction(WallpaperManager.ACTION_CHANGE_LIVE_WALLPAPER);
            String p = WallpaperService.class.getPackage().getName();
            String c = WallpaperService.class.getCanonicalName();
            intent.putExtra(WallpaperManager.EXTRA_LIVE_WALLPAPER_COMPONENT, new ComponentName(p, c));
        } else {
                intent.setAction(WallpaperManager.ACTION_LIVE_WALLPAPER_CHOOSER);
            }

        startActivityForResult(intent, 0);
    }
}
