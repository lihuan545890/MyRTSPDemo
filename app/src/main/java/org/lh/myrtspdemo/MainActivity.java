package org.lh.myrtspdemo;

import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.content.res.Configuration;
import android.os.Bundle;
import android.util.Log;
import android.view.SurfaceView;
import android.view.Window;

public class MainActivity extends Activity {
    static {
        System.loadLibrary("rtspdemo-jni");
    }

    SurfaceView mLocalPreview;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
//        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
        requestWindowFeature(Window.FEATURE_NO_TITLE);

        setContentView(R.layout.activity_main);

        VideoCapture.initialize(this);
        mLocalPreview = (SurfaceView)findViewById(R.id.local_preview);
        VideoCapture.start(mLocalPreview.getHolder(), 1280, 720, 30,180);
        new Thread(new Runnable() {
            @Override
            public void run() {
                VideoCapture.startPushStream();
            }
        }).start();

    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        VideoCapture.destroy();
        Log.i("RTSPDemo", "onDestroy........................");
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);

        if(newConfig.orientation == Configuration.ORIENTATION_LANDSCAPE){
            Log.i("RTSPDemo", "onConfigurationChanged. landscape");

        }else{
            Log.i("RTSPDemo", "onConfigurationChanged. portraitscape");
        }

    }
}
