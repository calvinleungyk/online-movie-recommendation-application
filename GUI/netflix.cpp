#include "netflix.h"
#include <sstream>
#include <fstream>
#include <istream>
#include <string>
#include <iostream>
#include <utility>

using namespace std;

#define FILEDIR "./data/main.txt"

Netflix::Netflix()
{
	readFile();
}

Netflix::~Netflix()
{

}

bool Netflix::containsRatings(string name)
{
	return current_user->returnRatings()->contains(name);
}

void Netflix::addRatings(int a )
{
	current_user->returnRatings()->ratings(current_user->currentMovie()->getTitle(), a);
}

void Netflix::setCurrentUser(string &login)
{
	current_user = user.get(login);
}

User *Netflix::getCurrentUser()
{
	return current_user;
}

string Netflix::printCurrentMovie()
{
	if (current_user->currentMovie() == NULL)
	{
		return "No movie rented";
	}
	else
		return current_user->currentMovie()->getTitle();
}

bool Netflix::checkLoginValid(string loginString)
{
	return user.contains(loginString);
}

bool Netflix::checkTitleValid(string searchString)
{
	if ( movie.getCase(searchString) != NULL)
		return true;
	else return false;
}

Map<string, int>* Netflix::getCurrentRatings()
	{
		return getCurrentUser()->returnRatings();
	}

void Netflix::setIter(Set<string> *s)
{
	iter = s->begin();
}

void Netflix::mapIter(Map<string, int> *s)
{
	mapiter_empty = false;
	mapiter = s->begin();
	if (mapiter == s->end())
	{
		mapiter_empty = true;
	}
}

void Netflix::actorIter(Set<string> *s)
{
	actoriter = s->begin();
}

Set<string>* Netflix::getSet(string keyword)
{
	return keywords.getCase(keyword);
}

Set<string>* Netflix::getActor(string keyword)
{
	return actors.getCase(keyword);
}

bool Netflix::checkKeywordValid(string searchString)
{
	if ( keywords.getCase(searchString) != NULL)
		return true;
	else return false;
}

bool Netflix::checkActorValid(string searchString)
{
	if ( actors.getCase(searchString) != NULL)
		return true;
	else return false;
}

bool Netflix::checkIDValid(string IDString)
{
	return !( user.contains(IDString) );
}

bool Netflix::checkPasswordValid(string IDString, string PWString)
{
	return ( user.get(IDString)->passwordIsCorrect(PWString) );
}

void Netflix::createNewUser(string id, string name, string pw, string addr, string cred)
{
	User *u = new User (id, name);
	u->addPassword(pw);
	u->addAddress(addr);
	u->addCharge(cred, 0);
	user.add(id, u);
}

void Netflix::rentMovies()
{
	current_user->rentMovie( current_user->movieQueue()->peekFront() );
  string temp = ((current_user->returnCredit()).at(0)).first;
  current_user->addCharge(temp, current_user->movieQueue()->peekFront()->getPrice());

	current_user->movieQueue()->dequeue();
}

void Netflix::rentMovie()
{
	current_user->rentMovie( current_user->movieQueue()->peekFront() );
	current_user->movieQueue()->dequeue();
}

void Netflix::deleteMovie()
{
	current_user->movieQueue()->dequeue();
}

void Netflix::moveMovie()
{
	current_user->movieQueue()->enqueue( current_user->movieQueue()->peekFront() );
	current_user->movieQueue()->dequeue();
}

void Netflix::addMovie( string title )
{
	current_user->movieQueue()->enqueue( movie.getCase(title) );
}

void Netflix::saveFile()
{
	ofstream file;
	string temp_queue;
	file.open(file1.c_str(), ofstream::trunc);
	file.close();
	User *temp_user;
	file.open(file1.c_str(), ios::out | ios::app);
	if (file.is_open())
  {
  	for (Map<string, User*>::Iterator si = user.begin(); si != user.end(); ++si)
    {
    	temp_user = (*si).second;
    	file << "BEGIN " << temp_user->getID() << endl;
	    file << "NAME: " << temp_user->getName() << endl;
	    file << "PASSWORD: " << temp_user->getPw() << endl;
	    file << "ADDRESS: " << temp_user->getAddr() << endl;
		  file << "CREDIT: " << (current_user->returnCredit()[0]).first << " " << (current_user->returnCredit()[0]).second << endl;

	    if (temp_user->currentMovie() != NULL)
	    {
	    	file << "MOVIE: " << temp_user->currentMovie()->getTitle() << endl; 
	    }
	    file << "BEGIN QUEUE\n";
	    
		    while (temp_user->movieQueue()->size() > 0 )
		    {
		    	temp_queue = temp_user->movieQueue()->peekFront()->getTitle();
		    	file << temp_queue << endl;
		    	temp_user->movieQueue()->dequeue();
		    	file.flush();
		    }
		  
	    file << "END QUEUE\n";
	    file << "BEGIN RATINGS\n";
	    if (temp_user->returnRatings()->size()!=0)
	    {
	    	for (Map<string, int>::Iterator si = temp_user->returnRatings()->begin(); si != temp_user->returnRatings()->end(); ++si)
		    {
		    	file << (*si).second << " " << (*si).first << endl;
		    }
	    }
	    
	    file << "END RATINGS\n";
	    file << "END\n";
    }
    file.close();
  }
  else 
  {
  	cout << "Unable to open file to write new user info."; 
  	exit(1);
  }
}

void Netflix::returnCurrentMovie()
{
	current_user->returnMovie();
}

void Netflix::logout()
{
	current_user = NULL;
}

string Netflix::printMovie(string title)
{
	stringstream ss;
	string p;
	ss << movie.getCase(title)->getPrice();
	ss >> p;
	return (movie.getCase(title)->getTitle() + " $" + p);
}

string Netflix::printKeywords(string title)
{
	return movie.getCase(title)->returnKeywords();
}

void Netflix::readFile()
{
	string line; //string to store temporary getline from file
	ifstream file (FILEDIR); //ifstream object to open and read from files
	stringstream ss; //stringstream to append string to names and titles
	string temp_id; //temporary id to constructor new user object
	string temp_user; //temporary user name to construct new user object
	string temp_name; //temporary movie name to construct movie
	string temp_rented;

	string temp_keyword; //temporary keywords to add to movie
	string temp;//temporary string for string appending to various names
	string temp_queue;//string
	int temp_ratings;
	bool hasKey=false;

	if (file.is_open()) //first read the main data file for reading user and movie files later
	{	
		getline (file, line);
		file1 = line;
		getline (file, line);
		file2 = line;
		file.close();
	}
	else //if fails to read data file exit program and show error message
	{
		cout << "File error.  Please try again.  Format is ./main filename.txt" << endl;
		exit(1);
	}

	file.open(file2.c_str()); //open and read movie file
	if ( file.is_open() )
	{	
		Movie *m; //pointer for consturcting new movie
		Set<string> *movieKey; //pointer for constructing a set of movie names for a keyword
		while(getline (file, line)) //read lines loop
		{
			ss.clear();
			ss.str(""); //make sure the stream is cleared
			temp = ""; //clear temp strings
			
			if ( line.find("BEGIN") == 0 ) //if line starts with BEGIN, store string into temp_name for movie name
			{
				temp_name = ""; //clear string
				ss << line;
				ss >> temp; //ignoring "BEGIN"
				ss >> temp_name;
				while (ss >> temp){
					temp_name = temp_name + ' '+ temp; //appending movie name
				}
				m = new Movie(temp_name); //constructing new movie object
			}
			else if ( line.find("PRICE") == 0 ) //if line starts with BEGIN, store string into temp_name for movie name
			{
				int price;
				ss << line;
				ss >> temp; //ignoring "PRICE"
				ss >> price;
				m->setPrice(price); //constructing new movie object
			}
			else if ( line.find("KEYWORD") == 0 ) //if line starts with KEYWORD, store string into temp_keyword
			{
				hasKey=true;
				temp_keyword = ""; //clear string
				ss << line;
				ss >> temp; //ignoring "KEYWORD"
				ss >> temp_keyword;
				while (ss >> temp){
					temp_keyword = temp_keyword + ' '+ temp; //appending keyword
				}
				m->addKeyword(temp_keyword); //add keyword into movie
				if ( !keywords.contains(temp_keyword) ) //check if the keyword exists already, if it does, skip constructing new set
				{
					movieKey = new Set<string>; //construct new set for a new keyword
					keywords.add(temp_keyword, movieKey); //add keyword and movie name set to map
				}
				(keywords.get(temp_keyword))->add(temp_name); //add movie name to set in keywords map
				
			}
			else if ( line.find("ACTOR") == 0 ) //if line starts with ACTOR, store string into temp_keyword
			{
				hasKey=true;
				temp_keyword = ""; //clear string
				ss << line;
				ss >> temp; //ignoring "KEYWORD"
				ss >> temp_keyword;
				while (ss >> temp){
					temp_keyword = temp_keyword + ' '+ temp; //appending keyword
				}
				m->addActor(temp_keyword); //add keyword into movie
				if ( !actors.contains(temp_keyword) ) //check if the actor exists already, if it does, skip constructing new set
				{
					movieKey = new Set<string>; //construct new set for a new actor
					actors.add(temp_keyword, movieKey); //add actor and movie name set to map
				}
				(actors.get(temp_keyword))->add(temp_name); //add movie name to set in actors map
				
			}
			else if (line.find("END") == 0 ) //
			{
				movie.add(temp_name,m); //add movie* pointer to movie map
				if (hasKey)
				{
					movieKey->add(temp_name);
					hasKey = false;
				}
				
			}
		}
		file.close(); //close movie file
	}
	else // print error message and quit if file cannot be opened
	{
		cout << "Filename error.  Please try again.  Cannot open movie info file." << endl;
		exit(1);
	}

	file.open(file1.c_str()); 
	if (file.is_open()) //open and read user file according to first line of main data file
	{	
		User *u; //pointer for constructing new user
		while(getline (file, line)) //get string line by line
		{
			ss.clear();
			ss.str(""); //clearing stringstream
			temp = ""; //clear string before every loop starts
			if ( line.find("BEGIN QUEUE") == 0 ) //start loading movies into user queue
			{
				getline(file, line);
				try
				{
					while (line.find("END QUEUE") != 0)
					{
						ss.clear();
						ss.str(""); //clearing stringstream
						temp_queue = ""; //clear temp string
						ss << line;
						ss >> temp_queue;
						while (ss >> temp)
						{
							temp_queue = temp_queue + ' '+ temp; //append movie name
						}
						(u->movieQueue())->enqueue( movie.getCase(temp_queue) );
						getline(file, line);
					}
				}
				catch(NoSuchElementException &e)
				{
					cout << "when loading user file, a movie in user.txt " << temp_queue << "does not exist in movie.txt!\n";
				}
			}
			else if ( line.find("BEGIN RATINGS") == 0 ) //start loading movies into user queue
			{
				getline(file, line);
				try
				{
					while (line.find("END RATINGS") != 0)
					{
						ss.clear();
						ss.str(""); //clearing stringstream
						temp_queue = ""; //clear temp string
						ss << line;
						ss >> temp_ratings;
						while (ss >> temp)
						{
							if (temp_queue == "")
							{
								temp_queue=temp;
							}
							else
							{
								temp_queue = temp_queue + ' '+ temp; //append movie name
							}
						}
						string temp_name1 = movie.getCase(temp_queue)->getTitle();
						( u->returnRatings())->add( temp_name1, temp_ratings );

						getline(file, line);
					}
				}
				catch(NoSuchElementException &e)
				{
					cout << "when loading user file, a movie in user.txt " << temp_queue << " does not exist in movie.txt!\n";
				}
			}
			else if ( line.find("BEGIN") == 0 ) //store string into temp_id if BEGIN is found in the line
			{
				temp_id = ""; //clear temp string
				ss << line;
				ss >> temp; //ignoring "BEGIN" using additional ss >>
				ss >> temp_id;
			}
			else if ( line.find("NAME") == 0 ) //store string into temp_user is NAME is found in the line
			{
				temp_user = ""; //clear temp string
				ss << line;
				ss >> temp; //ignoring "NAME" using additional ss>>
				ss >> temp_user;
				while (ss >> temp)
				{
					temp_user = temp_user + ' '+ temp; //append middle name, last names with space
				}
				u = new User(temp_id, temp_user); //construct new user
			}
			else if ( line.find("ADDRESS") == 0 ) //store string into temp_user if ADDRESS is found in the line
			{
				temp_user = ""; //clear temp string
				ss << line;
				ss >> temp; //ignoring "NAME" using additional ss>>
				ss >> temp_user;
				while (ss >> temp)
				{
					temp_user = temp_user + ' '+ temp; //append address with space
				}
				u->addAddress(temp_user); //construct new address
			}
			else if ( line.find("PASSWORD") == 0 ) //store string into temp_user if PASSWORD is found in the line
			{
				temp_user = ""; //clear temp string
				ss << line;
				ss >> temp; //ignoring "NAME" using additional ss>>
				ss >> temp_user;
				u->setPassword(temp_user); //construct new user
			}
			else if ( line.find("CREDIT") == 0 ) //store string into temp_user is NAME is found in the line
			{
				int charge;
				temp_user = ""; //clear temp string
				ss << line;
				ss >> temp; //ignoring "NAME" using additional ss>>
				ss >> temp_user;
				ss >> charge;
				u->pushCredit(temp_user,charge); //construct new user
			}
			else if ( line.find("MOVIE") == 0 ) //if line starts with MOVIE, store string into temp_rented for movie name
			{
				temp_name = ""; //clear string
				ss << line;
				ss >> temp; //ignoring "MOVIE:"
				ss >> temp_rented;
				while (ss >> temp){
					temp_rented = temp_rented + ' '+ temp; //appending rented movie name
				}
				if( temp_rented != "") //point user's rented pointer to rented movie if temp_rented is not empty
				{
					try
					{
						u->rentMovie( movie.getCase(temp_rented) );
					}
					catch (NoSuchElementException &e) //if data is problematic or movie is not found, cout error message
					{
						cout << "There is no such movie name in database. Please check MOVIE line of user " << temp_id << endl;
					}
				}
			}
			else if (line.find("END") == 0 ) //construct new user when "END" is seen, i.e. enough info is gathered
			{
				user.add(temp_id,u); //add the User* pointer to the user map
			}
		}
		file.close(); //close user file
	}
	else // print error message and quit if file cannot be opened
	{
		cout << "Filename error.  Please try again.  Cannot open user info file." << endl;
		exit(1);
	}
}