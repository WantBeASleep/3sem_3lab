#pragma once
using namespace std;

#include "sequence.hpp"
#include "arraySequence.hpp"

#include "../../sorts/isort.hpp"
#include "../../sorts/avlSort.hpp"

#include <iostream>

template <typename T>
class SortedSequence
{
  private:
    Sequence<T>* data;
    ISort<T>* sort;
    bool (*cmp)(const T&, const T&);

  public:
    SortedSequence(bool (*cmp)(const T&, const T&)) 
    {
      data = new ArraySequence<T>(); 
      sort = new AVLSort<T>(); 
      this->cmp = cmp;
    }

    SortedSequence(Sequence<T>* Seq, bool (*cmp)(const T&, const T&)) 
    {
      this->cmp = cmp; 
      data = sort.Sort(Seq, cmp);
    }

    SortedSequence(T *items, int count, bool (*cmp)(const T&, const T&))
    {
      this->cmp = cmp;
      data = new ArraySequence<T>(items, count);
      Sequence<T> *tmp = data;
      data = sort.Sort(data, cmp);
      delete tmp;
    }
    
    ~SortedSequence() {delete data; delete sort;}

    int GetLength() const {return data->GetLength();}
    
    bool GetIsEmpty() const {return (bool)(data->GetLength());}
    
    T& Get(int index) const {return data->Get(index);}

    T& GetFirst() const {return data->GetFirst();}

    T& GetLast() const {return data->GetLast();}

    int IndexOf(const T& item) const {return data->IndexOf(item);}

    SortedSequence<T> GetSubSequecne(int startIndex, int endIndex) const
    {
      Sequence<T>* Seq = data->GetSubsequence(startIndex, endIndex);
      SortedSequence<T> Res(Seq);
      delete Seq;
      return Res;
    }

    void Add(const T& item)
    {
      data->Append(item);
      Sequence<T>* tmp = data;
      data = sort->Sort(data, cmp);
      delete tmp;
    }

    SortedSequence& operator= (Sequence<T>* Seq)
    {
      delete data;
      data = sort->Sort(Seq, cmp);
      return *this;
    }

};