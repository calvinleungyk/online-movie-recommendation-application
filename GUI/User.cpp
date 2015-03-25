#include "User.h"
#include "md5.cpp"
#include "Map.h"
#include <string>

using namespace std;

  User::User (const string ID, const string name)    
  	{
      user_id = ID;
      user_name = name;
      rented = NULL;
      queue = new Queue<Movie*>;
      ratings = new Map<string, int>;
      total_charge = 0;
    };  
  /* constructor that generates a user with the given name and ID.
     While multiple users may have the same name, the ID should be unique
     (e.g., an e-mail address), so that users can log in with it. */

  User::User (const User & other)
  {
  	user_id = other.user_id;
  	user_name = other.user_name;
    queue = other.queue;
    ratings = other.ratings;
    rented = other.rented;
  }; // copy constructor

  User::~User ()
  {
  	delete queue;
    delete ratings;
  };            // destructor

  string User::getPw()
  {
    return password;
  }
  string User::getAddr()
  {
    return address;
  }
  std::vector<std::pair<string, int> > User::returnCredit()
  {
    return credit;
  }

  void User::addCharge(string card, int price)
  {
    int temp2 = (credit[0]).second;
    temp2 = temp2 + price;
    credit.pop_back();
    credit.push_back( std::make_pair(card, temp2) );
    total_charge = total_charge + price;
  }

  void User::addAddress(string addr)
  {
    address = addr;
  }

  void User::addPassword(string pw)
  {
    password = md5(pw);
  }

  void User::setPassword(string pw)
  {
    password = pw;
  }

  bool User::passwordIsCorrect(string pw)
  {
    return ( password == md5(pw) );
  }

  string User::getID () const
  {
  	return user_id;
  };    // returns the ID associated with this user

  string User::getName () const
  {
  	return user_name;
  };  // returns the name associated with this user

  Map<string, int> *User::returnRatings()
    {
      return ratings;
    }

  int User::returnTotalCharge()
  {
    return total_charge;
  }

  Queue<Movie*> *User::movieQueue ()
  {
    return queue;
  } ;
      /* returns a pointer to the user's movie queue.
         This is the easiest way to ensure that you can modify the queue.
         (If you return by reference, that's also possible, but you'd need
         to be very careful not to invoke any deep copy constructors or
         assignments. A pointer is thus safer.) */

  void User::pushCredit(string card, int charge)
  {
    credit.push_back(std::make_pair(card, charge));
  }

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