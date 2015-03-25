//Mergesort.h

#ifndef MERGESORT_H
#define MERGESORT_H
#include <vector>
#include <iostream>
#include "../lib/Set.h"

using namespace std;

class MergeSort {
  public:
    template <class T>
    static vector <T> sort (vector<T> &a) 
    {
      //sort code here
      if ( a.size() == 1 )
      {
      	return a;
      }
      typename vector<T>::iterator m = a.begin() + (a.size()/2);
      vector<T> a1 (a.begin(), m);
      vector<T> a2 (m, a.end());

      a1 = sort(a1);
      a2 = sort(a2);
      return merge(a1, a2);
    };
  private:
    template <class T>
    static vector <T> merge (vector<T> &a1, vector<T> &a2)
    {
    	vector<T> b;
    	unsigned int first = 0;
    	unsigned int second = 0;
    	while ( (first < a1.size()) && (second < a2.size()) )
    	{
    		if (a1[first] > a2[second])
    		{
    			b.push_back(a2[second]);
    			++second;
    		}	
    		else if (a1[first] < a2[second])
    		{
    			b.push_back(a1[first]);
    			++first;
    		}
    		else
    		{
    			b.push_back(a1[first]);
    			b.push_back(a2[second]);
    			++first;
    			++second;
    		}
    	}

    	while( first < a1.size() )
    	{
    		b.push_back(a1[first]);
    		++first;
    	}

    	while( second < a2.size() )
    	{
    		b.push_back(a2[second]);
    		++second;
    	}
    	return b;
    }

};

#endif