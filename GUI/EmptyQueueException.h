#include <exception>

#ifndef EMPTYQUEUEEXCEPTION_H
#define EMPTYQUEUEEXCEPTION_H

class EmptyQueueException: public std::exception
{
public:

	const char * what () const throw ()
	  {
	    return "";
	    //return "The element you are looking for does not exist!";
	  }
};

#endif