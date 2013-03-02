package org.opencv.samples.tutorial3;

import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.UUID;
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
import org.opencv.core.Scalar;
import org.opencv.imgproc.Imgproc;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
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

public class Sample3Native extends Activity implements CvCameraViewListener {
    private static final String TAG = "OCVSample::Activity";

    private Mat                    	mRgba;
    private Mat                    	mGrayMat;
    private CameraBridgeViewBase   	mOpenCvCameraView;
		private File                   	mCascadeFile;
		private MenuItem               	mItemPreviewRGBA;
		private CascadeClassifier      	mJavaDetector;
    private MenuItem               	mItemFace40;
    private byte[]                  right = new byte[]{1};//HI
    private byte[]                  left = new byte[]{0};//HI
    private UUID 										SERIAL_UUID;
    private MenuItem               	mItemFace30;
    private BluetoothDevice         device;
    private MenuItem               	mItemFace20;
    private MenuItem               	mItemFace15;
    private BluetoothAdapter       	adapter = null;
    private OutputStream	   				out = null;
    private BluetoothSocket        	socket;
    private ArrayList<Integer>	   	compare = new ArrayList<Integer>();
    private char 		   							compare_Ind = 0;
    private Handler		   						toastTeller;
    private static final Scalar    	FACE_RECT_COLOR     = new Scalar(0, 255, 0, 255);
    private static final Scalar    	OLD_COLOR     = new Scalar(0, 0, 255, 255);
    private float                  	mRelativeFaceSize   = 0.15f;
    private int                    	mAbsoluteFaceSize   = 0;
    private int			   							REQUEST_ENABLE_BT = 1;
    private BaseLoaderCallback     	mLoaderCallback = new BaseLoaderCallback(this) {
    	
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
					    InputStream is = getResources().openRawResource(R.raw.fist);
	            File cascadeDir = getDir("cascade", Context.MODE_PRIVATE);
	            mCascadeFile = new File(cascadeDir, "fist.xml");
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
									if (msg.what == 2) {
										//Toast.makeText(Sample3Native.this, msg.obj.toString(), Toast.LENGTH_SHORT).show();
										Log.v("GestureRecognizer", msg.obj.toString());
									}
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
	
			BluetoothAdapter adapter = BluetoothAdapter.getDefaultAdapter();
			if (adapter == null) {
	    	// Device does not support Bluetooth
	    	finish(); //exit
			}
			if (!adapter.isEnabled()) {
				//make sure the device's bluetooth is enabled
	    	Intent enableBluetooth = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
	    	startActivityForResult(enableBluetooth, REQUEST_ENABLE_BT);
			}
			SERIAL_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"); //UUID for serial connection
			String mac = "00:06:66:00:D8:EA"; //my laptop's mac adress
			/*if(adapter.checkBluetoothAddress(mac))
	    	Toast.makeText(this, "ok address", Toast.LENGTH_SHORT).show();
			else
	    	Toast.makeText(this, "no ok address", Toast.LENGTH_SHORT).show();*/
			device = adapter.getRemoteDevice(mac); //get remote device by mac, we assume these two devices are already paired


	 		// Get a BluetoothSocket to connect with the given BluetoothDevice
			socket = null;
			out = null;
			try {
	    	socket = device.createRfcommSocketToServiceRecord(SERIAL_UUID); 
			} catch (IOException e) {}
			try {           
	  	  socket.connect(); 
	    	//out = socket.getOutputStream();
	    	
	    	//now you can use out to send output via out.write
			} catch (IOException e) {}
    }

		public void reconnect(){
			BluetoothAdapter adapter = BluetoothAdapter.getDefaultAdapter();
			if (adapter == null) {
	    	// Device does not support Bluetooth
	    	finish(); //exit
			}
			if (!adapter.isEnabled()) {
				//make sure the device's bluetooth is enabled
	    	Intent enableBluetooth = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
	    	startActivityForResult(enableBluetooth, REQUEST_ENABLE_BT);
			}
			SERIAL_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"); //UUID for serial connection
			String mac = "00:06:66:00:D8:EA"; //my laptop's mac adress
			if(adapter.checkBluetoothAddress(mac))
	    	Toast.makeText(this, "ok address", Toast.LENGTH_SHORT).show();
			else
	    	Toast.makeText(this, "no ok address", Toast.LENGTH_SHORT).show();
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
			if (item == mItemFace15){
      	setMinFaceSize(0.15f);
	    	try {
	      	out.write(left); 
	    	} catch (IOException e) {
	    		try {
	    			socket.close(); 	    			
					} catch (IOException f) {Toast.makeText(this, "Can't Close", Toast.LENGTH_SHORT).show();}
					/*try {           
	  	  		socket.connect(); 
	    			out = socket.getOutputStream();
	    			//now you can use out to send output via out.write
					} catch (IOException g) {}*/
	    	}
	   	}
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
    public void onPause(){
    	if (mOpenCvCameraView != null)
      	mOpenCvCameraView.disableView();
      super.onPause();
    }

    @Override
    public void onResume(){
    	super.onResume();
      OpenCVLoader.initAsync(OpenCVLoader.OPENCV_VERSION_2_4_3, this, mLoaderCallback);
    }

    public void onDestroy() {
    	super.onDestroy();
			try {
	    	socket.close(); 
			} catch (IOException e) {}
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
      }

      MatOfRect faces = new MatOfRect();
        
      if (mJavaDetector != null)
      	mJavaDetector.detectMultiScale(mGrayMat, faces, 1.1, 2, 2, // TODO: objdetect.CV_HAAR_SCALE_IMAGE
        	new Size(mAbsoluteFaceSize, mAbsoluteFaceSize), new Size());
      Rect[] facesArray = faces.toArray();
      for (int i = 0; i < facesArray.length; i++){
				//assuming compare already had one
	    	if(compare.isEmpty())
					compare.add(facesArray[i].x);
	    	else{
		    	for(int j = 0; j < compare.size() && j < 4; j++){
						if(facesArray[i].x > (int) compare.get(j) + 10 || facesArray[i].x < (int) compare.get(j) - 10){
			    		if(compare.size() < 4)
								compare.add(facesArray[i].x);
			   			Core.rectangle(mRgba, facesArray[i].tl(), facesArray[i].br(), FACE_RECT_COLOR, 3);
						}
						else{
			    		Core.rectangle(mRgba, facesArray[i].tl(), facesArray[i].br(), OLD_COLOR, 3);
						}
		    	}   
	    	}
			}
	
			if(compare.size() == 4){
				//300 might be a good swipe value, also assuming that only hands would be boxed
					if (facesArray.length > 0 && (facesArray[0].x >= compare.get(3) + 100)){
						/*new Thread(new Runnable(){
							public void run(){
								Message msg = new Message();
								msg.what = 2;
								msg.obj = "Right swipe";
								toastTeller.sendMessage(msg);
							}
		 				}).start();*/try{out.write(right);}
		 				catch (IOException e) {}
						compare.remove(3);
					}
				//Toast.makeText(getApplicationContext(), "Right Swipe", Toast.LENGTH_SHORT).show();
				//right swipe
				else if (facesArray.length > 0 && (facesArray[0].x <= compare.get(3) - 100)){
					/*new Thread(new Runnable(){
						public void run(){
							Message msg = new Message();
						msg.what = 2;
						msg.obj = "Left swipe";
						//for front camera opposite swipe!!!
						toastTeller.sendMessage(msg);
						}
		 			}).start();*/try{out.write(left);}catch (IOException e) {}
					compare.remove(3);
				}
			}
			//Toast.makeText(getApplicationContext(), "Left Swipe", Toast.LENGTH_SHORT).show();
			//left swipe

      return mRgba;
    }

    public native void FindFeatures(String cascade_name, long matAddrGray, long matAddrRgba);
}
