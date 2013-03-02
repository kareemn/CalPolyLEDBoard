//============================================================================
// Name : opencv_handdetect.cpp
// Author : andol li, andol@andol.info
// Version : 0.1
// Copyright : 2012
// Description : using haartraining results to detect the hand gesture of FIST in video stream.
//
//============================================================================
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <jni.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <vector>

using namespace cv;
using namespace std;

const double scale = 1.1;
const int CAMERA_NUM = 1;

//1.0 api version
CvMemStorage* storage = 0;
CvHaarClassifierCascade* cascade = 0;
void detectAndDraw(IplImage *input_image);
//const char* cascade_name = "hand.xml";

//define the path to cascade file
//string cascadeName = "hand.xml";

extern "C" {
JNIEXPORT void JNICALL Java_org_opencv_samples_tutorial3_Sample3Native_FindFeatures(JNIEnv* jenv, jobject, jstring jFileName, jlong addrGray, jlong addrRgba);

JNIEXPORT void JNICALL Java_org_opencv_samples_tutorial3_Sample3Native_FindFeatures(JNIEnv* jenv, jobject, jstring jFileName, jlong addrGray, jlong addrRgba)
{/*
int main()
{*/
	//1.0 api version

        IplImage frame = *(Mat*)addrRgba;
	IplImage *frame_copy = 0;
	const char* cascade_name = jenv->GetStringUTFChars(jFileName, NULL);
	cascade = (CvHaarClassifierCascade*) cvLoad(cascade_name, 0, 0, 0);
	Mat& mGr  = *(Mat*)addrGray;
        Mat& mRgb = *(Mat*)addrRgba;
        vector<KeyPoint> v;

	
	if (!cascade)
	{
		fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
		return;
	}

	FastFeatureDetector detector(50);
	detector.detect(mGr, v);
	    for( unsigned int i = 0; i < v.size(); i++ )
	    {
        	const KeyPoint& kp = v[i];
        	circle(mRgb, Point(kp.pt.x, kp.pt.y), 10, Scalar(255,0,0,255));
	    }

	storage = cvCreateMemStorage(0);
	/*CvCapture *capture = cvCaptureFromCAM(CAMERA_NUM);

	cvNamedWindow("result", 1);
	if (capture)
	{
		while (1)
		{
			if (!cvGrabFrame(capture))
				break;
			frame = cvRetrieveFrame(capture);

			if (!frame)
			{
				break;
			}
			if (!frame_copy)
			{
				frame_copy = cvCreateImage(cvSize(frame->width, frame->height), IPL_DEPTH_8U, frame->nChannels);
			}
			if (frame->origin == IPL_ORIGIN_TL)
			{
				cvCopy(frame, frame_copy, 0);
			}
			else
			{
				cvFlip(frame, frame_copy, 0);
			}
			detectAndDraw(frame_copy);
			if (cvWaitKey(10) >= 0)
			{
				break;
			}
		}
		cvReleaseImage(&frame_copy);
		cvReleaseCapture(&capture);
	}*/
		while(1){
			if (!frame_copy)
			{
				frame_copy = cvCreateImage(cvSize(frame.width, frame.height), IPL_DEPTH_8U, frame.nChannels);
			}
			if (frame.origin == IPL_ORIGIN_TL)
			{
				cvCopy(&frame, frame_copy, 0);
			}
			else
			{
				cvFlip(&frame, frame_copy, 0);
			}
			detectAndDraw(frame_copy);
			if (cvWaitKey(10) >= 0)
			{
				break;
			}
		}	
		cvReleaseImage(&frame_copy);
	return;
}
}

void detectAndDraw(IplImage *img)
{
	double scale = 1.1;
	IplImage* temp = cvCreateImage(cvSize(img->width/scale,img->height/scale), 8, 3);
	CvPoint pt1, pt2;
	int i;

	cvClearMemStorage(storage);
	if (cascade)
	{
		CvSeq *hands = cvHaarDetectObjects(img, cascade, storage, scale, 2, CV_HAAR_DO_CANNY_PRUNING, cvSize(24, 24));
		for (i = 0; i < (hands?hands->total:0); i++)
		{
			CvRect* r = (CvRect*)cvGetSeqElem(hands, i);
			pt1.x = r->x*scale;
			pt2.x = (r->x+r->width)*scale;
			pt1.y = r->y*scale;
			pt2.y = (r->y+r->height)*scale;
			cvRectangle(img, pt1, pt2, CV_RGB(200, 0, 0), 1, 8, 0);
		}
	}
	cvShowImage("result", img);
	cvReleaseImage(&temp);
}
