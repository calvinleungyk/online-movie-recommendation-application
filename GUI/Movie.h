#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include "Set.h"
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

    void addActor (string actor); 
    string returnKeywords() const;
    Set<string> returnActors() const;
    int getPrice();
    void setPrice(int p);

  private:
    string title;
    Set<string> keywords;
    Set<string> actors;
    int price;
    
    // you get to decide what goes here
};

#endif