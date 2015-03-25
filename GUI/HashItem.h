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
      HashItem(){};
      HashItem(keyType key, valueType value) {
            this->key = key;
            this->value = value;
            this->next = NULL;
      }
 
      bool operator== (const HashItem<keyType,valueType> & other)const
      {
        return (this->key == other.getKey() && this->value == other.getValue());
      }

      keyType getKey() const {
            return key;
      }
 
      valueType getValue() const {
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