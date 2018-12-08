package org.lh.myrtspdemo;

import android.app.Activity;
import android.content.pm.ActivityInfo;
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
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
        requestWindowFeature(Window.FEATURE_NO_TITLE);

        setContentView(R.layout.activity_main);

        mLocalPreview = (SurfaceView)findViewById(R.id.local_preview);
        VideoCapture.initialize(this);
        VideoCapture.start(mLocalPreview.getHolder(), 1280, 720, 30,180);
    }


    @Override
    protected void onDestroy() {
        super.onDestroy();
        VideoCapture.destroy();
        Log.i("RTSPDemo", "onDestroy........................");
    }
}
