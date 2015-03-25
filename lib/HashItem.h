//HashItem.h

#ifndef __HASHITEM_H__
#define __HASHITEM_H__
template <class keyType, class valueType>
class HashItem {
private:
      keyType key;
      valueType value;
      HashItem *next;
public:
      HashItem(keyType key, valueType value) {
            this->key = key;
            this->value = value;
            this->next = NULL;
      }
 
      keyType getKey() {
            return key;
      }
 
      valueType getValue() {
            return value;
      }
 
      void setValue(valueType value) {
            this->value = value;
      }
 
      HashItem *getNext() {
            return next;
      }
 
      void setNext(HashItem *next) {
            this->next = next;
      }
};

#endif