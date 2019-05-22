#ifndef MICROCONTROLLER_H
#define MICROCONTROLLER_H

class microcontroller
{
	public: 
		microcontroller(); 
		int getPosition(int, unsigned char); 
		int setTarget(int, unsigned char, unsigned short); 
		void moveForward(int); 
		void moveBackward(int); 
		void moveLeft(int); 
		void moveRight(int); 
		void moveBase(int, int); 
		void moveForearm(int, int); 
		void moveWrist(int, int); 
		void openGripper(int); 
		void closeGripper(int); 
		void setInitialPosition(int); 
		void grabObject(int); 
		void retrieveObject(int); 
		
		
	private:  
		int fd; 
		int position; 
		int target; 	
	
}; 


#endif
