#pragma once

#include <iostream>
#include <fstream>

#include "../structs/sequence/sequence.hpp"

using namespace std;

template <typename stream, typename seq_type>
void PrintSeqAsList(stream& os, Sequence<seq_type>* Seq)
{
  os << "[";
  for (int i = 0; i < Seq->GetLength(); i++)
  {
    os << Seq->Get(i);
    
    if (i == Seq->GetLength() - 1) os << "]";
    else os << ", ";
  }
}