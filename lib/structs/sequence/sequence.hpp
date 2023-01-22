#pragma once

template <class T>
class Sequence
{
  public:
    virtual ~Sequence() {}

    // получение
    virtual T& GetFirst() const = 0;
    virtual T& GetLast() const = 0;
    virtual T& Get(int index) const = 0;
    virtual Sequence<T>* Copy() const = 0;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;
    virtual int GetLength() const = 0;
    virtual int IndexOf(const T& item) const = 0;

    //@ INFO
    virtual bool Contains(const T& item) const = 0;
    
    //Операции
    virtual void Append(const T& item) = 0;
    virtual void Prepend(const T& item) = 0;
    virtual void InsertAt(int index, const T& item) = 0;
    virtual void Set(int index, const T& item) = 0;
    virtual void Swap(int index1, int index2) = 0;
    virtual void DoEmpty() = 0;
    virtual Sequence<T>* Concat(Sequence<T>* Seq) = 0;
    
};