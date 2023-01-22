#pragma once
#include <iostream>
#include <string>
using namespace std;

#include "../sequence/sequence.hpp"
#include "../sequence/arraySequence.hpp"

/*
  wayStats хоть и базируется на классе елемента, но отражает статистику ветки дерева
  в EType методы 
   Better - сравнивает 2 EType
   GetWayStat - возвращает EType с суммироваными статами текущего и входящего EType
   InLimit - чекает на предел сумму текущих статов и нового Etype
   cout для EType
*/

template <typename EType>
class solutionNode
{
  public:
    EType key;
    solutionNode<EType>* prev;
    Sequence<solutionNode<EType>*>* leaves;
    
    EType wayStats;

    solutionNode()
    {
      leaves = new ArraySequence<solutionNode<EType>*>();
    }

    solutionNode(const EType& key, solutionNode<EType>* prev, const EType& wayStats) :  key(key), wayStats(wayStats)
    {
      leaves = new ArraySequence<solutionNode<EType>*>();
      this->prev = prev;
    }

    ~solutionNode()
    {
      delete leaves;
    }
};

template <typename EType>
class solutionTree
{
  private:
    solutionNode<EType>* root;
    solutionNode<EType>* answer;
    Sequence<EType>* data;

    void addLeaves(solutionNode<EType>* ptr, Sequence<EType>* options)
    {
      if (!options->GetLength())
      {
        if (!answer) answer = ptr; // для первого равно
        else if (answer->key.Better(ptr->key)) answer = ptr;
        return;
      }

      for (int i = 0; i < options->GetLength(); i++)
      {
        EType newNodeWayStat = ptr->wayStats.GetWayStat(options->Get(i));
        solutionNode<EType>* newNode = new solutionNode<EType>(options->Get(i), ptr, newNodeWayStat);
                
        Sequence<EType>* newNodeOptions = new ArraySequence<EType>();
        for (int j = 0; j < options->GetLength(); j++)
        {
          if (i != j && newNodeWayStat.InLimit(options->Get(j)))
          {
            newNodeOptions->Append(options->Get(j));
          }
        }
        ptr->leaves->Append(newNode);

        addLeaves(ptr->leaves->GetLast(), newNodeOptions);

        delete newNodeOptions;
      }
      return;
    }

  public:

    solutionTree(Sequence<EType>* data)
    {
      answer = nullptr;
      root = new solutionNode<EType>();
      this->data = data->Copy();

      Sequence<EType>* tmpData = new ArraySequence<EType>();
      for (int i = 0; i < data->GetLength(); i++)
      {
        if (root->key.InLimit(data->Get(i))) tmpData->Append(data->Get(i));
      }
      delete this->data;
      this->data = data;

      addLeaves(root, data);

      cout << "END" << endl;
      solutionNode<EType>* answerWayPtr = answer;
      while (answerWayPtr->prev)
      {
        cout << answerWayPtr->key << endl;
        answerWayPtr = answerWayPtr->prev;
      }
    }

    ~solutionTree()
    {
      // in progress
    }
    
};