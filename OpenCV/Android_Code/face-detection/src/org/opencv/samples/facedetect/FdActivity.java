package org.opencv.samples.facedetect;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

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
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.PowerManager;
import android.os.PowerManager.WakeLock;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.WindowManager;

import java.util.Calendar;

public class FdActivity extends Activity implements CvCameraViewListener2 {

    private static final String     TAG                 = "OCVSample::Activity";
    private static final Scalar     HAND_RECT_COLOR     = new Scalar(0, 255, 0, 255);
    //private static final Scalar   WHITE_COLOR          = new Scalar(255, 255, 255, 255);
    //private static final Scalar   OLD_COLOR		     = new Scalar(0, 0, 255, 255);
    public static final int         JAVA_DETECTOR       = 0;
    public static final int         NATIVE_DETECTOR     = 1;
    public static final int         NUM_FRAMES_TO_LEARN_FROM = 13;
    private static final int        START_HOUR          = 6;
    private static final int        END_HOUR            = 19;

    private MenuItem                mItemHand40;
    private MenuItem                mItemHand30;
    private MenuItem                mItemHand20;
    private MenuItem                mItemHand15;
    private MenuItem                mItemType;

    private Mat                     mRgba;
    private Mat                     mGray;

    private File                    mCascadeFile;
    private CascadeClassifier       mJavaDetector;
    private DetectionBasedTracker   mNativeDetector;

    private int                     mDetectorType       = JAVA_DETECTOR;
    private String[]                mDetectorName;

    private float                   mRelativeHandSize   = 0.2f;
    private int                     mAbsoluteHandSize   = 0;

    private CameraBridgeViewBase    mOpenCvCameraView;
    //my guys
    private Mat						mRgb;
    private Mat						mFGMask;
    private BackgroundSubtractorMOG sub;
    /*private int 					bgCount;
    private ArrayList<Integer>		compare;
    private Handler                 toastTeller;*/

    //diego's guys
    private BluetoothAdapter        adapter             = null;
    private boolean                 check               = true;
    private BluetoothDevice         device;
    private int                     display_len         = 160;


    private OutputStream            out                 = null;
    private byte[]                  pos; 
    private int                     curr_pos            = 0;
    private int                     prev_pos            = 0;
    private int                     curr_y              = 600;
    private byte[]                  up                  = new byte[]{(byte)201};//{(byte)'u'};
    private byte[]                  right               = new byte[]{(byte)202};//{(byte)'r'};
    private byte[]                  left                = new byte[]{(byte)203};//{(byte)'l'};     
    private byte[]                  power_on            = new byte[]{(byte)255};//{(byte)'r'};
    private byte[]                  power_off           = new byte[]{(byte)254};//{(byte)'l'}; 
    private boolean                 swipe_up            = false;
    private boolean                 swipe_r             = false;
    private boolean                 swipe_l             = false;
    private int                     REQUEST_ENABLE_BT   = 1;
    private UUID                    SERIAL_UUID;
    private float                   screen_pos          = .166f;
    private BluetoothSocket         socket;


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
                    InputStream is = getResources().openRawResource(R.raw.haarcascade_fist);
                    File cascadeDir = getDir("cascade", Context.MODE_PRIVATE);
                    mCascadeFile = new File(cascadeDir, "haarcascade_fist.xml");
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
                    /*toastTeller = new Handler() {
                            public void handleMessage(Message msg) {
                                if (msg.what == 2)
                                Toast.makeText(FdActivity.this, msg.obj.toString(), Toast.LENGTH_SHORT).show();
                                super.handleMessage(msg);
                            }
                        };*/

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

    /*
     * Called when the activity is first created!
     * On create, disable sleep mode, set up the bluetooth connection.
     */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        Log.i(TAG, "called onCreate");
        super.onCreate(savedInstanceState);

        setContentView(R.layout.face_detect_surface_view);

        mOpenCvCameraView = (CameraBridgeViewBase) findViewById(R.id.fd_activity_surface_view);
        mOpenCvCameraView.setCvCameraViewListener(this);

        /*
         * Disable sleep
         */
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        /*
         * COMMUNICATE WITH HARDWARE
         */
        adapter = BluetoothAdapter.getDefaultAdapter();
        if (adapter == null) {
            // Device does not support Bluetooth
            finish(); //exit
        }
        if (!adapter.isEnabled()) {
            //make sure the device's bluetooth is enabled
            Intent enableBluetooth = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            //Intent testConnection = new Intent(BluetoothDevice.ACTION_ACL_DISCONNECTED);
            startActivityForResult(enableBluetooth, REQUEST_ENABLE_BT);
        }
        SERIAL_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"); //UUID for serial connection
        //String mac = "00:06:66:00:D8:EA"; //my laptop's mac adress
        String mac = "00:06:66:00:D8:EA"; 
        device = adapter.getRemoteDevice(mac); //get remote device by mac, we assume these two devices are already paired


        // Get a BluetoothSocket to connect with the given BluetoothDevice
        socket = null;
        out = null;
        try {
            socket = device.createRfcommSocketToServiceRecord(SERIAL_UUID); 
        } catch (IOException e) {}
        try {           
            socket.connect(); 
            out = socket.getOutputStream();

            //now you can use out to send output via out.write
        } catch (IOException e) {}
    }

    public void reconnect(){

        // Get a BluetoothSocket to connect with the given BluetoothDevice*/            
        try{
            socket.close();
            if(out != null){
                out.close();
            }
        }
        catch (IOException e) {}

        socket = null;
        out = null;
        try {
            socket = device.createRfcommSocketToServiceRecord(SERIAL_UUID); 
        } catch (IOException e) {}
        try {           
            socket.connect();
        } catch (IOException e) {}
        try{
            out = socket.getOutputStream();
        }
        catch (IOException e) {}
        if(out != null)
            Log.v("Output Stream ", "connected");
    }

    @Override
    public void onPause()
    {
        super.onPause();
        if (mOpenCvCameraView != null)
            mOpenCvCameraView.disableView();
        /*
         * Send a message to turn the board OFF
         */
        lowPower(true);
    }

    @Override
    public void onResume()
    {
        super.onResume();
        OpenCVLoader.initAsync(OpenCVLoader.OPENCV_VERSION_2_4_3, this, mLoaderCallback);
        /*
         * Send a message to turn the board ON
         */
        lowPower(false);
    }

    /*
     * On destroy, turn off the camera.
     */
    public void onDestroy() {
        super.onDestroy();
        mOpenCvCameraView.disableView();
    }

    public void onCameraViewStarted(int width, int height) {
        mGray = new Mat();
        mRgba = new Mat();
        mRgb = new Mat();
        mFGMask = new Mat();
        /*
         * Use all of this junk later when improving the hand detection

        sub = new BackgroundSubtractorMOG();
        sub.setInt("nmixtures", 1);
    	bgCount = 0;
    	compare = new ArrayList<Integer>();
         */
    }

    public void onCameraViewStopped() {
        mGray.release();
        mRgba.release();
        mRgb.release();
        mFGMask.release();
    }

    /*
     * This is not currently in use.
     */

    public void learnBackground(double learningRate) {
        Imgproc.cvtColor(mGray, mRgb, Imgproc.COLOR_GRAY2RGB);
        sub.apply(mRgb, mFGMask, learningRate);//exports a gray image
        Imgproc.threshold(mFGMask, mFGMask, 128, 255, Imgproc.THRESH_BINARY);
        Imgproc.medianBlur(mFGMask, mFGMask, 9);
        Imgproc.erode(mFGMask, mFGMask, new Mat());
        Imgproc.dilate(mFGMask, mFGMask, new Mat());
        mGray.copyTo(mFGMask, mFGMask);
    }

    /*
     * This method is primarily here for debugging.
     * If you touch the screen, it should force show the low-power screen.
     * @see android.app.Activity#onTouchEvent(android.view.MotionEvent)
     */
    @Override
    public boolean onTouchEvent(MotionEvent event) {
        Intent myIntent = new Intent(this, LowPowerActivity.class);
        startActivity(myIntent);
        return super.onTouchEvent(event);
    }

    public boolean timeForLowPowerMode() {

        Calendar cal = Calendar.getInstance();
        int currentHour = cal.get(Calendar.HOUR_OF_DAY);
        if(END_HOUR < currentHour && currentHour < START_HOUR) {
            Intent myIntent = new Intent(this, LowPowerActivity.class);
            startActivity(myIntent);
            return true;
        }

        return false;
    }

    public Mat onCameraFrame(CvCameraViewFrame inputFrame) {

        mRgba = inputFrame.rgba();
        mGray = inputFrame.gray();

        if(timeForLowPowerMode())
            return mGray;

        /*if (mDetectorType == JAVA_DETECTOR) {
          //backgroundFilter the first NUM_FRAMES_TO_LEARN_FROM
            if(bgCount++ < NUM_FRAMES_TO_LEARN_FROM)
                learnBackground(0.0);
            else {
                bgCount = 0;
                learnBackground(-1);
            }
            //learnBackground(-1);
        }
        else if (mDetectorType == NATIVE_DETECTOR) {
            //mFGMask = mNativeDetector.learnBackground(mFGMask);
        }
        else {
            Log.e(TAG, "Detection method is not selected!");
        }*/


        //trial junk
        /*if(lastFrame.empty())
            lastFrame = mRgba; //should be CV_32FC1 or CV_64FC1
        else { //phase correlate this frame to last frame
            //Imgproc.cvtColor(mRgba, currentFrame, Imgproc.COLOR_RGBA2mRGBA);
            currentFrame = mRgba;
            //mRgba.convertTo(currentFrame, Imgproc.CV_32FC1, 1, 0);
            subPixel = Imgproc.phaseCorrelate(lastFrame, currentFrame);
        }*/

        /*
         * haar stuff
         */

        if (mAbsoluteHandSize == 0) {
            int height = mGray.rows();
            if (Math.round(height * mRelativeHandSize) > 0) {
                mAbsoluteHandSize = Math.round(height * mRelativeHandSize);
            }
            mNativeDetector.setMinFaceSize(mAbsoluteHandSize);
        }

        MatOfRect hands = new MatOfRect();

        if (mDetectorType == JAVA_DETECTOR) {
            if (mJavaDetector != null)
                mJavaDetector.detectMultiScale(mGray, hands, 1.1, 2, 2, // TODO: objdetect.CV_HAAR_SCALE_IMAGE
                        new Size(mAbsoluteHandSize, mAbsoluteHandSize), new Size());
        }
        else if (mDetectorType == NATIVE_DETECTOR) {
            if (mNativeDetector != null)
                mNativeDetector.detect(mGray, hands);
        }
        else {
            Log.e(TAG, "Detection method is not selected!");
        }

        Rect[] handsArray = hands.toArray();

        /*
         * This following code prints only the first detected box
         * It uses this detection to send control messages to the bluetooth
         */
        if (handsArray.length > 0){
            Core.rectangle(mRgba, handsArray[0].tl(), handsArray[0].br(), HAND_RECT_COLOR, 3);

            /*
             * Talk to the bluetooth
             */

            //log all locations and test to see what swipe would be best!!!!!
            pos = new byte[]{(byte)(display_len-((handsArray[0].width+handsArray[0].x)*screen_pos))};
            curr_pos = handsArray[0].x;
            if(check){
                if((curr_pos - prev_pos) > 300)
                    swipe_l = true;
                else if((curr_pos - prev_pos) < - 300)
                    swipe_r = true;
                else if(curr_y + 100 < handsArray[0].y)
                    swipe_up = true;
            }
            else
                check = true;

            if(swipe_up || swipe_l || swipe_r)
                check = false;

            //else
            curr_y = handsArray[0].y;
            prev_pos = curr_pos;
            try {
                if(out != null){
                    if(swipe_l){
                        Log.v("Swipe ", "swipe left");
                        out.write(left);
                        swipe_l = false;
                    }
                    else if(swipe_r){
                        Log.v("Swipe ", "swipe right");
                        out.write(right);
                        swipe_r = false;
                    }
                    else if(swipe_up){
                        Log.v("Swipe ", "swipe up");
                        out.write(up);
                        swipe_up = false;
                    }
                    else                    
                        out.write(pos);
                }
                else{
                    reconnect(); 
                }
            } catch (IOException e) {}
        }

        /*
         * On Screen notifications:
         * there exist two alerts: "swipe left" and "swipe right"
         *
       if(compare.size() == 4){
           //300 might be a good swipe value, also assuming that only hands would be boxed
           if (handsArray.length > 0 && (handsArray[0].x >= compare.get(3) + 100)){
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
           else if (handsArray.length > 0 && (handsArray[0].x <= compare.get(3) - 100)){
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
       }*/



        return mRgba;
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        Log.i(TAG, "called onCreateOptionsMenu");
        mItemHand40 = menu.add("Hand size 40%");
        mItemHand30 = menu.add("Hand size 30%");
        mItemHand20 = menu.add("Hand size 20%");
        mItemHand15 = menu.add("Hand size 15%");
        mItemType   = menu.add(mDetectorName[mDetectorType]);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        Log.i(TAG, "called onOptionsItemSelected; selected item: " + item);
        if (item == mItemHand15){
            setMinHandSize(0.15f);
            reconnect();
        }
        else if (item == mItemHand40){
            setMinHandSize(0.4f);
            try{
                out.write(up);
            }
            catch (IOException e) {}
        }
        else if (item == mItemHand30)
            setMinHandSize(0.3f);
        else if (item == mItemHand20)
            setMinHandSize(0.2f);
        else if (item == mItemType) {
            mDetectorType = (mDetectorType + 1) % mDetectorName.length;
            item.setTitle(mDetectorName[mDetectorType]);
            setDetectorType(mDetectorType);
        }
        return true;
    }

    private void setMinHandSize(float handSize) {
        mRelativeHandSize = handSize;
        mAbsoluteHandSize = 0;
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

    public void lowPower(boolean enterLowPower){
        try{
            if(out != null){
                if(!enterLowPower){
                    Log.v("Intents ", "not reached");
                    out.write(power_on);
                }
                else{
                    out.write(power_off);
                    Log.v("Intents ", "reached");
                    /*Intent myIntent = new Intent(this, LowPowerActivity.class);
                    startActivity(myIntent);*/
                }
            }
        } catch (IOException e) {}
    }
}
