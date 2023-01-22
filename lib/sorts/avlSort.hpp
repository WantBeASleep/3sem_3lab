#pragma once
using namespace std;

#include <iostream>
#include <string>
#include "../structs/sequence/sequence.hpp"
#include "../structs/trees/binaryTree.hpp"
#include "isort.hpp"


template <class T>
class AVLSort : public ISort<T>
{
  private:
    string name = "Binary AVL Sort";

  public:
    string GetName() const override {return name;}

    Sequence<T>* Sort(Sequence<T>* _Seq, bool (*cmp)(const T&, const T&)) const override
    {
      AVLTree<T> tree(cmp);
      for (int i = 0; i < _Seq->GetLength(); tree.Add(_Seq->Get(i)), i++);
      
      Sequence<T>* Res = tree.GetSequence();
      return Res;
    }
};