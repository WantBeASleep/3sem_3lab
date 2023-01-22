#pragma once

#include <string>
#include <fstream>

#include "../structs/sequence/sequence.hpp"
#include "../structs/sequence/arraySequence.hpp"

using namespace std;

static Sequence<string>* parse_seq(string FileName)
{
  Sequence<string>* Seq = new ArraySequence<string>();

  string line;
  ifstream in(FileName);
  while (getline(in, line))
  {
    Seq->Append(line);
  }
  in.close();

  return Seq;
}