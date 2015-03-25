#include "User.h"
#include <string>

using namespace std;

  User::User (const string ID, const string name)    
  	{
      user_id = ID;
      user_name = name;
      rented = NULL;
      queue = new Queue<Movie*>;
    };  
  /* constructor that generates a user with the given name and ID.
     While multiple users may have the same name, the ID should be unique
     (e.g., an e-mail address), so that users can log in with it. */

  User::User (const User & other)
  {
  	user_id = other.user_id;
  	user_name = other.user_name;
    queue = other.queue;
    rented = other.rented;
  }; // copy constructor

  User::~User ()
  {
  	delete queue;
  };            // destructor

  string User::getID () const
  {
  	return user_id;
  };    // returns the ID associated with this user

  string User::getName () const
  {
  	return user_name;
  };  // returns the name associated with this user

  Queue<Movie*> *User::movieQueue ()
  {
    return queue;
  } ;
      /* returns a pointer to the user's movie queue.
         This is the easiest way to ensure that you can modify the queue.
         (If you return by reference, that's also possible, but you'd need
         to be very careful not to invoke any deep copy constructors or
         assignments. A pointer is thus safer.) */

  void User::rentMovie (Movie *m)
  {
    if (rented != NULL) return;
    rented = m;
  };
      /* sets the user's currently rented movie to m.
         If the user already has a movie checked out, then it does nothing.
         (So no overwriting the current movie.) */

  void User::returnMovie ()
  {
    rented = NULL;
  };
      /* returns the movie that the user currently has checked out.
         Does nothing if the user doesn't currently have a movie. */

  Movie* User::currentMovie ()
  {
    return rented;
  };
      /* returns the user's current checked out movie.
         Returns NULL if the user has no movie checked out. */