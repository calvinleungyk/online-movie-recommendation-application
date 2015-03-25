#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <typeinfo>
#include <string>
#include "HashItem.h"
#include <sstream>
#include <algorithm>
#include <iostream>

const int TABLE_SIZE = 128;

template <class FirstType, class SecondType> 
struct Pair {
   FirstType first;
   SecondType second;

   Pair (FirstType first, SecondType second)
      { this->first = first; this->second = second; }
   // we're very nice and give you this piece of difficult code for free :-P
};

class KeyNotFoundException : public std::exception
{ // thrown when the user searches for a non-existing key
public:
    KeyNotFoundException () throw () {}
  ~KeyNotFoundException () throw () {}
};

template<class keyType, class valueType>
class HashTable {
private:
      HashItem<keyType, valueType> **table;
public:

  class Iterator 
  {
    private:
      const HashTable<keyType, valueType> *whoIBelongTo;
      HashItem<keyType, valueType> *curr;
      int count;

      Iterator (const HashTable<keyType, valueType> *m, HashItem<keyType, valueType> *c, int a)
      { 
        whoIBelongTo = m;
        curr = c;
        count = a;
      }
      
           /* add any constructors that you feel will be helpful,
              and choose whether to make them public or private. */
    public:
      friend class HashTable;
      Iterator(){}

      Pair<keyType, valueType> operator* () const
      {
        keyType key = this->curr->getKey();
        valueType value = this->curr->getValue();
        Pair <keyType, valueType> p (key, value);
        return p;
      }
          // return the current (key, value) pair the iterator is at

      HashTable<keyType,valueType>::Iterator operator++ ()
      {
        if (curr == NULL)
        {
          return NULL;
        }
        else if (curr->getNext() == NULL)
        {
          count +=1;
          HashItem<keyType,valueType> **temp = (whoIBelongTo->getTable());
          while (temp[count] == NULL && count < TABLE_SIZE+1)
          {
            count +=1;
          }
          if(count == TABLE_SIZE+1)
             curr = NULL
          else
            curr = temp[count];
        }
        else 
        {
          curr = curr->getNext();
        }
        return *this;
      }
          // advances the iterator (pre-increment)

      HashTable<keyType,valueType>::Iterator operator= (const HashTable<keyType,valueType>::Iterator & other)
      {
        this->whoIBelongTo = other.whoIBelongTo;
        this->curr = other.curr;
        this->count = other.count;
        return *this;
      }
          // assigns the other iterator to this iterator and returns this

      bool operator== (const HashTable<keyType,valueType>::Iterator & other) const
      {
        return ( (curr == other.curr) && (whoIBelongTo == other.whoIBelongTo) && (count == other.count));
      }
          // returns whether this iterator is equal to the other iterator

      bool operator!= (const HashTable<keyType,valueType>::Iterator & other) const
      {
        return ( !this->operator == (other) );
      };
          // returns whether this iterator is not equal to the other iterator


       /* Optionally, if you think that it makes your code easier to write,
          you may also overload other operators: */

       /* You may define a public copy constructor and/or default constructor
          if you think it would be helpful. */
  };

    HashTable<keyType,valueType>::Iterator begin () const
    {
      int a = returnCount();
      return HashTable<keyType, valueType>::Iterator(this, table[a], a);
    };
       // returns an iterator initialized to the first element

     HashTable<keyType,valueType>::Iterator end () const
     {

      return HashTable<keyType, valueType>::Iterator(this, NULL, TABLE_SIZE+1);
     };
       /* returns an iterator initialized past the last element,
          to designate that the end of the map has been reached. */

     int returnCount()
     {
       HashItem<keyType, valueType> *iter;
       for(int i = 0; i < TABLE_SIZE; i++)
       {
         iter = table[i];
         if (iter == NULL)
         {
          continue;
         }
         else
         {
          return i;
         }
       }
     }

      HashTable() {
            table = new HashItem<keyType, valueType>*[TABLE_SIZE];
            for (int i = 0; i < TABLE_SIZE+1; i++)
                  table[i] = NULL;
      }
 
      const valueType get(const keyType key) const
      {
        std::stringstream ss;
        int hash = 0;
        int key_int;
        if ( typeid(keyType) == typeid(std::string) )
        {
          for (int i=0; i<key.length(); i++)
          hash += (int) key[i]; 
          hash = hash%TABLE_SIZE;
        }
        else if ( typeid(keyType) == typeid(int) )
        {
          ss << key;
          ss >> key_int;
          hash = (key_int % TABLE_SIZE);
        }
            if (table[hash] == NULL)
                  throw KeyNotFoundException();
            else {
                  HashItem<keyType, valueType> *item = table[hash];
                  while (item != NULL && item->getKey() != key)
                        item = item->getNext();
                  if (item == NULL)
                        throw KeyNotFoundException();
                  else
                        return item->getValue();
            }
      }
 
      void insert(keyType key, valueType value) {
        std::cout << "This is hash\n";
        int hash = 0;
        std::stringstream ss;
        int key_int;
        if ( typeid(keyType) == typeid(std::string) )
        {
          for (int i=0; i<key.length(); i++)
          hash += (int) key[i]; 
          hash = hash%TABLE_SIZE;
        }
        else if ( typeid(keyType) == typeid(int) )
        {
          ss << key;
          ss >> key_int;
          hash = (key_int % TABLE_SIZE);
        }
            if (table[hash] == NULL)
                  table[hash] = new HashItem<keyType, valueType>(key, value);
            else {
                  HashItem<keyType, valueType> *item = table[hash];
                  while (item->getNext() != NULL)
                        item = item->getNext();
                  if (item->getKey() == key)
                        item->setValue(value);
                  else
                        item->setNext(new HashItem<keyType, valueType>(key, value));
            }
      }

      HashItem<keyType, valueType> **getTable() const
      {
        return table;
      }

      HashTable<keyType, valueType> &operator= (const HashTable<keyType, valueType> &other)
      {
        HashItem <keyType, valueType> **table_other = other.getTable();
        HashItem <keyType, valueType> *iter;
        HashItem <keyType, valueType> *iter_other;
        delHelper();
        for (int i = 0; i < TABLE_SIZE; i++)
        {
          iter = table[i];
          iter_other = table_other[i];
          while(iter_other!=NULL)
          {
            this->insert(iter_other->getKey(), iter_other->getValue());
            iter_other = iter_other->getNext();
          }
        }
        return (*this);
      }

      bool operator== (const HashTable<keyType, valueType> &other)
      {
        HashItem <keyType, valueType> **table_other = other.getTable();
        HashItem <keyType, valueType> *iter;
        HashItem <keyType, valueType> *iter_other;
        for (int i = 0; i < TABLE_SIZE; i++)
        {
          iter = table[i];
          iter_other = table_other[i];
          while(iter!=NULL)
          {
            if ( (iter->getKey() != iter_other->getKey() ) || ( iter->getValue() != iter_other->getValue() ) )
            {
              return false;
            }
            iter = iter->getNext();
            iter_other = iter_other->getNext();
          }
        }
        return true;
      }


      bool operator!= (const HashTable<keyType, valueType> &other)
      {
        return (! (*this == other) );
      };

      void delHelper()
      {
        HashItem <keyType, valueType> *iter;
        HashItem <keyType, valueType> *iter_next;
        for (int i = 0; i < TABLE_SIZE+1; i++)
        {
          iter = table[i];
          if (iter!=NULL)
          {
            while (iter->getNext() != NULL)
            {
              iter_next = iter->getNext();
              delete iter;
              iter = iter_next;
            }
            delete iter;
          }
        }
      }

      void remove(keyType key) {
            int hash = 0;
        std::stringstream ss;
        int key_int;
        if ( typeid(keyType) == typeid(std::string) )
        {
          for (int i=0; i<key.length(); i++)
          hash += (int) key[i]; 
          hash = hash%TABLE_SIZE;
        }
        else if ( typeid(keyType) == typeid(int) )
        {
          ss << key;
          ss >> key_int;
          hash = (key_int % TABLE_SIZE);
        }
            if (table[hash] != NULL) {
                  HashItem<keyType, valueType> *prevItem = NULL;
                  HashItem<keyType, valueType> *item = table[hash];
                  while (item->getNext() != NULL && item->getKey() != key) {
                        prevItem = item;
                        item = item->getNext();
                  }
                  if (item->getKey() == key) {
                        if (prevItem == NULL) {
                             HashItem<keyType, valueType> *nextItem = item->getNext();
                             delete item;
                             table[hash] = nextItem;
                        } else {
                             HashItem<keyType, valueType> *next = item->getNext();
                              delete item;
                             prevItem->setNext(next);
                        }
                  }
            }
      }
 
      bool containsCase(keyType key)
      {
        keyType compare1 = key;
        keyType compare2;
        transform(compare1.begin(), compare1.end(), compare1.begin(),(int (*)(int))tolower);
        HashItem <keyType, valueType> *iter;
        for (int i = 0; i < TABLE_SIZE; i++)
        {
          iter = table[i];
          while (iter != NULL)
          {
            compare2 = iter->getKey();
            transform(compare2.begin(), compare2.end(), compare2.begin(),(int (*)(int))tolower);
            if (compare1.compare(compare2) == 0)
              {return true;} 
            iter = iter->getNext();
          }
        }
        if (iter == NULL)
          {
            return false;
          }
      }

      const valueType getCase(const keyType key) const
      {
        keyType compare1 = key;
        keyType compare2;
        transform(compare1.begin(), compare1.end(), compare1.begin(),(int (*)(int))tolower);
        HashItem <keyType, valueType> *iter;
        for (int i = 0; i < TABLE_SIZE; i++)
        {
          iter = table[i];
          while (iter != NULL)
          {
            compare2 = iter->getKey();
            transform(compare2.begin(), compare2.end(), compare2.begin(),(int (*)(int))tolower);
            if (compare1.compare(compare2) == 0)
              {return iter->getValue();} 
            iter = iter->getNext();
          }
        }
        if (iter == NULL)
          {
            throw KeyNotFoundException();
          }
      }

      ~HashTable() {
            for (int i = 0; i < TABLE_SIZE; i++)
                  if (table[i] != NULL) {
                        HashItem<keyType, valueType> *prevItem = NULL;
                        HashItem<keyType, valueType> *item = table[i];
                        while (item != NULL) {
                             prevItem = item;
                             item = item->getNext();
                             delete prevItem;
                        }
                  }
            delete[] table;
      }
};

#endif