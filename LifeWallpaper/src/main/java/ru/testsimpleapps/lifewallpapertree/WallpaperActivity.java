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

import java.lang.reflect.Method;

public class WallpaperActivity extends Activity implements Button.OnClickListener{
    // Hold a reference to our GLSurfaceView
    private static WallpaperGLSurfaceViewActivity wallpaperGLSurfaceViewActivity = null;
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
        setButtonActions();
        // Advice
        toast = Toast.makeText(this, "Live Wallpaper", Toast.LENGTH_SHORT);

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
    protected void onDestroy() {
        Log.d(WallpaperLib.TAG, this.getClass().toString() + " - onDestroy");
        super.onDestroy();
        WallpaperApplication.getApplication().savePreferences();
        if(!GLWallpaperOpenService.isWallpaperSet())
            WallpaperLib.exit();
        wallpaperGLSurfaceViewActivity = null;
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

    private void setButtonActions(){
        installFull = (Button) findViewById(R.id.button_install_full);
        installFull.setOnClickListener(this);
        installLight = (Button) findViewById(R.id.button_install_light);
        installLight.setOnClickListener(this);
        exit = (Button) findViewById(R.id.button_exit);
        exit.setOnClickListener(this);
    }

    private void setWallpaper(){
        try {
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
        } catch(Exception e){
            e.printStackTrace();
            try {
                WallpaperManager manager = WallpaperManager.getInstance(this);
                Method method = WallpaperManager.class.getMethod("getIWallpaperManager", null);
                Object objIWallpaperManager = method.invoke(manager, null);
                Class[] param = new Class[1];
                param[0] = ComponentName.class;
                method = objIWallpaperManager.getClass().getMethod("setWallpaperComponent", param);

                // Get the intent of the desired wallpaper service. Note: I created my own
                // Custom wallpaper service. You'll need a class reference and package
                // Of the desired live wallpaper
                Intent intent = new Intent(WallpaperService.SERVICE_INTERFACE);
                intent.setClassName(this.getPackageName(), WallpaperService.class.getName());

                // Set the live wallpaper (throws security exception if you're not system-privileged app)
                method.invoke(objIWallpaperManager, intent.getComponent());
            } catch(Exception ex){
                ex.printStackTrace();
                Toast.makeText(this, getResources().getString(R.string.message_button_install_error), Toast.LENGTH_LONG).show();
            }
        }
    }

    public static boolean isActivity(){
        if(wallpaperGLSurfaceViewActivity != null)
            return true;
        return false;
    }
}
