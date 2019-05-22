/* VISION RECOGNITION
 * CLASS DEFINITION:
 * This class defines the attributes and functions for VISION RECOGNITION
 * Performs all cascade file loading, object detection, and drawing targets
 * on the video screen
 *
 * FUNCTION DEFINITIONS:
 *
 * visionrecognition() : DEFAULT CONSTRUCTOR
 * PRE-CONDITIONS: NONE
 * POST-CONDITIONS: NONE
 * DESCRIPTION:
 * default constructor for vision recognition class.  Initializes
 * Cascade classifiers and string variables
 *
 * detectObj() : FUNCTION FOR OBJECT RECOGNITION
 * PRE-CONDITIONS: MAT, BOOLEAN, STRING
 * POST-CONDITIONS: BOOLEAN
 * DESCRIPTION:
 * Function for object detection.  This function accepts a Mat object,
 * a boolean, and a String.  Uses CascadeClassifier definitions to
 * scan image frame.  If an object is found, function will place a rectangle
 * around the center and return true.  else, it will remain false and return
 * false
 *
 * getFaceCascade() : FUNCTION FOR LOADING FACE CLASSIFIER
 * PRE-CONDITIONS: INT, CONST CHAR
 * POST-CONDITIONS: NONE
 * DESCRIPTION:
 * Function for loading face classifier file.  If successful, it will
 * set the string to the face classifier file, if failure it will print
 * a error message to the screen
 *
 * getPlateCascade() : FUNCTION FOR LOADING PLATE CLASSIFIER
 * PRE-CONDITIONS: INT, CONST CHAR
 * POST-CONDITIONS: NONE
 * DESCRIPTION:
 * Function for loading the plate classifier file.  If successful, it will
 * set the string to the plate classifier file.  If there is a failure,
 * a message will be printed to the console
 *
 * getCatCascade() : FUNCTION FOR LOADING PLATE CLASSIFIER
 * PRE-CONDITIONS: INT, CONST CHAR
 * POST-CONDITIONS: NONE
 * DESCRIPTION:
 * Function for loading the cat classifier file.  If successful, it will
 * set the string to the plate classiifer file.  If there is a failure, a m
 * message will be printed to the console.
 * visionrecognition.h
 *
 *  Created on: Feb 28, 2018
 *      Author: Supreme Leader Jake
 */

#ifndef VISIONRECOGNITION_H
#define VISIONRECOGNITION_H

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

class visionrecognition {

	public:
		visionrecognition(); //default constructor for vision recognition class
		bool detectObj(Mat, bool, String);
		void getFaceCascade(int, const char **);
		void getPlateCascade(int, const char **);
		void getCatCascade(int, const char **);


	private:
		String face_cascade_name;
		String cat_cascade_name;
		String plate_cascade_name;
		CascadeClassifier face_cascade;
		CascadeClassifier plate_cascade;
		CascadeClassifier cat_cascade;


};


#endif /* VISIONRECOGNITION_H */
