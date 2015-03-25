#include "Movie.h"
#include <algorithm>
#include <sstream>

using namespace std;


Movie::Movie (string t)
{
	title = t;
}      // constructor for a movie with the given title

Movie::Movie (const Movie & other)
{
	title = other.title;
}  // copy constructor

Movie::~Movie ()
{
}                  // destructor

string Movie::getTitle () const
{
	return title;
}  // returns the title of the movie

void Movie::addKeyword (string keyword)
{
	keywords.add(keyword);
}
  /* Adds the (free-form) keyword to this movie.
     If the exact same keyword (up to capitalization) was already
     associated with the movie, then the keyword is not added again. */

Set<string> Movie::returnActors() const
{
	return actors;
}

Set<string> Movie::getAllKeywords () const
{
  return keywords;
}

  /* Returns a set of all keywords associated with the movie. */

void Movie::printMovie ()
{
	cout << title <<  endl;
	keywords.printAll();
}

string Movie::returnKeywords() const
{
	string keyword = "Keywords\n";
	for ( Set<string>::Iterator si = this->keywords.begin(); si != this->keywords.end(); ++si )
	{
		keyword = keyword + *si + "\n";
	}
	keyword = keyword + "\nActors\n";
	for ( Set<string>::Iterator si = this->actors.begin(); si != this->actors.end(); ++si )
	{
		keyword = keyword + *si + "\n";
	}

	return keyword;
}

void Movie::addActor (string actor)
{
	actors.add(actor);
}

int Movie::getPrice()
{
	return price;
}

void Movie::setPrice(int p)
{
	price = p;
}