#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "visionrecognition.h"
#include "path.h"
#include "microcontroller.h"

//C/C++ Native libraries
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

//std and OpenCV namespaces
using namespace std;
using namespace cv;


/** @function main */
int main(int argc, const char** argv)
{
	//object declarations
	visionrecognition vrs;
	Path rbtpath;
	VideoCapture capture;
	microcontroller mcrctr;
	Mat frame;

	//main variable declarations
    String window_name = "Harvey Video Feed";
	bool found = false;
	int leg = 0;
	int edge = 10;
	int step = 0;
	int pass = 1;
	int fd;
	char forward = 'f';
	char right = 'r';
	char left = 'l';
	char backward = 'b';
	char direction;
	const char * device = "/dev/ttyACM0";

	fd = open(device, O_RDWR | O_NOCTTY); //open Pololu Maestro microcontroller
	if(fd == -1)
	{
		perror(device);
		cout << "Error opening microcontroller" << endl;
		return 1;
	} //return error if device fails to open

	struct termios options; //struct and termios options for serial port communication
			tcgetattr(fd, &options);
			options.c_iflag &= ~(INLCR | IGNCR | ICRNL | IXON | IXOFF);
			options.c_oflag &= ~(ONLCR | OCRNL);
			options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
			tcsetattr(fd, TCSANOW, &options);

	vrs.getFaceCascade(argc, argv); //load cascade files into main String variables
	vrs.getPlateCascade(argc, argv);
	vrs.getCatCascade(argc, argv);

    //initialize camera feed
    capture.open(0);
    if (!capture.isOpened())
    {
    	cout << "Could not initialize Camera, Sorry m8";
    	return -1;
    }

    while (capture.read(frame)) //infinite loop for video feed
    {
        if(frame.empty())
        {
            cout << "Error -- No frame detected you scallywag";
            break;
        }

        found = vrs.detectObj(frame, found, window_name); //load classifier into frame, function will mark found = true if object detected

        if(!found)
        {
        	cout << "No objects detected" << endl;
        	cout << "Advancing Rover " << endl;

        	if (step < edge) //if not at edge & object !found, move forward
        	{
        		rbtpath.push(forward);
        		cout << "pushed directional command: " << forward << endl;
        		mcrctr.moveForward(fd); //move rover forward
        		step++;
        		cout << "Step: " << step << endl;
        	}
        	else if (step == edge && (leg == 0 || leg == 2))
        	{
        		leg++;
        		edge += 10;
        		rbtpath.push(right);
        		cout << "Pushed directional command" << right << endl;
        		mcrctr.moveRight(fd); //function to move rover right
        		step++;
        		cout << "Step: " << step << endl;
        	}
        	else if (step == edge && (leg == 1 || leg == 3))
        	{
        		leg++;
        		edge += 10;
        		rbtpath.push(left);
        		cout << "Pushed directional command: " << left << endl;
        		mcrctr.moveLeft(fd); //function to move rover left
        		step++;
        		cout << "Step: " << step << endl;
        	}
        	else if (step == edge && leg == 4)
        	{
        		pass++;
        		cout << "Pass complete. Now moving to pass: " << pass << endl;
        		rbtpath.~Path(); //destroy path stack
        		step = 0;
        		leg = 0;
        		edge = 10; //reset path setting variables
        		mcrctr.moveRight(fd);
        		sleep(0.25);
        		mcrctr.moveRight(fd);
        	}
        	else
        		cout << "Unable to push command" << endl; //print to console if error occurs

        }
        else if (found)
        {
        	cout << "object detected" << endl;
        	mcrctr.grabObject(fd);
        	mcrctr.retrieveObject(fd); //grab and retrieve sequence
        	cout << "Object retrieved" << endl;
        	cout << "Returning back to home" << endl;
        	mcrctr.moveRight(fd);
        	sleep(0.25);
        	mcrctr.moveRight(fd); //pivot rover to turn around

        	while(rbtpath.getPathSize() > 0)
        	{
        		direction = rbtpath.pop(); //receive directional node from path stack

        		switch(direction)
        		{
        		  case 'f':
        			  cout << "Received directional command: " << direction << endl;
        			  mcrctr.moveForward(fd);
        			  cout << "Current path size: " << rbtpath.getPathSize() << endl;
        			  step--;
        			  cout << "Step: " << step << endl;
        			  sleep(1);
        			  break;
        		  case 'l':
        			  cout << "Received directional command: " << direction << " Moving right" << endl;
        			  mcrctr.moveRight(fd);
        			  cout << "Current path size: " << rbtpath.getPathSize() << endl;
        			  step--;
        			  cout << "Step: " << step << endl;
        			  sleep(1);
        			  break;
        		  case 'r':
        			  cout << "Received directional command" << direction << " Moving left" << endl;
        			  mcrctr.moveLeft(fd);
        			  cout << "Current path size: " << rbtpath.getPathSize() << endl;
        			  step--;
        			  cout << "Step: " << step << endl;
        			  sleep(1);
        			  break;
        		  case 'b':
        			  cout << "Received directional command" << direction << endl;
        			  mcrctr.moveBackward(fd);
        			  cout << rbtpath.getPathSize() << endl;
        			  step--;
        			  cout << "Step: " << step << endl;
        			  sleep(1);
        			  break;
        		  default:
        			  cout << "Error: could not determine return node" << endl;
        			  break;
        		}
        	}
        	mcrctr.moveRight(fd);
        	sleep(0.25);
        	mcrctr.moveRight(fd); //pivot rover to turn around

        	found = false; //reset found variable
        }

        if(waitKey(10) == 27) //break loop if there is a 10 second delay or hotkey is pressed
        {
        	break;
        }

        else if(pass == 3) //if passes reach 3, end program
        {
        	break;
        }
    }
    return 0;
}
