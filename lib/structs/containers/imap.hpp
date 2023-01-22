#pragma once
using namespace std;

#include "../sequence/sequence.hpp"

template <typename TKey, typename TElement>
class IMap
{
  public:
    virtual ~IMap() {}

    //@ ПОЛУЧЕНИЕ
    virtual int GetCount() const = 0;
    virtual int GetCapacity() const = 0;
    virtual TElement& Get(const TKey& key) const = 0;
    virtual Sequence<TKey>* GetKeys() const = 0;
    virtual Sequence<TElement>* GetValues() const = 0;
    
    //@ INFO
    virtual bool ContainsKey(const TKey& key) const = 0;

    //@ ОПЕРАЦИИ
    virtual void Add(const TKey& key, const TElement& element) = 0;
    virtual void Remove(const TKey& key) = 0;

};