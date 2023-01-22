#pragma once
using namespace std;

#include "../structs/sequence/sequence.hpp"

template <class T>
class ISort
{
  public:
    virtual string GetName() const = 0;
    virtual Sequence<T>* Sort(Sequence<T>* Seq, bool (*cmp)(const T&, const T&)) const = 0;
};