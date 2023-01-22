#pragma once
using namespace std;

#include <string>
#include <exception>
#include <stdexcept>


template <class T>
class DynamicArray
{
  private:
    T* data;
    int size;

    void CheckValidIndex(int index) const
    {
      if (index < 0 || index >= size)
        throw out_of_range("IndexOutOfRange(" + to_string(index) + ")");
    }

  public:
    // конструкторы/деструкторы
    DynamicArray()
    {
      size = 0;
      data = nullptr;
    }

    DynamicArray(T* items, int count)
    {
      size = count;
      data = new T[size];
      for (int i = 0; i < size; data[i] = items[i], i++);
    }

    DynamicArray(const DynamicArray<T>& dynArray)
    {
      size = dynArray.size;
      data = new T[size];
      for (int i = 0; i < size; data[i] = dynArray.data[i], i++);
    }

    ~DynamicArray()
    {
      if (data != nullptr) delete [] data;
    }

    // декомпозиция
    T& Get(int index) const
    {
      CheckValidIndex(index);
      return data[index];
    }

    int GetSize() const
    {
      return size;
    }

    // операции

    void Set(int index, const T& value)
    {
      CheckValidIndex(index);
      data[index] = value;
    }

    void Resize(int newSize)
    {
      T* newData = new T[newSize];
      for (int i = 0; i < newSize; i++)
      {
        if (i < size) newData[i] = data[i];
      }
      
      T* tmp = data;
      data = newData;
      size = newSize;

      if (tmp != nullptr) delete [] tmp;
    }

    void DoEmpty()
    {
      delete [] data;
      size = 0;
    }

};