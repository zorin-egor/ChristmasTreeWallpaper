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
    private Button mSetFullButton;
    private Button mSetLightButton;
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
            case R.id.set_full_button:
                PreferenceManager.getInstance(getApplicationContext()).setWallpaperQuality(true);
                mWallpaperSurface.setQuality(true);
                setWallpaper();
                break;
            case R.id.set_light_button:
                PreferenceManager.getInstance(getApplicationContext()).setWallpaperQuality(false);
                mWallpaperSurface.setQuality(false);
                setWallpaper();
                break;
            case R.id.exit_button:
                finish();
                break;
        }
    }

    private void init(@Nullable Bundle savedInstanceState) {
        mWallpaperSurface = findViewById(R.id.wallpaper_surface);
        setButtonActions();
    }

    private void setButtonActions() {
        mSetFullButton = findViewById(R.id.set_full_button);
        mSetFullButton.setOnClickListener(this);
        mSetLightButton = findViewById(R.id.set_light_button);
        mSetLightButton.setOnClickListener(this);
        mExitButton = findViewById(R.id.exit_button);
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
