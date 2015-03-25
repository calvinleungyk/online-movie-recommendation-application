    #include <iostream>
#include <string>
#include <fstream>
//#include <regex> probably the easiest method to deal with text input, but not supported by GCC 4.8
//if you're curious, try either GCC 4.9 or a differnt C++ compiler.
#include "../header/Map.h"
#define PRINT(s) std::cout << s << std::endl

void parseArgs(std::string line, std::string & arg1, std::string & arg2, bool & arg1flag, bool & arg2flag);

int main (int argc, char* argv[])
{
  if (argc > 1)
  {
    std::cerr << "Too many arguments" << std::endl;
    return -1;
  }

  PRINT("Greetings, o illustrious students of C++!");
  PRINT("Be so kind as to enter a command below:");
  PRINT("QUIT               : Makes me go away.");
  PRINT("ADD   [name][email]: Causes me to store the [email] under [name].");
  PRINT("REMOVE[name]       : Causes me to remove the entry under [name].");
  PRINT("QUERY [name]       : Causes me to read out the entry under [name].");
  PRINT("LOAD  [filename]   : Causes me to load ALL the entries under [filename].");
  PRINT("PRINT              : Causes me to print my contents. *Bonus function!*");
  PRINT("COPY               : Causes me to copy another map.");
  std::cout << std::endl;

  Map<std::string, std::string> * m = new Map<std::string, std::string>();

  bool doEnd = false;

  while(!doEnd)
  {
    std::string line;
    getline(std::cin, line);

    std::string arg1, arg2;
    bool arg1flag = false;
    bool arg2flag = false;
    parseArgs(line, arg1, arg2, arg1flag, arg2flag);

    if (line == "QUIT")
    doEnd = true;
    else if (line.find("ADD") == 0)
    {
      if(arg1flag && arg2flag)
      {
        bool result = false;
        m->get(arg1, result);
        if (result)
          PRINT("ERROR: Name already in map.");
        else
          PRINT(arg1 + " stored with value: " + arg2);
        m->add(arg1, arg2);

      }
      else
        PRINT("Malformed arguments.");
    }
    else if (line.find("REMOVE") == 0)
    {
      if(arg1flag)
      {
        bool result = false;
        m->get(arg1, result);
        if (!result)
          PRINT("ERROR: Name was not in map.");
        else
          PRINT(arg1 + " removed.");
        m->remove(arg1);
      }
      else
        PRINT("Malformed argument.");
    }
    else if (line.find("QUERY") == 0)
    {
      if(arg1flag)
      {
        bool result = false;
        m->get(arg1, result);
        if (!result)
          PRINT("ERROR: Name was not in map.");
        else
          PRINT("Key: " + arg1 + " | Value: " + m->get(arg1, result));
      }
      else
        PRINT("Malformed argument.");
    }
    else if (line.find("PRINT") == 0)
    {
      m->printAll();
    }
    else if (line.find("LOAD") == 0)
    {
      if(arg1flag)
      {
        std::string fileLine;
        std::ifstream file;
        file.open(arg1);
        if(!file.is_open())
          std::cerr << "File not openable." << std::endl;
        else
        {
          Map<std::string, std::string> * other = new Map<std::string, std::string>();
          while (getline(file, fileLine))
          {
            std::string fileArg1, fileArg2;
            bool file1flag = false;
            bool file2flag = false;
            parseArgs(fileLine, fileArg1, fileArg2, file1flag, file2flag);//reusing code! checks for bad file!
            if (file1flag && file2flag)
              other->add(fileArg1, fileArg2);
            else
              PRINT("Bad file contents");
          }
          m->merge(*other);
          delete other;
          file.close();
          PRINT("Contents of file \"" + arg1 + "\" were merged with database."); 
        }
      }
      else
        PRINT("Malformed argument.");
    }
    else if (line.find("COPY") == 0)
    {
      Map<std::string, std::string> other(*m);
      other.printAll();
    }
    else
      PRINT("Command not recognized: " + line);
  }
  delete m;
}

void parseArgs(std::string line, std::string & arg1, std::string & arg2, bool & arg1flag, bool & arg2flag)
{
  //argument extraction
  
  int start = line.find("[");
  int end = line.find("]");
  if (start != -1 && end != -1 && end > start)
  {
    arg1 = line.substr(start+1, end-start-1);
    arg1flag = true;
    if ((int)line.size() > end)
    {
      std::string rest = line.substr(end+1, std::string::npos);
      start = rest.find("[");
      end = rest.find("]");
      if (start != -1 && end != -1 && end > start)
      {
        arg2 = rest.substr(start+1, end-start-1);
        arg2flag = true;
      }
    }
  }
}