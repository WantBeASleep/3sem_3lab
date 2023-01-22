#pragma once
using namespace std;

#include "imap.hpp"
#include "../trees/binaryTree.hpp"
#include "PairKeyVal.hpp"
#include "../sequence/sequence.hpp"
#include "../sequence/arraySequence.hpp"


template <typename TKey, typename TElement>
class AVLMap : public IMap<TKey, TElement>
{
  private:
    AVLTree<PairKeyVal<TKey, TElement>> data;

  public:
    AVLMap(bool (*cmp)(const PairKeyVal<TKey, TElement>&, const PairKeyVal<TKey, TElement>&)) : data(cmp) {}

    int GetCount() const override
    {
      return data.GetCount();
    }

    int GetCapacity() const override 
    {
      return 0;
    }

    TElement& Get(const TKey& key) const override
    {
      PairKeyVal<TKey, TElement> pair(key);
      return data.Get(pair).element;
    }

    Sequence<TKey>* GetKeys() const override
    {
      Sequence<PairKeyVal<TKey, TElement>>* Pairs = data.GetSequence();
      Sequence<TKey>* Keys = new ArraySequence<TKey>();

      for (int i = 0; i < Pairs->GetLength(); Keys->Append(Pairs->Get(i).key), i++);

      delete Pairs;
      return Keys;
    }

    Sequence<TElement>* GetValues() const override
    {
      Sequence<PairKeyVal<TKey, TElement>>* Pairs = data.GetSequence();
      Sequence<TElement>* Values = new ArraySequence<TElement>();

      for (int i = 0; i < Pairs->GetLength(); Values->Append(Pairs->Get(i).element), i++);

      delete Pairs;
      return Values;
    }

    bool ContainsKey(const TKey& key) const override
    {
      Sequence<TKey>* Keys = GetKeys();
      bool res = Keys->Contains(key);
      delete Keys;
      return res;
    }

    void Add(const TKey& key, const TElement& element) override 
    {
      PairKeyVal<TKey, TElement> pair(key, element);
      data.Add(pair);
    }

    void Remove(const TKey& key) override 
    {
      PairKeyVal<TKey, TElement> pair(key);
      data.Remove(pair);
    }

};