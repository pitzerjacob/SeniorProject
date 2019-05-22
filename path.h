/*
CLASS SUMMARY: PATH.H 
Path.h defines a stack of characters that can be of any size.  
The sole purpose of the stack is to track robot movements in 
the field of operation.  while the robot is seaching for objects
the main file will push directions moved unto the stack.  Once an 
object is found or the robot reaches the end of a search path, 
values will be popped off until the stack is empty

FUNCTION DEFINITIONS: 
Path() DEFAULT CONSTRUCTOR: 
PRE-CONDITIONS: NONE
POST-CONDITIONS: NONE
DESCRIPTION: 
Default constructor for Path.h.  Initializes path size to 0 once
program begins. 

~Path() DEFAULT DESTRUCTOR: 
PRE-CONDITIONS: NONE
POST-CONDITIONS: NONE
DESCRIPTION: 
Default destructor for path.h.  At the end of the program, main will 
call destructor to destroy anything remaining of the stack to free 
memory.  Called when the robot makes a pass and does not find any 
objects.   

push() PUSH ON STACK FUNCTION: 
PRE-CONDITIONS: CHAR
POST-CONDITIONS: NONE
DESCRIPTION: 
Push function for path.h.  Function will take a char input and push it 
onto the stack.  Function will also increment the stack size counter, 
initialized by the constructor

pop() POP OFF STACK FUNCTION: 
PRE-CONDITIONS: NONE
POST-CONDITIONS: CHAR
DESCRIPTION: 
Pop function for path.h.  Function will pop off the top character from 
the stack and return it to the main program.  It will decrement the 
stack size counter.

getPathSize() STACK SIZE COUNTER: 
PRE-CONDITIONS: NONE
POST-CONDITIONS: INT 
DESCRIPTION: 
Returns the stack size whenever called.  Either from main or from the 
path class
*/

#ifndef PATH_H
#define PATH_H

class Path 
{
 	public: 
 		Path(); //default constructor for Path class
 		~Path(); //default destructor for Path class 
 		void push(char); //pushes a direction value onto the stack 
 		int getPathSize(); //returns path size 
 		char pop(); //pops a directional value back to the main program 
	 
	
	private: 
		struct Node { //struct data type for Node
			char direc; 
			Node *next; 
		};	
		
		struct Node *top; //pointer for top of the stack
		int pathsize; //counter for path stack size 
	
}; 


#endif
