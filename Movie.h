#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include "../lib/Set.h"
using namespace std;

class Movie {
  public: 
    Movie (string title);       // constructor for a movie with the given title

    Movie (const Movie & other);  // copy constructor

    ~Movie ();                  // destructor

    string getTitle () const;   // returns the title of the movie

    void addKeyword (string keyword); 
      /* Adds the (free-form) keyword to this movie.
         If the exact same keyword (up to capitalization) was already
         associated with the movie, then the keyword is not added again. */

    Set<string> getAllKeywords () const;
      /* Returns a set of all keywords associaed with the movie. */
    void printMovie();

    string returnKeywords() const;

  private:
    string title;
    Set<string> keywords;
    
    // you get to decide what goes here
};

#endif