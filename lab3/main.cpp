#include <iostream>
using namespace std;
#include "../lib/structs/trees/graph.hpp"
#include "../lib/structs/containers/PairKeyVal.hpp"
#include "../lib/funcs/menu_viewer.hpp"

#define INF 999

class VertexCore
{
  public:
    int mass = 0;
  
  VertexCore& operator= (const VertexCore& val1)
  {
    mass = val1.mass;
    return *this;
  }
};

class EdgeCore
{
  public:
    int mass;
  EdgeCore(){mass = 0;}
  EdgeCore(int mass)
  {
    this->mass = mass;
  }

  EdgeCore& operator= (const EdgeCore& val1)
  {
    mass = val1.mass;
    return *this;
  }

  bool operator== (const EdgeCore& val1)
  {
    if (mass == val1.mass) return true;
    else return false;
  }
};

EdgeCore operator+ (const EdgeCore& val1, const EdgeCore& val2)
{
  EdgeCore res(val1.mass + val2.mass);
  return res;
}

static bool comparatorTree(const PairKeyVal<Vertex<VertexCore>, LinkedList<Edge<EdgeCore>>>& val1, const PairKeyVal<Vertex<VertexCore>, LinkedList<Edge<EdgeCore>>>& val2)
{
  if (val1.key.GetVertexId() < val2.key.GetVertexId())
  {
    return true;
  } else 
  {
    return false;
  }
}

void outList(const LinkedList<Edge<EdgeCore>>& list);
void outGraph(const Graph<VertexCore, EdgeCore>& graph1);
void outSeq(Sequence<int>* list);
void Distra(const Graph<VertexCore, EdgeCore>& graph1, int startVertexId, int endVertexId);
void outSeqSeq(Sequence<Sequence<int>*>* list);
void SetBaseGraph(Graph<VertexCore, EdgeCore>& graph1);
void SetComponentGraph(Graph<VertexCore, EdgeCore>& graph1);
void GetDijkstra(Graph<VertexCore, EdgeCore>& graph1, int startVertexId, int endVertexId, EdgeCore& infEdgeCore, EdgeCore& nullEdgeCore);
void GetComponents(Graph<VertexCore, EdgeCore>& graph1);

static bool comparatorEdgeCore(const EdgeCore& val1, const EdgeCore& val2)
{
  if (val1.mass < val2.mass) return true;
  else return false;
}

int main()
{
  Graph<VertexCore, EdgeCore> graph1(comparatorTree);
  graph1.SetEdgeCoreCmp(comparatorEdgeCore);
  EdgeCore nullEdgeCore(0);
  EdgeCore infEdgeCore(999);

  string opt_values[4] = {"Set Base Graph", "Set Component Graph", "Get way", "Get Component"};
  Sequence<string>* Options = new ArraySequence<string>(opt_values, 4);

  int res = 1;
  while (res)
  {
    res = ViewAnsMenu(Options);
    switch (res)
    {
      case 1:
      {
        SetBaseGraph(graph1);
        outGraph(graph1);
        break;
      }
      case 2:
      {
        SetComponentGraph(graph1);
        outGraph(graph1);
        break;
      }
      case 3:
      {
        int startVertexId, endVertexId;
        cin >> startVertexId;
        cin >> endVertexId;
        GetDijkstra(graph1, startVertexId, endVertexId, infEdgeCore, nullEdgeCore);
        break;
      }
      case 4:
      {
        GetComponents(graph1);
        break;
      }
    }
  }
  delete Options;
  return 0;
} 

void GetComponents(Graph<VertexCore, EdgeCore>& graph1)
{
  Sequence<Sequence<int>*>* components = graph1.GetConnectedComponents();
  outSeqSeq(components);
  cout << endl;
  for (int i = 0; i < components->GetLength(); i++)
  {
    delete components->Get(i);
  }
  delete components;
}

void GetDijkstra(Graph<VertexCore, EdgeCore>& graph1, int startVertexId, int endVertexId, EdgeCore& infEdgeCore, EdgeCore& nullEdgeCore)
{
  DijkstraWay<EdgeCore>* result = graph1.Dijkstra(startVertexId, endVertexId, infEdgeCore, nullEdgeCore);
  cout << "Вес пути: " << result->wayStats.mass << endl << "Путь: ";
  outSeq(result->vertexesIdsWay);
  cout << endl; 
  delete result->vertexesIdsWay;
  delete result; 
}

void outGraph(const Graph<VertexCore, EdgeCore>& graph1)
{
  Sequence<int>* vertexIds = graph1.GetVertexIds();
  for (int i = 0; i < vertexIds->GetLength(); i++)
  {
    cout << "[" << vertexIds->Get(i) << "]";
    cout << " --> ";
    outList(graph1.GetEdgeList(vertexIds->Get(i)));
    cout << endl;
  }
  delete vertexIds;
}

void outList(const LinkedList<Edge<EdgeCore>>& list)
{
  if (list.GetLength() == 0) 
  {
    cout << "[empty]";
    return;
  }
  cout << "[";
  for (int i = 0; i < list.GetLength() - 1 ; cout << "(" << list.Get(i).GetEdgeStartVertexId() << ":" << list.Get(i).GetEdgeEndVertexId() << ":" << list.Get(i).GetEdgeData().mass << ")" << ", ", i++);
  cout << "(" << list.Get(list.GetLength()-1).GetEdgeStartVertexId() << ":" << list.Get(list.GetLength()-1).GetEdgeEndVertexId() << ":" << list.Get(list.GetLength()-1).GetEdgeData().mass << ")" << "]";
}

void outSeq(Sequence<int>* list)
{
  if (list->GetLength() == 0) 
  {
    cout << "[empty]";
    return;
  }
  cout << "[";
  for (int i = 0; i < list->GetLength() - 1 ; cout << list->Get(i) << ", ", i++);
  cout << list->Get(list->GetLength()-1) << "]";
}

void outSeqSeq(Sequence<Sequence<int>*>* list)
{
  if (list->GetLength() == 0) 
  {
    cout << "[empty]";
    return;
  }
  cout << "[";
  for(int i = 0; i < list->GetLength() - 1; i++)
  {
    outSeq(list->Get(i));
    cout << ", ";
  }
  outSeq(list->Get(list->GetLength()-1));
  cout << "]";
}

void SetBaseGraph(Graph<VertexCore, EdgeCore>& graph1)
{
  Vertex<VertexCore> vert1(1);
  Vertex<VertexCore> vert2(2);
  Vertex<VertexCore> vert3(3);
  Vertex<VertexCore> vert4(4);
  Vertex<VertexCore> vert5(5);
  Vertex<VertexCore> vert6(6);

  EdgeCore core1(7);
  Edge<EdgeCore> edge1(1, 1, 2, core1);
  EdgeCore core2(9);
  Edge<EdgeCore> edge2(2, 1, 3, core2);
  EdgeCore core3(10);
  Edge<EdgeCore> edge3(3, 2, 3, core3);
  EdgeCore core4(14);
  Edge<EdgeCore> edge4(4, 1, 6, core4);
  EdgeCore core5(2);
  Edge<EdgeCore> edge5(5, 3, 6, core5);
  EdgeCore core6(9);
  Edge<EdgeCore> edge6(6, 5, 6, core6);
  EdgeCore core7(6);
  Edge<EdgeCore> edge7(7, 4, 5, core7);
  EdgeCore core8(11);
  Edge<EdgeCore> edge8(8, 3, 4, core8);
  EdgeCore core9(15);
  Edge<EdgeCore> edge9(9, 2, 4, core9);

  graph1.AddVertex(vert1);
  graph1.AddVertex(vert2);
  graph1.AddVertex(vert3);
  graph1.AddVertex(vert4);
  graph1.AddVertex(vert5);
  graph1.AddVertex(vert6);
  graph1.AddEdge(1, edge1);
  graph1.AddEdge(1, edge2);
  graph1.AddEdge(1, edge4);
  graph1.AddEdge(2, edge3);
  graph1.AddEdge(2, edge9);
  graph1.AddEdge(3, edge5);
  graph1.AddEdge(3, edge8);
  graph1.AddEdge(4, edge7);
  graph1.AddEdge(5, edge6);
}

void SetComponentGraph(Graph<VertexCore, EdgeCore>& graph1)
{
  Vertex<VertexCore> vert1(1);
  Vertex<VertexCore> vert2(2);
  Vertex<VertexCore> vert3(3);

  Vertex<VertexCore> vert4(4);
  Vertex<VertexCore> vert5(5);

  Vertex<VertexCore> vert6(6);

  EdgeCore core1(1);
  Edge<EdgeCore> edge1(1, 1, 2, core1);
  EdgeCore core2(2);
  Edge<EdgeCore> edge2(2, 2, 3, core2);
  EdgeCore core3(3);
  Edge<EdgeCore> edge3(3, 3, 1, core3);

  EdgeCore core4(4);
  Edge<EdgeCore> edge4(4, 4, 5, core4);
  
  graph1.AddVertex(vert1);
  graph1.AddVertex(vert2);
  graph1.AddVertex(vert3);
  
  graph1.AddVertex(vert4);
  graph1.AddVertex(vert5);

  graph1.AddVertex(vert6);

  graph1.AddEdge(1, edge1);
  graph1.AddEdge(2, edge2);
  graph1.AddEdge(3, edge3);

  graph1.AddEdge(4, edge4);
}