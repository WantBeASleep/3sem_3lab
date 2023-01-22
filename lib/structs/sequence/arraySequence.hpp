#pragma once
using namespace std;

#include "sequence.hpp"
#include "dynamicArray.hpp"

template <class T>
class ArraySequence : public Sequence<T>
{
  private:
    DynamicArray<T> data;

  public:
    ArraySequence() {}

    ArraySequence(T* items, int count) : data(items, count) {}

    ArraySequence(const ArraySequence<T>& arrSeq) : data(arrSeq.data) {}

    ~ArraySequence() {}

    // получение
    T& GetFirst() const override 
    {
      return data.Get(0);
    }

    T& GetLast() const override 
    {
      return data.Get(data.GetSize() - 1);
    }

    T& Get(int index) const override 
    {
      return data.Get(index);
    }

    Sequence<T>* Copy() const override 
    {
      return (Sequence<T>*)(new ArraySequence<T>(*this));
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override
    {
      Sequence<T>* Seq = new ArraySequence<T>();
      for (int i = startIndex; i <= endIndex; Seq->Append(data.Get(i)), i++);
      return Seq;
    }

    int GetLength() const override 
    {
      return data.GetSize();
    }

    int IndexOf(const T& item) const override
    {
      for (int i = 0; i < data.GetSize(); i++)
      {
        if (data.Get(i) == item) return i;
      }
      return -1;
    }

    //@ INFO
    bool Contains(const T& item) const override
    {
      for (int i = 0; i < data.GetSize(); i++)
      {
        if (data.Get(i) == item) return true;
      }
      return false;
    }
    
    //Операции
    void Append(const T& item) override
    {
      data.Resize(data.GetSize() + 1);
      data.Set(data.GetSize() - 1, item);
    }

    void Prepend(const T& item) override
    {
      data.Resize(data.GetSize() + 1);
      for (int i = data.GetSize() - 1; i > 0 ; data.Set(i, data.Get(i - 1)), i--);
      data.Set(0, item);
    }

    void InsertAt(int index, const T& item) override
    {
      data.Resize(data.GetSize() + 1);
      for (int i = data.GetSize() - 1; i > index; data.Set(i, data.Get(i - 1)), i--);
      data.Set(index, item);
    }

    void Set(int index, const T& item) override 
    {
      data.Set(index, item);
    }

    void Swap(int index1, int index2) override
    {
      T tmp = data.Get(index1);
      data.Set(index1, data.Get(index2));
      data.Set(index2, tmp);
    }

    void DoEmpty() override
    {
      data.DoEmpty();
    }

    Sequence<T>* Concat(Sequence<T>* _seq) override
    {
      Sequence<T>* Seq = new ArraySequence<T>(*this);
      for (int i = 0; i < _seq->GetLength(); Seq->Append(_seq->Get(i)), i++);
      return Seq;
    }
};