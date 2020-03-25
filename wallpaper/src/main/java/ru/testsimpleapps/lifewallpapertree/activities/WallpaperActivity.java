package ru.testsimpleapps.lifewallpapertree.activities;

import android.app.Activity;
import android.app.WallpaperManager;
import android.content.ComponentName;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import androidx.annotation.Nullable;

import ru.testsimpleapps.lifewallpapertree.R;
import ru.testsimpleapps.lifewallpapertree.managers.PreferenceManager;
import ru.testsimpleapps.lifewallpapertree.services.WallpaperGLService;
import ru.testsimpleapps.lifewallpapertree.views.WallpaperSurface;

public class WallpaperActivity extends Activity implements Button.OnClickListener{

    private WallpaperSurface mWallpaperSurface;
    private Button mInstallFullButton;
    private Button mInstallLightButton;
    private Button mExitButton;

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.wallpaper_activity);
        init(savedInstanceState);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        mWallpaperSurface.onDestroy();
    }

    @Override
    public void onClick(View view) {
        switch (view.getId()){
            case R.id.button_install_full :
                PreferenceManager.getInstance(getApplicationContext()).setWallpaperQuality(true);
                mWallpaperSurface.setQuality(true);
                setWallpaper();
                break;
            case R.id.button_install_light :
                PreferenceManager.getInstance(getApplicationContext()).setWallpaperQuality(false);
                mWallpaperSurface.setQuality(false);
                setWallpaper();
                break;
            case R.id.button_exit :
                finish();
                break;
        }
    }

    private void init(@Nullable Bundle savedInstanceState) {
        mWallpaperSurface = findViewById(R.id.wallpaper_surface);
        setButtonActions();
    }

    private void setButtonActions() {
        mInstallFullButton = findViewById(R.id.button_install_full);
        mInstallFullButton.setOnClickListener(this);
        mInstallLightButton = findViewById(R.id.button_install_light);
        mInstallLightButton.setOnClickListener(this);
        mExitButton = findViewById(R.id.button_exit);
        mExitButton.setOnClickListener(this);
    }

    private void setWallpaper() {
        try {
            Intent intent = new Intent();
            intent.setAction(WallpaperManager.ACTION_CHANGE_LIVE_WALLPAPER);
            intent.putExtra(
                WallpaperManager.EXTRA_LIVE_WALLPAPER_COMPONENT,
                new ComponentName(this, WallpaperGLService.class)
            );
            startActivityForResult(intent, 0);
        } catch(Exception e) {
            Toast.makeText(this, getResources().getString(R.string.message_button_install_error), Toast.LENGTH_LONG).show();
        }
    }
}
