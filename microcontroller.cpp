#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include "microcontroller.h"

using namespace std; 

microcontroller::microcontroller()
{
	fd = 0; 
	position = 0; 
	target = 0; 
}

microcontroller::getPosition(int fd, unsigned char channel)
{
	unsigned char command[] = {0x90, channel}; 
	if(write(fd,command, sizeof(command)) == -1)
	{
		perror("Error"); 
		return -1; 
	}
	
	unsigned char response[2]; 
	if (read(fd,response,2) != 2)
	{
		perror("Error"); 
		return -1; 
	}
	
	return response[0] + 256*response[1]; 
	
}

microcontroller::setTarget(int fd, unsigned char channel, unsigned short target)
{
	unsigned char command[] = {0x84, channel, target & 0x7F, target >> 7 & 0x7F}; 
	if (write(fd, command, sizeof(command)) == -1)
	{
		perror("Error"); 
		return -1; 
	}
	return 0; 
}

void microcontroller::moveForward(int fd)
{
  setTarget(fd, 4, 7136); 
  setTarget(fd, 5, 5651); 	  
}

void microcontroller::moveBackward(int fd)
{
	
}

void microcontroller::moveRight(int fd)
{
	
}

void microcontroller::moveLeft(int fd)
{
	
}

void microcontroller::moveBase(int fd, int target) //member function to move arm base up or down
{
	int position = getPosition(fd, 0); //receives servo position from control board
	
	if (target == position) //checks if servo is already at target position
	{
	  cout << "Base already at desired position" << endl; 	
	} 
	else if (target > position) //move the base up if target is greater than current position
	{
		for (int i = position; i < target; i++)
		{
			setTarget(fd, 0, i); 
			sleep(0.75); 
		}
	}
	else if (target < position) //move base down if target is less than current position
	{
		for (int j = position; j > target; j--)
		{
			setTarget(fd, 0, j); 
			sleep(0.75); 
		}
	}
	else //print error message to console if a failure occurs
	{
		cout << "Error: Could not move to position" << endl; 
	}
}

void microcontroller::moveForearm(int fd, int target) //member function for forearm servo movement 
{
	int position = getPosition(fd, 3); //get forearm servo position 
	
	if (target == position)
	{
		cout << "Forearm is already at target position" << endl; 
	}
	else if (target > position) //if forearm target is greater than current position, move servo up
	{
		for (int i = position; i < target; i++)
		{
			setTarget(fd, 3, i); 
			sleep(0.75); 
		}
	}
	else if (target < position) //if target is less than current position, move servo down
	{
		for (int j = position; j > target; j-- )
		{
			setTarget(fd, 3, j); 
			sleep(0.75); 
		}
	}
	else //if unable to communicate with servo, print error message to console
	{
		cout << "Error: could not move to target position" << endl; 
	}
}

void microcontroller::moveWrist(int fd, int target) //member function for wrist servo movement
{
	int position = getPosition(fd, 2); 
	
	if (target == position) //print to console if servo is presently at target location
	{
		cout << "Servo located in target position" << endl; 
	}
	else if (target > position) //if target is greater than position, move wrist servo up 
	{
		for (int i = position; i < target; i++)
		{
			setTarget(fd, 2, i); 
			sleep(0.75); 
		}
	}
	else if (target < position) //if target is less than position, move wrist servo down
	{
		for (int j = position; j > position; j--)
		{
			setTarget(fd, 2, j); 
			sleep(0.75); 
		}
	}
	else //print error message to console if failure occurs
	{
		cout << "Error: could not communicate with wrist servo" << endl; 
	}
}

void microcontroller::openGripper(int fd)
{
	setTarget(fd, 1, 8000); 
}

void microcontroller::closeGripper(int fd)
{
	setTarget(fd, 1, 6000); 
}

void microcontroller::setInitialPosition(int fd)
{
  moveWrist(fd, 6000); 
  sleep(0.75); 
  moveForearm(fd, 7000);
  sleep(0.75); 
  moveBase(fd, 6000); 	
  sleep(0.75); 
  openGripper(fd); 
  sleep(0.75); 
}

void microcontroller::grabObject(int fd)
{
  moveBase(fd, 4000); 
  sleep(0.75); 
  moveWrist(fd, 5000); 
  sleep(0.75); 
  moveForearm(fd, 7000); 
  sleep(0.75);    
}

void microcontroller::retrieveObject(int fd)
{
	closeGripper(fd); 
	sleep(0.75); 
	moveBase(fd, 5000); 
	sleep(0.75); 
	
}
