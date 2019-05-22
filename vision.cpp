/*
 * visionrecognition.cpp
 *
 *  Created on: Feb 28, 2018
 *      Author: Supreme Leader Jake
 *
 */

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "visionrecognition.h"

#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

visionrecognition::visionrecognition()
{
  String face_cascade_name = "";
  String cat_cascade_name = "";
  String plate_cascade_name = "";
  CascadeClassifier face_cascade;
  CascadeClassifier plate_cascade;
  CascadeClassifier cat_cascade;
}

bool visionrecognition::detectObj(Mat frame, bool found, String window_name)
{
	vector<Rect> faces; //create rectangle vectors for target images
	vector<Rect> cats;
	vector<Rect> plates;
	Mat frame_gray; //create greyframe mat image

    const static Scalar colors[] =
    {
        Scalar(255,0,0),
        Scalar(255,128,0),
        Scalar(255,255,0),
        Scalar(0,255,0),
        Scalar(0,128,255),
        Scalar(0,255,255),
        Scalar(0,0,255),
        Scalar(255,0,255)
    }; //scalar array of frame color values

	cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
	equalizeHist( frame_gray, frame_gray );

	//Detect object functions
	face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(60, 60) );


	for ( size_t i = 0; i < faces.size(); i++ ) //if face detected, place rectangle over the center
	{

	  Rect r = faces[i];
	  Point center;
	  Scalar color = colors[i%8]; //create scalar of colors
	  double scale = 1;

	  rectangle( frame, Point(cvRound(r.x*scale), cvRound(r.y*scale)),
                 Point(cvRound((r.x + r.width-1)*scale), cvRound((r.y + r.height-1)*scale)),
                 color, 3, 8, 0); //create the rectangle

	  found = true; //return true, object found
	}

	for ( size_t j = 0; j < cats.size(); j++ ) //if cat detected, place a rectangle around it
	{

	  Rect r2 = cats[j];
	  Point center2;
	  Scalar color2 = colors[j%8];
	  double scale2 = 1;

	  rectangle( frame, Point(cvRound(r2.x*scale2), cvRound(r2.y*scale2)),
	             Point(cvRound((r2.x + r2.width-1)*scale2), cvRound((r2.y + r2.height-1)*scale2)),
	              color2, 3, 8, 0); //create the rectangle


	  Mat catROI = frame_gray( cats[j] );

	  found = true; //return true, object found
	}

	for ( size_t k = 0; k < plates.size(); k++ ) //if plate found, place a rectangle around it
	{

		Rect r3 = plates[k];
		Point center3;
		Scalar color3 = colors[k%8];
		double scale3 = 1;

		rectangle( frame, Point(cvRound(r3.x*scale3), cvRound(r3.y*scale3)),
		           Point(cvRound((r3.x + r3.width-1)*scale3), cvRound((r3.y + r3.height-1)*scale3)),
		           color3, 3, 8, 0); //draw the rectangle

        Mat plateROI = frame_gray( plates[k] );

		found = true; //return true, object found
	}

	//show the video feed
	imshow(window_name, frame);

	return found;
}

void visionrecognition::getFaceCascade(int argc, const char ** argv) //load the face cascade file
{
	CommandLineParser parser(argc, argv,
			"{face_cascade|/media/jake/NDrive/opencv/data/haarcascades/haarcascade_frontalface_alt.xml|}"); //get face cascade from openCV data folder
	face_cascade_name = parser.get<String>("face_cascade"); //set cascade to face_cascade string

	if (!face_cascade.load(face_cascade_name)) //if fail to load, print error message to console
	{
		cout << "Failure to load face cascade" << endl;
	}

}

void visionrecognition::getPlateCascade(int argc, const char ** argv) //load the plate cascade file
{
	CommandLineParser parser(argc, argv,
					"{plate_cascade|/media/jake/NDrive/opencv/data/haarcascades/haarcascade_license_plate_rus_16stages.xml");
		plate_cascade_name = parser.get<String>("plate_cascade");

		if (!plate_cascade.load(plate_cascade_name))
		{
			cout << "failure to load plate cascade" << endl;
		}

}

void visionrecognition::getCatCascade(int argc, const char ** argv) //load the cat cascade file
{
	CommandLineParser parser(argc, argv,
				"{cat_cascade|/media/jake/NDrive/opencv/data/haarcascades/haarcascade_frontalcatface.xml");
	cat_cascade_name = parser.get<String>("cat_cascade");

	if (!cat_cascade.load(cat_cascade_name))
	{
		cout << "failure to load cat cascade" << endl;
	}
}


