#ifndef __MAP_H__
#define __MAP_H__
#include "./lib/NoSuchElementException.h"
#include "HashTable.h"
#include <iostream>
#include <algorithm>
#include <string>

template <class keyType, class valueType>
struct MapItem
{
  keyType key;
  valueType value;
  MapItem<keyType, valueType> *prev = NULL, *next = NULL;
};


template <class keyType, class valueType>
class Map
{
  public:
    
  class Iterator 
  {
    private:
      const Map<keyType, valueType> *whoIBelongTo;
      typename HashTable<keyType, valueType>::Iterator curr;

      Iterator (const Map<keyType, valueType> *m, const typename HashTable<keyType, valueType>::Iterator h)
      { 
        whoIBelongTo = m;
        curr = h;
      }
      
           /* add any constructors that you feel will be helpful,
              and choose whether to make them public or private. */
    public:
      friend class Map;
      Iterator(){}

      const Map<keyType, valueType> *returnWhoIBelongTo()
      {
        return whoIBelongTo;
      }

      Pair<keyType, valueType> operator* () const
      {
        Pair <keyType, valueType> p ((*curr).first, (*curr).second);
        return p;
      }
          // return the current (key, value) pair the iterator is at

      Map<keyType,valueType>::Iterator operator++ ()
      {
        ++(this->curr);
        return *this;
      }
          // advances the iterator (pre-increment)

      Map<keyType,valueType>::Iterator operator= (const Map<keyType,valueType>::Iterator & other)
      {
        this->whoIBelongTo = other.whoIBelongTo;
        this->curr = other.curr;
        return *this;
      }
          // assigns the other iterator to this iterator and returns this

      bool operator== (const Map<keyType,valueType>::Iterator & other) const
      {
        return ( (this->curr == other.curr) && (whoIBelongTo == other.whoIBelongTo) );
      }
          // returns whether this iterator is equal to the other iterator

      bool operator!= (const Map<keyType,valueType>::Iterator & other) const
      {
        return ( !this->operator == (other) );
      };
          // returns whether this iterator is not equal to the other iterator


       /* Optionally, if you think that it makes your code easier to write,
          you may also overload other operators: */

       /* You may define a public copy constructor and/or default constructor
          if you think it would be helpful. */
  };

    Map<keyType,valueType>::Iterator begin () const
    {
      typename HashTable<keyType,valueType>::Iterator m = table.begin();
      return Map<keyType, valueType>::Iterator(this, m);
    };
       // returns an iterator initialized to the first element

     Map<keyType,valueType>::Iterator end () const
     {
      typename HashTable<keyType,valueType>::Iterator m = table.end();
      return Map<keyType, valueType>::Iterator(this, m);
     };
       /* returns an iterator initialized past the last element,
          to designate that the end of the map has been reached. */

    Map ()
    {
      num = 0;
    };  // constructor for a new empty map

    int getNum()
    {
      return num;
    }

    Map (const Map<keyType, valueType> &other) //copy constructor
    {
      num = other.getNum;
      table = other.getTable();
    };

    Map<keyType, valueType> &operator= (const Map<keyType, valueType> &other)
    {
      table = other.getTable();
      return *this; 
    };

    HashTable <keyType, valueType> getTable() const
    {
      return table;
    }
    
    bool operator== (const Map<keyType, valueType> &other)
    {
      if (this->num != other.num) return false;
      else
      {
        return ( table == other.getTable() );
      }
    };

    bool operator!= (const Map<keyType, valueType> &other)
    {
      return (! (*this == other) );
    };

    ~Map ()
    {
      //this->delHelper();
    }; // destructor

    void delHelper()
    {
      table.delHelper();
    };

    int size () const
    {
      return this->num;
    }; // returns the number of key-value pairs
    void add (const keyType &key, const valueType &value)
    {
      try
      {
        this->get(key);
        return;
      }
      catch (NoSuchElementException& e)
      {
        table.insert(key, value);
        this->num++;
      }
    }; 
      /* Adds a new association between the given key and the given value.If the key already has an association, it should do nothing.
      */
    void remove (const keyType &key)
    {
      table.remove(key);
      this->num--;
    };

     /* Removes the association for the given key.
        If the key has no association, it should do nothing. */
    const valueType get (const keyType key) const
    {
      valueType a;
      try 
      {
        a = table.get(key);
      }
      catch (KeyNotFoundException &e)
      {
        throw NoSuchElementException();
      }
      return a;
    };

    const valueType getCase (const keyType key) const
    {
      valueType a;
      try
      {
        a = table.getCase(key);
      }
      catch (KeyNotFoundException &e)
      {
        throw NoSuchElementException();
      }
      return a;
    };
     /* Returns the value associated with the given key.
        If the key existed in the map, success should be set to true.
        If the key has no association, it should set success to false. */

    void ratings(const keyType &key, const valueType &value)
    {
      try
      {
        table.get(key);
        remove(key);
        add(key, value);
      }
      catch (KeyNotFoundException &e)
      {
        add(key, value);
      }
    }

    void merge (const Map<keyType, valueType> & other)
    {
      HashItem<keyType, valueType> *iter = other.head;
      while(iter->next != NULL)
      {
        this->add(iter->key, iter->value);
        iter = iter->next;
      }
      this->add(iter->key,iter->value);
    };
     /* Adds all the key-value associations of other to the current map.
        If both maps (this and other) contain an association for the same
        key, then the one of this is used. */
    void printAll () const
    {
      if (this->num == 0) return;
      MapItem<keyType, valueType> *iter = this->head;
      std::cout << "Current contents:" << std::endl;
      while (iter != NULL)
      { 
        std::cout << iter->key << " : " << iter->value <<std::endl;
        iter = iter->next;
      }
    };

    bool containsCase(const keyType key)
    {
      return table.containsCase(key);
    };

    bool contains(const keyType key)
    { 
      try
      {
        table.get(key);
        return true;
      }
      catch (KeyNotFoundException &e)
      {
        return false;
      }
    };
    
  private:
     /* The head and tail of the linked list you're using to store
        all the associations. */
    HashTable <keyType, valueType> table;
    int num;
    

     /* If you like, you can add further data fields and private
        helper methods. */
};


#endif