package org.opencv.samples.tutorial3;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import org.opencv.core.MatOfRect;
import org.opencv.core.Core;
import org.opencv.core.MatOfRect;
import org.opencv.core.Size;
import org.opencv.core.Rect;
import org.opencv.android.BaseLoaderCallback;
import org.opencv.objdetect.CascadeClassifier;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewListener;
import org.opencv.imgproc.Imgproc;

import android.widget.Toast;


import android.content.Context;
import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.SurfaceView;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.view.WindowManager;
import org.opencv.core.Scalar;

public class Sample3Native extends Activity implements CvCameraViewListener {
    private static final String TAG = "OCVSample::Activity";

    private Mat                    mRgba;
    private Mat                    mGrayMat;
    private CameraBridgeViewBase   mOpenCvCameraView;
	private File                   mCascadeFile;
	private MenuItem               mItemPreviewRGBA;
	private CascadeClassifier      mJavaDetector;
    private MenuItem               mItemFace40;
    private MenuItem               mItemFace30;
    private MenuItem               mItemFace20;
    private MenuItem               mItemFace15;
    private int			   compare = 0;
    private Handler		   toastTeller;

    private static final Scalar    FACE_RECT_COLOR     = new Scalar(0, 255, 0, 255);
    private float                  mRelativeFaceSize   = 0.25f;
    private int                    mAbsoluteFaceSize   = 0;

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
		    try{
		    InputStream is = getResources().openRawResource(R.raw.hand);
                    File cascadeDir = getDir("cascade", Context.MODE_PRIVATE);
                    mCascadeFile = new File(cascadeDir, "hand.xml");
			FileOutputStream os = new FileOutputStream(mCascadeFile);

                        byte[] buffer = new byte[4096];
                        int bytesRead;
                        while ((bytesRead = is.read(buffer)) != -1) {
                            os.write(buffer, 0, bytesRead);
                        }
                        is.close();
                        os.close();
                        	
                    mJavaDetector = new CascadeClassifier(mCascadeFile.getAbsolutePath());
		    if (mJavaDetector.empty()) {
                            Log.e(TAG, "Failed to load cascade classifier");
                            mJavaDetector = null;
		    }
		    cascadeDir.delete();

		    toastTeller = new Handler() {
			public void handleMessage(Message msg) {
				if (msg.what == 2)
				Toast.makeText(Sample3Native.this, msg.obj.toString(), Toast.LENGTH_SHORT).show();
				super.handleMessage(msg);
			}
		    };

                    } catch (IOException e) {
                        e.printStackTrace();
                        Log.e(TAG, "Failed to load cascade. Exception thrown: " + e);
                    }
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
        mItemFace40 = menu.add("Face size 40%");
        mItemFace30 = menu.add("Face size 30%");
        mItemFace20 = menu.add("Face size 20%");
	mItemFace15 = menu.add("Face size 15%");
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        Log.i(TAG, "called onOptionsItemSelected; selected item: " + item);
	if (item == mItemFace15)
            setMinFaceSize(0.15f);
        else if (item == mItemFace40)
            setMinFaceSize(0.4f);
        else if (item == mItemFace30)
            setMinFaceSize(0.3f);
        else if (item == mItemFace20)
            setMinFaceSize(0.2f);
        return true;
    }

    private void setMinFaceSize(float faceSize) {
        mRelativeFaceSize = faceSize;
        mAbsoluteFaceSize = 0;
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
        Imgproc.cvtColor(inputFrame, mGrayMat, Imgproc.COLOR_RGBA2GRAY);

        if (mAbsoluteFaceSize == 0) {
            int height = mGrayMat.rows();
            if (Math.round(height * mRelativeFaceSize) > 0) {
                mAbsoluteFaceSize = Math.round(height * mRelativeFaceSize);
            }
            //mNativeDetector.setMinFaceSize(mAbsoluteFaceSize);
        }

        MatOfRect faces = new MatOfRect();

        //if (mDetectorType == JAVA_DETECTOR) {
        if (mJavaDetector != null)
            mJavaDetector.detectMultiScale(mGrayMat, faces, 1.1, 2, 2, // TODO: objdetect.CV_HAAR_SCALE_IMAGE
                    new Size(mAbsoluteFaceSize, mAbsoluteFaceSize), new Size());
        //}
        /*else if (mDetectorType == NATIVE_DETECTOR) {
            if (mNativeDetector != null)
                mNativeDetector.detect(mGray, faces);
        }
        else {
            Log.e(TAG, "Detection method is not selected!");
        }*/

        Rect[] facesArray = faces.toArray();
        for (int i = 0; i < facesArray.length; i++){
            Core.rectangle(mRgba, facesArray[i].tl(), facesArray[i].br(), FACE_RECT_COLOR, 3);
	    if(compare == 0)
	        compare = facesArray[i].y;
	    else if (compare < 0)
		compare++;
	}
	
	if(compare > 0){
	//300 might be a good swipe value, also assuming that only hands would be boxed
		if (facesArray.length > 0 && (facesArray[0].y >= compare + 100)){
			new Thread(new Runnable(){
				public void run(){
					Message msg = new Message();
					msg.what = 2;
					msg.obj = "Right swipe";
					toastTeller.sendMessage(msg);
				}
		 	}).start();
			compare = -4;
		}
			//Toast.makeText(getApplicationContext(), "Right Swipe", Toast.LENGTH_SHORT).show();
			//right swipe
		else if (facesArray.length > 0 && (facesArray[0].y <= compare - 100)){
			new Thread(new Runnable(){
				public void run(){
					Message msg = new Message();
					msg.what = 2;
					msg.obj = "Left swipe";
					toastTeller.sendMessage(msg);
				}
		 	}).start();
			compare = -4;
		}
	}
		//Toast.makeText(getApplicationContext(), "Left Swipe", Toast.LENGTH_SHORT).show();
		//left swipe

        return mRgba;
    }
        /*inputFrame.copyTo(mRgba);
        Imgproc.cvtColor(mRgba, mGrayMat, Imgproc.COLOR_RGBA2GRAY);
        FindFeatures(mCascadeFile.getAbsolutePath(), mGrayMat.getNativeObjAddr(), mRgba.getNativeObjAddr());

        return mRgba;
    }*/

    public native void FindFeatures(String cascade_name, long matAddrGray, long matAddrRgba);
}
