#pragma once
using namespace std;

template <typename TKey, typename TElement>
class PairKeyVal
{
  public:
    TKey key;
    TElement element;

    PairKeyVal() {}

    PairKeyVal(const TKey& key) 
    {
      this->key = key;
    }

    PairKeyVal(const TKey& key, const TElement& element) 
    {
      this->key = key; 
      this->element = element;
    }

    PairKeyVal(const PairKeyVal& obj) 
    {
      key = obj.key; 
      element = obj.element;
    }

    PairKeyVal& operator= (const PairKeyVal<TKey, TElement>& obj) 
    {
      key = obj.key; 
      element = obj.element; 
      return *this;
    }

    ~PairKeyVal() {}

    bool operator== (const PairKeyVal<TKey, TElement>& obj) const {return this->key == obj.key;}
    // bool operator> (const PairKeyVal<TKey, TElement>& obj) const {return this->key > obj.key;}
    // bool operator< (const PairKeyVal<TKey, TElement>& obj) const {return this->key < obj.key;}
};
