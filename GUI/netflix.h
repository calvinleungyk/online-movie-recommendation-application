#ifndef NETFLIX_H
#define NETFLIX_H

#include "User.h"
#include "Movie.h"
#include "Map.h"
#include "Set.h"
#include <string>

class Netflix
{

public:
	Netflix();
	~Netflix();
	string printCurrentMovie();
	string printCurrentKeywords();
	string printNameandID();
	string printMovie(string title);
	string printKeywords(string title);

	bool checkLoginValid(string loginString);
	bool checkPasswordValid(string IDString, string PWString);

	bool checkTitleValid(string searchString);
	bool checkKeywordValid(string searchString);
	bool checkIDValid(string IDString);
	bool checkActorValid(string searchString);

	void createNewUser(string id, string name, string pw, string addr, string cred);
	void rentMovie();
	void deleteMovie();
	void moveMovie();
	void addMovie( string title );

	void rentMovies();

	void readFile();

	void saveFile();
	void returnCurrentMovie();
	void logout();
	void addRatings(int a);
	bool containsRatings(string name);
	void mapIter(Map<string, int> *s);
	Map<string, int>* getCurrentRatings();
	Set<string>* getActor(string keyword);

	void setCurrentUser(string &login);
	User *getCurrentUser();
	void setIter(Set<string> *s);
	void actorIter(Set<string> *s);
	Set<string>* getSet(string keyword);
	Set<string>::Iterator iter;
	Set<string>::Iterator actoriter;
	Map<string, int>::Iterator mapiter;
	bool mapiter_empty;
	bool iter_empty;
	bool actoriter_empty;

private:
	Map<string, Movie*> movie; // a map to store movie pointers with the name of the movie as the key
	Map<string, User*> user; // a map to store user pointers with the name of the movie as the key
	Map<string, Set<string>*> keywords; // a map to store set pointers(which store movie names) with keywords as the key
	Map<string, Set<string>*> actors; // a map to store set pointers(which store movie names) with keywords as the key
	User *current_user;
	string file1;
	string file2;
	
};

#endif