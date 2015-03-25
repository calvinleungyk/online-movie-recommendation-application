#include <iostream>
#include <string>
#include <fstream>
//#include <regex> probably the easiest method to deal with text input, but not supported by GCC 4.8
//if you're curious, try either GCC 4.9 or a differnt C++ compiler.
#include "../header/Map.h"
#include "../header/Set.h"
#include <exception>


int main()
{
	Map<std::string, std::string> m;
		std::cout << "here\n";
	m.add("a","b");
	m.add("c","d");
	m.add("e","f");
	m.add("g","h");
	m.add("i","j");
	std::cout<< m.get("a") << std::endl;
	m.first();
	std::cout<<m.getCurrentKey() << ' '<< m.getCurrentValue() << std::endl;
	m.next();
	std::cout<<m.getCurrentKey() << ' '<< m.getCurrentValue() << std::endl;
	m.first();
	std::cout<<m.getCurrentKey() << ' '<< m.getCurrentValue() << std::endl;
	std::cout<< m.get("a") << std::endl;
	try{
	std::cout<< m.get("b") << std::endl;
}catch(std::exception& e)
{
	std::cout << "hi\n";
}

	return 0;
}