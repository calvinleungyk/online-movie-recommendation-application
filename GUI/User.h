#ifndef USER_H
#define USER_H
#include <string>
#include <iostream>
#include "Map.h"
#include <vector>
#include <utility>
#include "Movie.h"
#include "./lib/Queue.h"

using namespace std;

class User {
  public:
    User (string ID, string name);
;  
    /* constructor that generates a user with the given name and ID.
       While multiple users may have the same name, the ID should be unique
       (e.g., an e-mail address), so that users can log in with it. */

    User (const User & other); // copy constructor

    ~User ();            // destructor

    string getID () const;    // returns the ID associated with this user
    string getName () const;  // returns the name associated with this user

    Queue<Movie*> * movieQueue (); 
      /* returns a pointer to the user's movie queue.
         This is the easiest way to ensure that you can modify the queue.
         (If you return by reference, that's also possible, but you'd need
         to be very careful not to invoke any deep copy constructors or
         assignments. A pointer is thus safer.) */

    void rentMovie (Movie *m);
      /* sets the user's currently rented movie to m.
         If the user already has a movie checked out, then it does nothing.
         (So no overwriting the current movie.) */

    void returnMovie ();
      /* returns the movie that the user currently has checked out.
         Does nothing if the user doesn't currently have a movie. */

    Movie* currentMovie ();
      /* returns the user's current checked out movie.
         Returns NULL if the user has no movie checked out. */
    Map<string, int> *returnRatings();

    void addPassword(string pw);
    void setPassword(string pw);
    bool passwordIsCorrect(string pw);
    void addAddress(string addr);
    void addCharge(string card, int price);
    int returnTotalCharge();
    string getPw();
    string getAddr();
    std::vector<std::pair<string, int> > returnCredit();
    void pushCredit(string card, int charge);

  private:
    string user_name;
    string user_id;
    Queue<Movie*> *queue;
    Movie *rented;
    Map<string, int> *ratings;
    string address;
    std::vector<std::pair<string, int> > credit;
    int total_charge;
    string password;

    // you get to decide what goes here.
};

#endif