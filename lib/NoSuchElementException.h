#include <exception>

#ifndef NOSUCHELEMENTEXCEPTION_H
#define NOSUCHELEMENTEXCEPTION_H

class NoSuchElementException: public std::exception
{
public:

	const char * what () const throw ()
	  {
	    return "";
	    //return "The element you are looking for does not exist!";
	  }
};

#endif