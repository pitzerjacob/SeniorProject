#include <iostream>
#include "path.h"

using namespace std; 

Path::Path()
{
	pathsize = 0; 
}

Path::~Path()
{
	Node *temp; 
	char tempchar; 
	
	while(pathsize != 0)
	{
	
	  if (pathsize != 0)
	  {
		   temp = top; 
		   top = top -> next; 
		   tempchar = temp -> direc; 
		   delete temp; 
		   temp = 0;
		   pathsize --;  
	  }
	  else if (pathsize == 1)
	  {
		  temp = top; 
		  top = top -> next; 
		  tempchar = temp -> direc; 
		  delete temp; 
		  temp = 0; 
		  top = NULL; 
		  delete top; 
		  pathsize --; 
	  }
    }
}

void Path::push(char data) //member function for pushing directional node onto the path stack 
{ 
	Node *entry; 
	entry = new Node; //create an instance of a new node 
	
	entry -> direc = data; 
	entry -> next = top; 
	top = entry; 
	
	pathsize++; 
}

char Path::pop() //member function for popping directional nodes off the path stack 
{
	Node *temp; 
	char currdirec; //value for direction data popped off stack 
	
	if (pathsize != 0)
	{
		 temp = top; 
		 top = top -> next; 
		 currdirec = temp -> direc; 
		 delete temp; 
		 temp = 0;
		 pathsize --;  
		 return currdirec; 
	}
	else if (pathsize == 1)
	{
		temp = top; 
		top = top -> next; 
		currdirec = temp -> direc; 
		delete temp; 
		temp = 0; 
		top = NULL; 
		delete top; 
		pathsize --; 
	}
	else
		cout << "Path stack is empty bruh" << endl; 
	
}

int Path::getPathSize()
{
	return pathsize; 
}
