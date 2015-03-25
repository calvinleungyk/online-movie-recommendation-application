#ifndef __SET_H__
#define __SET_H__

#include "Map.h"
#include "./lib/NoSuchElementException.h"
#include "Mergesort.h"
#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Set
{
  public:
    
     class Iterator {
         /* add any constructors that you feel will be helpful,
            and choose whether to make them public or private. */
        private:
          const Set<T> *whoIBelongTo;
          typename Map<T, int>::Iterator curr;
          Iterator(const Set <T> *s, const typename Map<T, int>::Iterator m)
          {
            whoIBelongTo = s;
            curr = m;
          };
          
        public:
          const Set<T> *returnWhoIBelongTo()
          {
            return whoIBelongTo;
          }
          Iterator(){};
          friend class Set<T>;
          T operator* () const
          { 
            return (*curr).first;
          };
              // return the item the iterator is at

          Set<T>::Iterator operator++ ()
          {
            ++(this->curr);
            return *this;
          };
              // advances the iterator (pre-increment)

          Set<T>::Iterator operator= (const Set<T>::Iterator & other)
          {
            this->whoIBelongTo = other.whoIBelongTo;
            this->curr = other.curr;
            return *this;
          };
              // assigns the other iterator to this iterator and returns this
      
          bool operator== (const Set<T>::Iterator & other) const
          {
            return ( (this->curr == other.curr) && (this->whoIBelongTo == other.whoIBelongTo) );
          };
              // returns whether this iterator is equal to the other iterator

          bool operator!= (const Set<T>::Iterator & other) const
          {
            return ( !this->operator==(other) );
          }
              // returns whether this iterator is not equal to the other iterator

           /* Optionally, if you think that it makes your code easier to write,
              you may also overload other operators: */

           /* You may define a public copy constructor and/or default constructor
              if you think it would be helpful. */
     };

     Set<T>::Iterator begin () const
     {

      typename Map<T,int>::Iterator m = storage.begin();
      return Set<T>::Iterator(this, m);
     };
       // returns an iterator initialized to the first element

     Set<T>::Iterator end () const
     {
      typename Map<T,int>::Iterator m = storage.end();
      return Set<T>::Iterator(this, m);
     };
       /* returns an iterator initialized past the last element,
          to designate that the end of the map has been reached. */
    Set (){};  // constructor for a new empty set

    Set (const Set<T> &other)
    {
      storage = other.storage;
    }; //copy constructor that simple uses Map<keyType, valueType>::Map<keyType, valueType> &operator= to copy the storage map from the other Set

    ~Set ()
    {
      /*for (Set<T>::Iterator si = this->begin(); si != this->end(); ++si)
      {
        std::cout << (*si) << std::endl;
      }*/
    }; // destructor

    Set<T> &operator= (const Set<T> &other)
    {
      storage = other.storage;
      return *this;
    }; //operator= that uses Map<keyType, valueType>::Map<keyType, valueType> &operator= to assign other->storage to this->storage

    int size () const
    {
        return this->storage.size();
    }; // returns the number of elements in the set

    void add (const T &item)
    {
        this->storage.add(item, 0);
    }; 
      /* Adds the item to the set.
         If the item is already in the set, it should do nothing.
      */

    void remove (const T &item)
    {
        this->storage.remove(item);
    };
     /* Removes the item from the set.
        If the item was not in the set, it should do nothing. */

    bool contains (T item) const
    {
      return (this->storage.contains(item));
    };
     /* Returns whether the item is in the set. */

    void merge (const Set<T> & other)
    {
        this->storage.merge(other.storage);
    };
     /* Adds all elements of other to this set. 
        However, will not create duplicates, i.e., it ignores elements
        already in the set. */

	 void printAll () 
    {
      for (Set<T>::Iterator si = this->begin(); si != this->end(); ++si)
      {
        cout << *si << endl;
      }
    };

    Set<T> setUnion ( Set<T> & other) const //taken away const for function
    {
      vector<T> a1;
      vector<T> a2;
      Set<T> uni;
      for (Iterator si = this->begin(); si != this->end(); ++si)
      {
        a1.push_back(*si);
      }
      for (Iterator si = other.begin(); si != other.end(); ++si)
      {
        a2.push_back(*si);
      }

      MergeSort::sort(a1);      
      MergeSort::sort(a2);
      unsigned int first = 0;
      unsigned int second = 0;
      while ( (first < a1.size()) && (second < a2.size()) )
      {
        if (a1[first] > a2[second])
        {
          uni.add(a2[second]);
          ++second;
        } 
        else if (a1[first] < a2[second])
        {
          uni.add(a1[first]);
          ++first;
        }
        else
        {
          uni.add(a1[first]);
          ++first;
          ++second;
        }
      }
      while( first < a1.size() )
      {
        uni.add(a1[first]);
        ++first;
      }

      while( second < a2.size() )
      {
       uni.add(a2[second]);
        ++second;
      }
      return uni;
    };
  // Returns the union of this and other. Does not alter this.

    Set<T> setIntersection (const Set<T> & other) const
    {
      vector<T> a1;
      vector<T> a2;
      vector<T> temp;
      Set<T> inter;
      for (Iterator si = this->begin(); si != this->end(); ++si)
      {
        a1.push_back(*si);
      }
      for (Iterator si = other.begin(); si != other.end(); ++si)
      {
        a2.push_back(*si);
      }
      MergeSort::sort(a1);      
      MergeSort::sort(a2);

      unsigned int first = 0;
      unsigned int second = 0;
      unsigned int third = 0;
      while ( (first < a1.size()) && (second < a2.size()) )
      {
        if ( a1.at(first) == a2.at(second) )
        {
          inter.add( a1.at(first) );
          ++first;
          ++second;
        } 
        else if ( a1.at(first) > a2.at(second) )
        {
          temp = a1;
          a1 = a2;
          a2 = temp;
          third = first;
          first = second;
          second = third;
        }
        else
        {
          ++first;
        }
      }
      return inter;
    };

    void delHelper()
    {
      storage.delHelper();
    };

  // Returns the intersection of this and other. Does not alter this.

  private:
    Map<T, int> storage;
     /* You should use a Map (your own implementation) to store your set.
        It is part of your assignment to figure out what types you 
        need for the keyType and valueType. */

     /* If you like, you can add further data fields and private
        helper methods. */
};

#endif
