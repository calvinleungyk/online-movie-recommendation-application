#ifndef __MAP_H__
#define __MAP_H__
#include "NoSuchElementException.h"
#include <iostream>
#include <algorithm>
#include <string>

template <class FirstType, class SecondType> 
struct Pair {
   FirstType first;
   SecondType second;

   Pair (FirstType first, SecondType second)
      { this->first = first; this->second = second; }
   // we're very nice and give you this piece of difficult code for free :-P
};

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
      MapItem<keyType, valueType> *curr;

      Iterator (const Map<keyType, valueType> *m, MapItem<keyType, valueType> *c)
      { 
        whoIBelongTo = m;
        curr = c;
      }
      
           /* add any constructors that you feel will be helpful,
              and choose whether to make them public or private. */
    public:
      friend class Map;
      Iterator(){}

      Pair<keyType, valueType> operator* () const
      {
        keyType key = this->curr->key;
        valueType value = this->curr->value;
        Pair <keyType, valueType> p (key, value);
        return p;
      }
          // return the current (key, value) pair the iterator is at

      Map<keyType,valueType>::Iterator operator++ ()
      {
        curr = curr->next;
        return *this;
      }
          // advances the iterator (pre-increment)

      Map<keyType,valueType>::Iterator operator++ (int dummy)
      {
        MapItem<keyType, valueType> *temp;
        temp = curr;
        curr = curr->next;
        return *temp;
      }
          // advances the iterator (post-increment)

      Map<keyType,valueType>::Iterator operator= (const Map<keyType,valueType>::Iterator & other)
      {
        this->whoIBelongTo = other.whoIBelongTo;
        this->curr = other.curr;
        return *this;
      }
          // assigns the other iterator to this iterator and returns this

      bool operator== (const Map<keyType,valueType>::Iterator & other) const
      {
        return ( (curr == other.curr) && (whoIBelongTo == other.whoIBelongTo) );
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
      return Map<keyType, valueType>::Iterator(this, head);
    };
       // returns an iterator initialized to the first element

     Map<keyType,valueType>::Iterator end () const
     {
      return Map<keyType, valueType>::Iterator(this, NULL);
     };
       /* returns an iterator initialized past the last element,
          to designate that the end of the map has been reached. */

    Map ()
    {
      num = 0;
      head = NULL;
      tail = NULL;
    };  // constructor for a new empty map

    Map (const Map<keyType, valueType> &other) //copy constructor
    {
      num = 0;
      head = NULL;
      tail = NULL;
      MapItem<keyType, valueType> *other_iter = other.head;
      while( this->num != other.num )
      {
        this->add(other_iter->key, other_iter->value);
        other_iter = other_iter->next;
      }
    };

    Map<keyType, valueType> &operator= (const Map<keyType, valueType> &other)
    {
      MapItem<keyType, valueType> *iter = this->head;
      MapItem<keyType, valueType> *iter_o = other.head;
      if (iter_o == NULL)
      {
        iter = this->tail;
        this->num = 0;
        while(iter->prev != NULL)
        {
          iter = iter->prev;
          delete iter->next;
        }
        delete iter;
        head = NULL;
        tail = NULL;
        return *this;
      }
      if (iter == NULL)
      {
        this->add(iter_o->key, iter_o->value);
        iter = this->head;
      }
      while( (iter->next != NULL) && (iter_o->next != NULL) )
      {
        iter->key = iter_o->key;
        iter->value = iter_o->value;
        iter = iter->next;
        iter_o = iter_o->next;
      }
      if ( (iter->next == NULL) && (iter_o->next !=NULL) )
      {
        iter->key = iter_o->key;
        iter->value = iter_o->value;
        while (iter_o->next != NULL)
        {
           this->add(iter_o->next->key, iter_o->next->value);
           iter = iter->next;
           iter_o = iter_o->next;
        }
      }
      else if ( (iter->next != NULL) && (iter_o->next ==NULL) )
      {
        iter = this->tail;
        while(this->num != other.num)
        {
          iter = iter->prev;
          delete iter->next;
          this->num--;
        }
      }
      return *this; 
    };

    bool operator== (const Map<keyType, valueType> &other)
    {
      if (this->num != other.num) return false;
      else
      {
        MapItem<keyType, valueType> *iter = this->head;
        while (iter != NULL)
        {
          if (this->get(iter->key) != other.get(iter->key)) return false;
          iter = iter->next;
        }
      }
      return true; 
    };

    bool operator!= (const Map<keyType, valueType> &other)
    {
      return (! (*this == other) );
    };

    ~Map ()
    {
      for (Iterator si = this->begin(); si != this->end(); ++si)
      {
        if (si == this->begin())
        {
          continue;
        }
        delete si.curr->prev;
      }
      delete tail;
    }; // destructor

    void delHelper()
    {
      for (Iterator si = this->begin(); si != this->end(); ++si)
      {
        if (si == this->begin())
        {
          continue;
        }
        delete si.curr->prev->value;
      }
      delete tail->value;
    };

    valueType &returnHead()
    {
      return head->value;
    };

    int size () const
    {
      return this->num;
    }; // returns the number of key-value pairs

    void ratings(const keyType &key, const valueType &value)
    {
      try
      {
        this->get(key);
        remove(key);
        add(key,value);
        return;
      }
      catch (NoSuchElementException& e)
      {
        add(key,value);
      }
    }

    void credit(const keyType &key, const valueType &value)
    {
      try
      {
        valueType T = this->get(key);
        remove(key);
        add(key,T + value);
      }
      catch (NoSuchElementException& e)
      {
        add(key,value);
      }
    }

    void add (const keyType &key, const valueType &value)
    {
      try
      {
        this->get(key);
        return;
      }
      catch (NoSuchElementException& e)
      {
        MapItem<keyType, valueType> *item = new MapItem<keyType, valueType>;
        item->key = key;
        item->value = value;
        //code for adding first item
        if(head == NULL)
        {
          head = item;
          tail = item;
          head->next = NULL;
          tail->prev = NULL;
          this->num++;
          return;
        };
        tail->next = item;
        item->prev = tail;
        tail = item;
        
        this->num++;
      }
    }; 
      /* Adds a new association between the given key and the given value.If the key already has an association, it should do nothing.
      */
    void remove (const keyType &key)
    {
      this->get(key);
      MapItem<keyType, valueType> *iter = head;
      while(iter->key != key)
      {
        iter = iter->next;
      }
      if(iter == head)
      {
        head = iter->next;
        iter->next->prev = NULL;
        delete iter;
        this->num--;
        return;
      }
      iter->prev->next = iter->next;
      if(iter == tail)
      {
        tail = iter->prev;
      }
      else
      {
        iter->next->prev = iter->prev;
      }
      delete iter;
      this->num--;
    };

     /* Removes the association for the given key.
        If the key has no association, it should do nothing. */
    const valueType &get (const keyType key) const
    {
      MapItem<keyType, valueType> *iter = head;
      while ( (iter != NULL) && (iter->key != key) )
      {
        iter = iter->next;
      }
      if (iter == NULL)
      {
        throw NoSuchElementException();
      }
      return iter->value;
    };

    const valueType &getCase (const keyType key) const
    {
      MapItem<keyType, valueType> *iter = head;
      keyType compare1 = key;
      keyType compare2;
      transform(compare1.begin(), compare1.end(), compare1.begin(),(int (*)(int))tolower);
      while ( (iter != NULL) )
      {
        compare2 = iter->key;
        transform(compare2.begin(), compare2.end(), compare2.begin(),(int (*)(int))tolower);
        if (compare1.compare(compare2) == 0) break;
        iter = iter->next;
      }
      if (iter == NULL)
      {
        throw NoSuchElementException();
      }
      return iter->value;
    };
     /* Returns the value associated with the given key.
        If the key existed in the map, success should be set to true.
        If the key has no association, it should set success to false. */
    void merge (const Map<keyType, valueType> & other)
    {
      MapItem<keyType, valueType> *iter = other.head;
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
      keyType compare1 = key;
      keyType compare2;
      transform(compare1.begin(), compare1.end(), compare1.begin(),(int (*)(int))tolower);
      MapItem<keyType, valueType> *iter = head;
      while ( (iter != NULL) )
      {
        compare2 = iter->key;
        transform(compare2.begin(), compare2.end(), compare2.begin(),(int (*)(int))tolower);
        if (compare1.compare(compare2) == 0) break;
        iter = iter->next;
      }
      if (iter == NULL)
      {
        return false;
      }
      return true;
    };

    bool contains(const keyType key)
    { 
      MapItem<keyType, valueType> *iter = head;
      while ( (iter != NULL) && (iter->key != key) )
      {
        iter = iter->next;
      }
      if (iter == NULL)
      {
        return false;
      }
      return true;
    };
    
  private:
     /* The head and tail of the linked list you're using to store
        all the associations. */
    MapItem <keyType, valueType> *head;
    MapItem <keyType, valueType> *tail, *trav;
    int num;
    

     /* If you like, you can add further data fields and private
        helper methods. */
};


#endif