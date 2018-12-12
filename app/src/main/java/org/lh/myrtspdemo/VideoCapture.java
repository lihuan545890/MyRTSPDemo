package org.lh.myrtspdemo;

import android.content.Context;
import android.hardware.Camera;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.WindowManager;

/**
 * Created by lihuan on 2018/12/7.
 */

public class VideoCapture {
    private final static String TAG = "VideoCapture.java";
    private static Context sCtx;

    public final static boolean initialize(Context ctx) {
        sCtx = ctx;

        boolean bRet = _initialize(ctx);
        if (bRet == false)
        {
            return false;
        }
        // set screen dimension
        DisplayMetrics dm = new DisplayMetrics();
        WindowManager wm = (WindowManager)
                ctx.getSystemService(Context.WINDOW_SERVICE);
        wm.getDefaultDisplay().getMetrics(dm);
        int width = dm.widthPixels;
        int height = dm.heightPixels;
        if (width > height)
        {
            int t = width;
            width = height;
            height = t;
        }
        _setScreenSize(width, height);
        return true;
    }

    public final static boolean start(SurfaceHolder prevHolder,
                                      int nWidth, int nHeight, int nMaxFPS, int nOrient) {
        Log.v(TAG, "start enter");

        boolean ret =_start(prevHolder, nWidth, nHeight, nMaxFPS, nOrient);

        Log.v(TAG, "start leave");
        return ret;
    }

    public final static void destroy() {
        _destroy();
    }
    public final static void startPushStream(){
        _startPushStream();
    }
    private native final static boolean _initialize(Context ctx);
    private native final static void _setScreenSize(int width, int height);
    private native final static boolean _start(SurfaceHolder prevHolder,
                                               int nWidth, int nHeight, int nMaxFPS, int nOrient);
    private native final static void _stop();
    private native final static void _destroy();
    private native final static boolean _switchCamera();
    private native final static void  _startPushStream();
    public native final static void setOrientation(int nOrient);
    public native final static void setPreviewRotation(int nRotation);
    public native final static int getCameraId();
    public native final static int getCameraCount();
    public native final static Camera.Parameters getParameters();
    public native final static void setParameters(Camera.Parameters params);

}
