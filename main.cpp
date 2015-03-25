#include "User.h"
#include "Movie.h"
#include "./GUI/Map.h"
#include "./lib/Set.h"
#include "./lib/EmptyQueueException.h"
#include "./lib/NoSuchElementException.h"
#include "./lib/Queue.h"
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#define PRINT(s) std::cout << s << std::endl

using namespace std;

void readFile(int argc, char * argv[], Map<string, Movie*> &movie, Map<string, User*> &user, Map<string, Set<string>*> &keywords, string &file1, string &file2); //function to read the input files and to store the data
void delPointers(Map<string, Movie*> &movie, Map<string, User*> &user, Map<string, Set<string>*> &keywords); //function to delete allocated memory
void mainMenu(Map<string, Movie*> &movie, Map<string, User*> &user, Map<string, Set<string>*> &keywords, string &file1); 
void startQueue(Map<string, Movie*> &movie, Map<string, User*> &user, Map<string, Set<string>*> &keywords, string &file1);
//queue menu

void loggedIn(Map<string, Movie*> &movie, Map<string, User*> &user, Map<string, Set<string>*> &keywords, string &file1, User* current_user);
//menu shown after logged in

void mainMenu(Map<string, Movie*> &movie, Map<string, User*> &user, Map<string, Set<string>*> &keywords, string &file1);
//main function that interacts with user
void printMovie(string title); //function to print a movie's details
void writeFile(Map<string, Movie*> &movie, Map<string, User*> &user, Map<string, Set<string>*> &keywords, string &file1);
void commandNotValid();

int main(int argc, char * argv[]){
	string file1; //string to store user file (first line of input file name)
	string file2; //string to store movie file (first line of input file name)

	Map<string, Movie*> movie; // a map to store movie pointers with the name of the movie as the key
	Map<string, User*> user; // a map to store user pointers with the name of the movie as the key
	Map<string, Set<string>*> keywords; // a map to store set pointers(which store keywords of a movie) with the name of the movie as the key

	readFile(argc, argv,movie, user, keywords, file1, file2);
	mainMenu(movie, user, keywords, file1);
	writeFile(movie, user, keywords, file1);
	delPointers(movie, user, keywords);
	return 0;
}

void commandNotValid()
{
	cout << "Please enter a valid command!\n";
	cin.clear();
	cin.ignore(256,'\n');
}

void writeFile(Map<string, Movie*> &movie, Map<string, User*> &user, Map<string, Set<string>*> &keywords, string &file1)
{
	ofstream file;
	file.open(file1, ofstream::trunc);
	file.close();
	User *temp_user;
	file.open(file1, ofstream::out | ofstream::app);
	if (file.is_open())
  {
  	for (Map<string, User*>::Iterator si = user.begin(); si != user.end(); ++si)
    {
    	temp_user = (*si).second;
    	file << "BEGIN " << temp_user->getID() << endl;
	    file << "NAME: " << temp_user->getName() << endl;
	    if (temp_user->currentMovie() != NULL)
	    {
	    	file << "MOVIE: " << temp_user->currentMovie()->getTitle() << endl; 
	    }
	    file << "BEGIN QUEUE\n";
	    try
	    {
		    while (temp_user->movieQueue()->size() > 0 )
		    {
		    	file << temp_user->movieQueue()->peekFront()->getTitle();
		    	temp_user->movieQueue()->dequeue();
		    	file << endl;
		    }
		  }
		  catch (EmptyQueueException &e)
		  {
		  	cout << "movie queue is already empty\n";
		  }
	    file << "END QUEUE\n";
	    file << "END\n";
    }
    file.close();
  }
  else 
  {
  	cout << "Unable to open file to write new user info."; 
  	exit(1);
  }
};

void printMovie(Movie *m) 
{
	m->printMovie(); //call function from movie class to print title and keywords
};


void startQueue(Map<string, Movie*> &movie, Map<string, User*> &user, Map<string, Set<string>*> &keywords, string &file1)
{
	string option_string;
	stringstream ss;
};

void loggedIn(Map<string, Movie*> &movie, Map<string, User*> &user, Map<string, Set<string>*> &keywords, string &file1, User* current_user)
{
	bool logout = false; //boolean deciding when to logout
	string option_string;
	int option;
	stringstream ss;
	string name_or_keyword;
	string id_or_title;
	Queue<Movie*> *current_queue = current_user->movieQueue();

	while(!logout) //loop after login
	{
		if ( current_user->currentMovie() != NULL)
		{
			PRINT("\nYour checked out movie is: ");
			cout << endl << current_user->currentMovie()->getTitle() << endl;
		}
		else
		{
			PRINT("\nNo movie checked out");
		}
		PRINT("\n1. Search for a movie by title.");
		PRINT("2. Search for a movie by keyword.");
		PRINT("3. Return the current movie.");
		PRINT("4. View Queue.");
		PRINT("5. Logout");
		getline(cin, option_string);
		ss.str("");
		ss.clear();
		ss << option_string;
		ss >> option;
		if ( (ss.fail()) || (option > 5) || (option < 1) ) //if input is not an integer from 1-3, print error and continue loop
    {
    	cout << "\nPlease enter an integer from 1-5." << endl;
    }
		else if (option == 5) 
 		logout = true;
 		else if (option == 4)
  	{
			if (current_user->movieQueue()->isEmpty())
			{
				cout << endl;
				PRINT("Movie queue is empty!");
			}
			else
			{
				bool endQueue = false;
				try
				{
					while(!endQueue)
					{
						cout << "\nYou currently have " << current_queue->size() << " movies in queue.\n";
						cout << endl << "The movie on top of the queue is:\n"<< current_queue->peekFront()->getTitle() << endl;
						PRINT("\n1. Order movie.");
		  			PRINT("2. Remove movie from queue.");
		  			PRINT("3. Move movie to the back of queue.");
		  			PRINT("4. Return to user menu.");
		  			getline(cin, option_string);
		  			ss.str("");
		  			ss.clear();
		  			ss << option_string;
		  			ss >> option;
		  			if ( (ss.fail()) || (option > 4) || (option < 1) ) //if input is not an integer from 1-4, print error and continue loop
				    {
				    	cout << "\nPlease enter an integer from 1-4." << endl;
				    }
		  			else if (option == 4) 
		     		endQueue = true;
		     		else if(option == 3)
		     		{
		     			current_queue->enqueue( current_queue->peekFront() );
		     			current_queue->dequeue();
		     			PRINT("\nMovie moved to back.");
		     		}
		     		else if(option == 2)
		     		{
		     			current_queue->dequeue();
		     		}
		     		else if(option == 1)
		     		{
		     			if (current_user->currentMovie()==NULL)
		     			{
		     				current_user->rentMovie( current_queue->peekFront() );
		     				PRINT("\nMovie ordered.");
		     				PRINT("Current checked out movie: ");
		     				current_user->currentMovie()->printMovie();
		     				current_queue->dequeue();
		     				break;
		     			}
		     			else
		     			{
		     				PRINT("\nYou currently have a movie ordered: ");
		     				cout << current_user->currentMovie()->getTitle() << endl;
		     				PRINT("\nPlease return movie before you order another movie.");
		     			}
		     		}
		     		else
		     		{
		     			commandNotValid();
		     		}	
		     	}	
	     	}			
				catch(EmptyQueueException &e)
				{
					cout << "Movie queue is empty!\n";
				}
			}
  	}
  	else if (option == 3)
  	{
  		if ( current_user->currentMovie() != NULL) 
  		{
	  		cout << "\nReturning: \n";
	  		( current_user->currentMovie() )->printMovie();
	  		current_user->returnMovie();
	  		PRINT("\nMovie Returned!"); //prompt for movie title search
  		}
  		else
  		{
  			PRINT("\nCannot return movie: no movie checked out"); //return to options loop if no movie is checked out
  		}
  	}
  	else if (option == 1)
  	{
  		PRINT("\nPlease enter a title."); //prompt for movie title search
  		getline(cin, id_or_title);
			if ( movie.containsCase(id_or_title) ) //print movie details if movie exists
			{
				try
  			{
  				cout << endl;
  				printMovie( movie.getCase(id_or_title) );
  				cout << endl;
  				while (true)
	  			{
	  				PRINT("1. Add movie to queue.");
	  				PRINT("2. Return to Menu.");

	  				cin >> option;
	  				if (option == 1) 
	  				{
	  					current_queue->enqueue( movie.getCase(id_or_title));
	  					PRINT("\nMovie added!");
	  					break;
	  				}
	  				else if (option == 2)
	  				{
	  					break;
	  				}
	  				else
	  				{
	  					commandNotValid();
	  				}
		  		}
  			}
  			catch (NoSuchElementException e)
  			{
  				cout << "error after double checking.\n";
  			}
  		}
			else
  		{
  			PRINT("No movie found."); //return to options loop if movie does not exist
			}
  	}
  	else if (option == 3)
  	{
  		if ( current_user->currentMovie() != NULL) 
  		{
	  		current_user->returnMovie();
	  		cout << "\nReturning: \n";
	  		current_user->currentMovie()->printMovie();
	  		PRINT("\nMovie Returned!"); //prompt for movie title search
  		}
  		else
  		{
  			PRINT("\nCannot return movie: no movie checked out"); //return to options loop if no movie is checked out
  		}
  	}
  	else if (option == 2)
  	{
  		PRINT("\nPlease enter keyword(s)."); //prompt for movie keyword search
  		getline(cin, name_or_keyword);
  		if (keywords.containsCase(name_or_keyword))
  		{	
  			int size = (keywords.getCase(name_or_keyword))->size();
  			Set<string>::Iterator si = ( keywords.getCase(name_or_keyword) )->begin();
  			while(size > 1)
  			{
  				cout << endl;
  				cout << "\nThere are " << size << " matches.\n\n";
  				printMovie( movie.getCase( *si ) );
  				while(true)
  				{
	  				PRINT("\n1. Next movie.");
	  				PRINT("2. Add movie to queue.");
	  				PRINT("3. Return to Menu.");
	  				cin >> option;
	  				if (option == 1)
	  				{
							size--;
							++si;
							break;
	  				}
	  				else if (option == 2)
	  				{
	  					current_queue->enqueue( movie.getCase( *si ) );
	  					PRINT("Movie added!");
	  					break;
	  				}
	  				else if (option == 3)
	  				{
	  					size = 0;
	  					break;
	  				}
	  				else 
	  				{
	  					commandNotValid();
  					}
	  			}
	  			cin.clear();
					cin.ignore(256,'\n');
				}
  			if (size == 1)
  			{
	  			while (true)
	  			{
	  				cout << "\nThere is 1 match.\n\n";
	  				printMovie( movie.getCase( *si ));
	  				cout << endl;
	  				PRINT("1. Add movie to queue.");
	  				PRINT("2. Return to Menu.");

	  				cin >> option;
	  				if (option == 1) 
	  				{
	  					current_queue->enqueue( movie.getCase( *si ) );
	  					PRINT("Movie added!");
	  				}
	  				else if (option == 2)
	  				{
	  					break;
	  				}
	  				else
	  				{
	  					commandNotValid();
	  				}
		  		}
		  		cin.clear();
					cin.ignore(256,'\n');
				}
			}
  		else //print error message if no movie is associated to the keyword
  		{
  			PRINT("\nNo match.\n");
  		}
  	}
  }
};

void mainMenu(Map<string, Movie*> &movie, Map<string, User*> &user, Map<string, Set<string>*> &keywords, string &file1)
{
	bool doEnd = false; //boolean deciding when to quit application
	string option_string;
	int option; //int for user input options (e.g. 1,2,3)
	string id_or_title; //string shared by user id input and movie title input
	string name_or_keyword; //string shared by user name input and movie keyword input
	User *u;
	User *current_user;
	stringstream ss;
	ofstream file;
	while (!doEnd)
	{
		// start application
		option = 0;
		option_string = "";
		cout << endl;
		PRINT("1. Log in");
	  PRINT("2. Create a new user");
	  PRINT("3. QUIT");
	  cout << endl;
    getline(cin, option_string); //prompt user for action
    ss.clear();
    ss.str("");
    ss << option_string;
    ss >> option;
    if ( (ss.fail()) || (option > 3) || (option < 1) ) //if input is not an integer from 1-3, print error and continue loop
    {
    	cout << "\nPlease enter an integer from 1-3." << endl;
    }
    else if (option == 3) 
    doEnd = true; //end application as user wants to quit
  	else if (option == 2) //procress to create a new user
  	{
  		id_or_title = ""; //clear strings
  		PRINT("\nPlease enter an ID that you want.");
  		getline(cin, id_or_title);
  		bool space = false;
  		for (unsigned int i = 0; i < id_or_title.length(); i++)
  		{
  			if(id_or_title[i] == ' ') space = true; 
  		}
  		if ( id_or_title == "")
  		{
  			PRINT("\nPlease enter a valid id.");
  		}
  		else if (user.contains(id_or_title)) //check whether id is already in use
  		{
  			PRINT("\nSorry, but the ID is taken.  Try again."); //print error message and continue loop
  		}
  		else if(space)
  		{
  			PRINT("\nPlease do not use space character in your id.  Try again.");
  		}
  		else
  		{
  			name_or_keyword = "";
  			while (true)
  			{
	  			PRINT("\nPlease also enter a name for your user."); //if id is not in use, prompt user name
  				getline(cin, name_or_keyword);
  				if ( name_or_keyword == "")
	  			{
	  				PRINT("\nPlease enter a valid name.");
	  			}
	  			else break;
	  		}
  			u = new User(id_or_title, name_or_keyword); //construct new user with provided id and user name
  			user.add(id_or_title, u);
  		}
  	}
  	else if (option == 1)
  	{
  		PRINT("\nPlease enter your ID."); //prompt login id
  		getline(cin, id_or_title);
  		if (!user.contains(id_or_title)) //print error message if ID does not exist
  		{
  			PRINT("\nSorry, but the ID is incorrect.  Please try again.");
  		}
  		else
  		{
  			try
  			{
  				current_user = user.get(id_or_title);
  			}
  			catch (NoSuchElementException &e)
  			{
  				cout << "There is an error even after double checking, which is strange.\n";
  			}
  			loggedIn(movie, user, keywords, file1, current_user);
  		}
  	}
	}
}

void delPointers(Map<string, Movie*> &movie, Map<string, User*> &user, Map<string, Set<string>*> &keywords)
{
	movie.delHelper();
	user.delHelper();
	keywords.delHelper();
};


void readFile(int argc, char * argv[], Map<string, Movie*> &movie, Map<string, User*> &user, Map<string, Set<string>*> &keywords, string &file1, string &file2)
{
	string line; //string to store temporary getline from file
	ifstream file (argv[1]); //ifstream object to open and read from files
	stringstream ss; //stringstream to append string to names and titles
	string temp_id; //temporary id to constructor new user object
	string temp_user; //temporary user name to construct new user object
	string temp_name; //temporary movie name to construct movie
	string temp_rented;

	string temp_keyword; //temporary keywords to add to movie
	string temp;//temporary string for string appending to various names
	string temp_queue;//string
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

	file.open(file2); //open and read movie file
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
			else if (line.find("END") == 0 ) //
			{
				std::cout << "this is movie\n";
				movie.add(temp_name,m); //add movie* pointer to movie map
				std::cout << movie.getNum() << endl;
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
	file.open(file1); 
	if (file.is_open()) //open and read user file according to first line of main data file
	{	
		User *u; //pointer for constructing new user
		int temp_ratings;
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
					cout << "the movie " << temp_queue << "does not exist!\n";
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
						temp_ratings = 0; //clear temp string
						temp_queue = "";
						ss << line;
						ss >> temp_ratings;
						while (ss >> temp)
						{
							temp_queue = temp_queue + ' '+ temp; //append movie name
						}
						//u->ratings.add( movie.getCase(temp_queue), temp_ratings);
						getline(file, line);
					}
				}
				catch(NoSuchElementException &e)
				{
					cout << "the movie " << temp_queue << "does not exist!\n";
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
				 std::cout << "This is user\n";
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

};
