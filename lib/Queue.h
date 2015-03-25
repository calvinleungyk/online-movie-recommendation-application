#ifndef QUEUE_H
#define QUEUE_H
#include "EmptyQueueException.h"

template<class L>
struct Item{
  L value;
  Item *next, *prev;

  Item (const L &val)
        { value = val;}
};

template <class L>
class Queue {
  public:
    Queue()
    {
      num = 0;
      head = NULL;
      tail = NULL;
    }; //initialize pointers and num value to 0
    ~Queue()
    {
      while(this->num != 0)
      {
        dequeue();
      }
    }; //delete all pointers

    void enqueue (const L & item)
    {
      Item<L> *it = new Item<L> (item);
      if (isEmpty())
      {
        head = it;
        tail = it;
        tail->next = NULL;
        head->prev = NULL;
        this->num++;
        return;
      }
      tail->next = it;
      it->prev = tail;
      tail = it;
      this->num++;
    };
      /* adds the item to the end of the queue.
         The same item may be added many times. */

    void dequeue ()
    {
      if (isEmpty())
      {
        throw EmptyQueueException();
      }
      else if(this->num == 1)
      {
        delete head;
        head = NULL;
        tail = NULL;
        this->num--;
      }
      else
      {
        head = head->next;
        delete head->prev;
        head->prev = NULL;
        this->num--;
      }
    }; 
      /* removes the front element of the queue. 
         Throws an EmptyQueueException when called on an empty queue.
         EmptyQueueException should inherit from std::exception. */

    const L & peekFront ()
    {
      if (Queue::isEmpty())
      {
        throw EmptyQueueException();
        return NULL; //just to get rid of compiler warning
      }
      else
      {
        return head->value;
      }
    };
      /* returns the front element of the queue. 
         Throws an EmptyQueueException when called on an empty queue.
         EmptyQueueException should inherit from std::exception. */

    bool isEmpty ()
    {
      return (this->num == 0);
    };
      /* returns whether the queue is empty. */
    


    int size()
    {
      return num;
    }; 
    //return size of the queue

    Queue<L>& operator= (const Queue<L> &other)
    {
      Item<L> *iter = this->tail;
      Item<L> *iter_o = other.tail;
      while( (iter_o->prev != NULL) && (iter->prev != NULL) )
      {
        iter->val = other.value;
        iter = iter->prev;
        iter_o = iter_o->prev;
        this->num++;
      }
      iter->val = other.value;
      this->num++;
      if (iter->prev == NULL)
      {
        while(iter_o != NULL)
        {
          this->enqueue( *iter_o );
          iter_o = iter_o->prev;
        }
      }
      if (iter_o->prev == NULL)
      {
        while(this->num > other.num)
        {
          this->dequeue();
        }
      }
    };
  private:
    Item<L> *head, *tail;
    int num;
};

#endif