package yuvplayer.yuvplayer;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.SurfaceHolder;

public class YUVPlayer extends GLSurfaceView implements  Runnable,SurfaceHolder.Callback
{

    public YUVPlayer(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        new Thread(this).start();//回调run
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {

    }


    @Override
    public void run() {//传GLSurfaceView地址进去

    Open("/sdcard/outCat.yuv",getHolder().getSurface());

    }


    public  native void Open(String url,Object surface);



}
