package org.opencv.samples.facedetect;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;

import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewFrame;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.core.MatOfRect;
import org.opencv.core.Rect;
import org.opencv.core.Scalar;
import org.opencv.core.Size;
import org.opencv.imgproc.Imgproc;
import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewListener2;
import org.opencv.objdetect.CascadeClassifier;
import org.opencv.video.BackgroundSubtractorMOG;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.WindowManager;
import android.widget.Toast;

public class FdActivity extends Activity implements CvCameraViewListener2 {

    private static final String    TAG                 = "OCVSample::Activity";
    private static final Scalar    FACE_RECT_COLOR     = new Scalar(0, 255, 0, 255);
    private static final Scalar    OLD_COLOR		   = new Scalar(0, 0, 255, 255);
    public static final int        JAVA_DETECTOR       = 0;
    public static final int        NATIVE_DETECTOR     = 1;
    public static final int        NUM_FRAMES_TO_LEARN_FROM = 13;

    private MenuItem			   mItemFace50;
    private MenuItem               mItemFace40;
    private MenuItem               mItemFace30;
    private MenuItem               mItemFace20;
    private MenuItem               mItemType;

    private Mat                    mRgba;
    private Mat                    mGray;
    
    private File                   mCascadeFile;
    private CascadeClassifier      mJavaDetector;
    private DetectionBasedTracker  mNativeDetector;

    private int                    mDetectorType       = JAVA_DETECTOR;
    private String[]               mDetectorName;

    private float                  mRelativeFaceSize   = 0.2f;
    private int                    mAbsoluteFaceSize   = 0;

    private CameraBridgeViewBase   mOpenCvCameraView;
  //my guys
    private Mat						mRgb;
    private Mat						mFGMask;
    private BackgroundSubtractorMOG sub;
    private int 					bgCount;
    private ArrayList<Integer>		compare;
    private Handler                 toastTeller;


    private BaseLoaderCallback  mLoaderCallback = new BaseLoaderCallback(this) {
        @Override
        public void onManagerConnected(int status) {
            switch (status) {
                case LoaderCallbackInterface.SUCCESS:
                {
                    Log.i(TAG, "OpenCV loaded successfully");

                    // Load native library after(!) OpenCV initialization
                    System.loadLibrary("detection_based_tracker");

                    try {
                        // load cascade file from application resources
                        InputStream is = getResources().openRawResource(R.raw.haarcascade_openhand);
                        File cascadeDir = getDir("cascade", Context.MODE_PRIVATE);
                        mCascadeFile = new File(cascadeDir, "haarcascade_openhand.xml");
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
                        } else
                            Log.i(TAG, "Loaded cascade classifier from " + mCascadeFile.getAbsolutePath());

                        mNativeDetector = new DetectionBasedTracker(mCascadeFile.getAbsolutePath(), 0);

                        cascadeDir.delete();
                        
                        //Diego's handler initiation
                        toastTeller = new Handler() {
                            public void handleMessage(Message msg) {
                                if (msg.what == 2)
                                Toast.makeText(FdActivity.this, msg.obj.toString(), Toast.LENGTH_SHORT).show();
                                super.handleMessage(msg);
                            }
                        };
                        //^^^^^^^^^^^^^^^^^^^^^^^^^^

                    } catch (IOException e) {
                        e.printStackTrace();
                        Log.e(TAG, "Failed to load cascade. Exception thrown: " + e);
                    }

                    mOpenCvCameraView.enableView();
                } break;
                default:
                {
                    super.onManagerConnected(status);
                } break;
            }
        }
    };

    public FdActivity() {
        mDetectorName = new String[2];
        mDetectorName[JAVA_DETECTOR] = "Java";
        mDetectorName[NATIVE_DETECTOR] = "Native (tracking)";

        Log.i(TAG, "Instantiated new " + this.getClass());
    }

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        Log.i(TAG, "called onCreate");
        super.onCreate(savedInstanceState);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        setContentView(R.layout.face_detect_surface_view);

        mOpenCvCameraView = (CameraBridgeViewBase) findViewById(R.id.fd_activity_surface_view);
        mOpenCvCameraView.setCvCameraViewListener(this);
    }

    @Override
    public void onPause()
    {
        super.onPause();
        if (mOpenCvCameraView != null)
            mOpenCvCameraView.disableView();
    }

    @Override
    public void onResume()
    {
        super.onResume();
        OpenCVLoader.initAsync(OpenCVLoader.OPENCV_VERSION_2_4_3, this, mLoaderCallback);
    }

    public void onDestroy() {
        super.onDestroy();
        mOpenCvCameraView.disableView();
    }

    public void onCameraViewStarted(int width, int height) {
        mGray = new Mat();
        mRgba = new Mat();
        mRgb = new Mat();
        mFGMask = new Mat();
    	sub = new BackgroundSubtractorMOG(13, 4, 0.8);
    	bgCount = 0;
    	compare = new ArrayList<Integer>();
    }

    public void onCameraViewStopped() {
        mGray.release();
        mRgba.release();
        mRgb.release();
        mFGMask.release();
    }

    public void learnBackground(double learningRate) {
		Imgproc.cvtColor(mGray, mRgb, Imgproc.COLOR_GRAY2RGB);
        sub.apply(mRgb, mFGMask, learningRate);//exports a gray image
    }
    public Mat onCameraFrame(CvCameraViewFrame inputFrame) {

        //mRgba = inputFrame.rgba();
        mGray = inputFrame.gray();
        
        //backgroundFilter the first NUM_FRAMES_TO_LEARN_FROM
        if(bgCount++ < NUM_FRAMES_TO_LEARN_FROM)
            learnBackground(0.1);
        else
            learnBackground(0);
        
        //trial junk
        
        //Imgproc.findContours(image, contours, null, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE)
       
        //haar stuff
        
        if (mAbsoluteFaceSize == 0) {
            int height = mFGMask.rows();
            if (Math.round(height * mRelativeFaceSize) > 0) {
                mAbsoluteFaceSize = Math.round(height * mRelativeFaceSize);
            }
            mNativeDetector.setMinFaceSize(mAbsoluteFaceSize);
        }

        MatOfRect faces = new MatOfRect();

        if (mDetectorType == JAVA_DETECTOR) {
            if (mJavaDetector != null)
                mJavaDetector.detectMultiScale(mFGMask, faces, 1.1, 2, 2, // TODO: objdetect.CV_HAAR_SCALE_IMAGE
                        new Size(mAbsoluteFaceSize, mAbsoluteFaceSize), new Size());
        }
        else if (mDetectorType == NATIVE_DETECTOR) {
            if (mNativeDetector != null)
                mNativeDetector.detect(mFGMask, faces);
        }
        else {
            Log.e(TAG, "Detection method is not selected!");
        }

        Rect[] facesArray = faces.toArray();
        /*
         * Replacing the following commented two-lines with Diego's tracking code
         */
        
        /*for (int i = 0; i < facesArray.length; i++)
            Core.rectangle(mGray, facesArray[i].tl(), facesArray[i].br(), FACE_RECT_COLOR, 3);*/
        for (int i = 0; i < facesArray.length; i++){
    		//assuming compare already had one
    	    if(compare.isEmpty())
    		compare.add(facesArray[i].x);
    	    else{
    		    for(int j = 0; j < compare.size() && j < 4; j++){
    			if(facesArray[i].x > (int) compare.get(j) + 10 || facesArray[i].x < (int) compare.get(j) - 10){
    			    if(compare.size() < 4)
    				compare.add(facesArray[i].x);
    			    Core.rectangle(mFGMask, facesArray[i].tl(), facesArray[i].br(), FACE_RECT_COLOR, 3);
    			}
    			else{
    			    Core.rectangle(mFGMask, facesArray[i].tl(), facesArray[i].br(), OLD_COLOR, 3);
    			}
    		    }   
    	    }
    	}
    	
    	if(compare.size() == 4){
    	//300 might be a good swipe value, also assuming that only hands would be boxed
    		if (facesArray.length > 0 && (facesArray[0].x >= compare.get(3) + 100)){
    			new Thread(new Runnable(){
    				public void run(){
    					Message msg = new Message();
    					msg.what = 2;
    					msg.obj = "Right swipe";
    					toastTeller.sendMessage(msg);
    				}
    		 	}).start();
    			compare.remove(3);
    		}
    			//Toast.makeText(getApplicationContext(), "Right Swipe", Toast.LENGTH_SHORT).show();
    			//right swipe
    		else if (facesArray.length > 0 && (facesArray[0].x <= compare.get(3) - 100)){
    			new Thread(new Runnable(){
    				public void run(){
    					Message msg = new Message();
    					msg.what = 2;
    					msg.obj = "Left swipe";
    					//for front camera opposite swipe!!!
    					toastTeller.sendMessage(msg);
    				}
    		 	}).start();
    			compare.remove(3);
    		}
    	}
        
        
        
        //return mRgba;
        return mFGMask;
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        Log.i(TAG, "called onCreateOptionsMenu");
        mItemFace50 = menu.add("Face size 50%");
        mItemFace40 = menu.add("Face size 40%");
        mItemFace30 = menu.add("Face size 30%");
        mItemFace20 = menu.add("Face size 20%");
        mItemType   = menu.add(mDetectorName[mDetectorType]);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        Log.i(TAG, "called onOptionsItemSelected; selected item: " + item);
        if (item == mItemFace50)
            setMinFaceSize(0.5f);
        else if (item == mItemFace40)
            setMinFaceSize(0.4f);
        else if (item == mItemFace30)
            setMinFaceSize(0.3f);
        else if (item == mItemFace20)
            setMinFaceSize(0.2f);
        else if (item == mItemType) {
            mDetectorType = (mDetectorType + 1) % mDetectorName.length;
            item.setTitle(mDetectorName[mDetectorType]);
            setDetectorType(mDetectorType);
        }
        return true;
    }

    private void setMinFaceSize(float faceSize) {
        mRelativeFaceSize = faceSize;
        mAbsoluteFaceSize = 0;
    }

    private void setDetectorType(int type) {
        if (mDetectorType != type) {
            mDetectorType = type;

            if (type == NATIVE_DETECTOR) {
                Log.i(TAG, "Detection Based Tracker enabled");
                mNativeDetector.start();
            } else {
                Log.i(TAG, "Cascade detector enabled");
                mNativeDetector.stop();
            }
        }
    }
}