package org.opencv.samples.tutorial3;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import org.opencv.android.BaseLoaderCallback;
import org.opencv.objdetect.CascadeClassifier;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewListener;
import org.opencv.imgproc.Imgproc;


import android.content.Context;
import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.WindowManager;

public class Sample3Native extends Activity implements CvCameraViewListener {
    private static final String TAG = "OCVSample::Activity";

    private Mat                    mRgba;
    private Mat                    mGrayMat;
    private CameraBridgeViewBase   mOpenCvCameraView;
	private File                   mCascadeFile;
	private MenuItem               mItemPreviewRGBA;
	private CascadeClassifier      mJavaDetector;

    private BaseLoaderCallback     mLoaderCallback = new BaseLoaderCallback(this) {
        @Override
        public void onManagerConnected(int status) {
            switch (status) {
                case LoaderCallbackInterface.SUCCESS:
                {
                    Log.i(TAG, "OpenCV loaded successfully");

                    // Load native library after(!) OpenCV initialization
                    System.loadLibrary("native_sample");

                    mOpenCvCameraView.enableView();
		    InputStream is = getResources().openRawResource(R.raw.hand);
                    File cascadeDir = getDir("cascade", Context.MODE_PRIVATE);
                    mCascadeFile = new File(cascadeDir, "hand.xml");
                    mJavaDetector = new CascadeClassifier(mCascadeFile.getAbsolutePath());
                } break;
                default:
                {
                    super.onManagerConnected(status);
                } break;
            }
        }
    };

    public Sample3Native() {
        Log.i(TAG, "Instantiated new " + this.getClass());
    }

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        Log.i(TAG, "called onCreate");
        super.onCreate(savedInstanceState);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        setContentView(R.layout.tutorial3_surface_view);

        mOpenCvCameraView = (CameraBridgeViewBase) findViewById(R.id.tutorial4_activity_surface_view);
        mOpenCvCameraView.setCvCameraViewListener(this);
    }

	@Override
    public boolean onCreateOptionsMenu(Menu menu) {
        Log.i(TAG, "called onCreateOptionsMenu");
        mItemPreviewRGBA = menu.add(mCascadeFile.getAbsolutePath());
        return true;
    }

    @Override
    public void onPause()
    {
        if (mOpenCvCameraView != null)
            mOpenCvCameraView.disableView();
        super.onPause();
    }

    @Override
    public void onResume()
    {
        super.onResume();
        OpenCVLoader.initAsync(OpenCVLoader.OPENCV_VERSION_2_4_3, this, mLoaderCallback);
    }

    public void onDestroy() {
        super.onDestroy();
        if (mOpenCvCameraView != null)
            mOpenCvCameraView.disableView();
    }

    public void onCameraViewStarted(int width, int height) {
        mRgba = new Mat(height, width, CvType.CV_8UC4);
        mGrayMat = new Mat(height, width, CvType.CV_8UC1);
    }

    public void onCameraViewStopped() {
        mRgba.release();
        mGrayMat.release();
    }

    public Mat onCameraFrame(Mat inputFrame) {
        inputFrame.copyTo(mRgba);
        Imgproc.cvtColor(mRgba, mGrayMat, Imgproc.COLOR_RGBA2GRAY);
        FindFeatures(mCascadeFile.getAbsolutePath(), mGrayMat.getNativeObjAddr(), mRgba.getNativeObjAddr());

        return mRgba;
    }

    public native void FindFeatures(String cascade_name, long matAddrGray, long matAddrRgba);
}