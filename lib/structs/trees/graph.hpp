#pragma once
using namespace std;

#include "../containers/mapBinary.hpp"
#include "../containers/imap.hpp"
#include "LinkedList.hpp"
#include "../containers/PairKeyVal.hpp"
#include "../sequence/sequence.hpp"
#include "../sequence/arraySequence.hpp"

template <typename VertexCore>
class Vertex
{
  private:
    int id;
    VertexCore data;

  public:
    VertexCore& GetVertexData() 
    {
      return data;
    }
    
    int GetVertexId() const
    {
      return id;
    }

    Vertex(){}
    Vertex(int id) {this->id = id;}
    Vertex(int id, const VertexCore& data)
    {
      this->id = id;
      this->data = data;
    }

    bool operator== (const Vertex<VertexCore>& vert) const
    {
      if (id == vert.id) return true;
      return false;
    }

    Vertex& operator= (const Vertex& vert)
    {
      id = vert.id;
      data = vert.data;
      return *this;
    }
};

template <typename EdgeCore>
class Edge
{
  private:
    int id;
    int startVertexId, endVertexId;
    EdgeCore data;

  public:
    int GetEdgeId() const
    {
      return id;
    }

    int GetEdgeStartVertexId() const
    {
      return startVertexId;
    }
    
    int GetEdgeEndVertexId() const
    {
      return endVertexId;
    }

    const EdgeCore& GetEdgeData() const
    {
      return data;
    }

    Edge(){}
    Edge(int id, int startVertexId, int endVertexId)
    {
      this->id = id;
      this->startVertexId = startVertexId;
      this->endVertexId = endVertexId;
    }
    Edge(int id, int startVertexId, int endVertexId, const EdgeCore& data)
    {
      this->id = id;
      this->startVertexId = startVertexId;
      this->endVertexId = endVertexId;
      this->data = data;
    }

    Edge& operator= (const Edge& edge1)
    {
      id = edge1.id;
      startVertexId = edge1.startVertexId;
      endVertexId = edge1.endVertexId;
      data = edge1.data;
      return *this;
    } 
};



template <typename EdgeCore>
class DijkstraWay
{
  public:
    Sequence<int>* vertexesIdsWay;
    EdgeCore wayStats;
};

template <typename VertexCore, typename EdgeCore>
class Graph
{
  private:
    IMap<Vertex<VertexCore>, LinkedList<Edge<EdgeCore>>>* map;
    int vertexesCount;
    bool (*edgeCoreCmp)(const EdgeCore&, const EdgeCore&);

  public:
    Graph(bool (*cmp)(const PairKeyVal<Vertex<VertexCore>, LinkedList<Edge<EdgeCore>>>&, const PairKeyVal<Vertex<VertexCore>, LinkedList<Edge<EdgeCore>>>& ))
    {
      map = new AVLMap<Vertex<VertexCore>, LinkedList<Edge<EdgeCore>>>(cmp);
      vertexesCount = 0;
      edgeCoreCmp = nullptr;
    }

    int GetVertexCount() const
    {
      return vertexesCount;
    }

    Sequence<int>* GetAdjacentVertexIdList(int vertexId) const
    {
      Sequence<int>* list = new ArraySequence<int>();
      Vertex<VertexCore> vertx(vertexId);
      for (int i = 0; i < map->Get(vertx).GetLength(); i++)
      {
        list->Append(map->Get(vertx).Get(i).GetEdgeEndVertexId());
      }
      return list;
    }

    const EdgeCore& GetEdgeCore(int startVertexId, int endVertexId) const
    {
      Vertex<VertexCore> vertx(startVertexId);
      // костыль для обхода варнинга
      int res = 0;
      for (int i = 0; i < map->Get(vertx).GetLength(); i++)
      {
        if (endVertexId == map->Get(vertx).Get(i).GetEdgeEndVertexId())
        {
          res = i;
          break;
        }
      }
      return map->Get(vertx).Get(res).GetEdgeData();
    }

    void AddVertex(const Vertex<VertexCore>& vert)
    {
      LinkedList<Edge<EdgeCore>> emptyList;
      map->Add(vert, emptyList);
      vertexesCount++;
    }

    void AddEdge(int vertexId, const Edge<EdgeCore>& inEdge)
    {
      Vertex<VertexCore> vert1(vertexId);
      map->Get(vert1).Append(inEdge);

      Edge<EdgeCore> secEdge(inEdge.GetEdgeId(), inEdge.GetEdgeEndVertexId(), inEdge.GetEdgeStartVertexId(), inEdge.GetEdgeData());
      Vertex<VertexCore> vert2(secEdge.GetEdgeStartVertexId());
      map->Get(vert2).Append(secEdge);
    }

    Sequence<int>* GetVertexIds() const
    {
      Sequence<Vertex<VertexCore>>* vertexes = map->GetKeys();
      Sequence<int>* vertexIds = new ArraySequence<int>();
      for (int i = 0; i < vertexes->GetLength(); i++)
      {
        vertexIds->Append(vertexes->Get(i).GetVertexId());
      }
      delete vertexes;
      return vertexIds;
    }

    LinkedList<Edge<EdgeCore>>& GetEdgeList(int vertexId) const
    {
      Vertex<VertexCore> vert(vertexId);
      return map->Get(vert);
    }

    void SetEdgeCoreCmp(bool (*cmp)(const EdgeCore&, const EdgeCore&))
    {
      edgeCoreCmp = cmp;
    }

    DijkstraWay<EdgeCore>* Dijkstra(int startVertexId, int endVertexId, const EdgeCore& infEdgeCore, const EdgeCore& nullEdgeCore)
    {
      Sequence<EdgeCore>* waysEdgesStats = new ArraySequence<EdgeCore>();
      Sequence<int>* parentId = new ArraySequence<int>();
      Sequence<bool>* vertexesCheckStatus = new ArraySequence<bool>();

      for (int i = 0; i < vertexesCount; i++)
      {
        waysEdgesStats->Append(infEdgeCore);
        parentId->Append(-1);
        vertexesCheckStatus->Append(false);
      }
      waysEdgesStats->Set(startVertexId-1, nullEdgeCore);
      parentId->Set(startVertexId-1, startVertexId-1);

      for (int i = 0; i < vertexesCount; i++)
      {
        int activeVertexIdx = -1;
        for (int j = 0; j < vertexesCount; j++)
        {
          if (!vertexesCheckStatus->Get(j) && (activeVertexIdx == -1 || edgeCoreCmp(waysEdgesStats->Get(j), waysEdgesStats->Get(activeVertexIdx)))) activeVertexIdx = j;
        }
        if (waysEdgesStats->Get(activeVertexIdx) == infEdgeCore) break;
        vertexesCheckStatus->Set(activeVertexIdx, true);
        Sequence<int>* AdjacentVertexesId = GetAdjacentVertexIdList(activeVertexIdx + 1);
        for (int j = 0; j < AdjacentVertexesId->GetLength(); j++)
        {
          if (edgeCoreCmp(waysEdgesStats->Get(activeVertexIdx) + GetEdgeCore(activeVertexIdx + 1, AdjacentVertexesId->Get(j)), waysEdgesStats->Get(AdjacentVertexesId->Get(j) - 1)))
          {
            waysEdgesStats->Set(AdjacentVertexesId->Get(j) - 1, waysEdgesStats->Get(activeVertexIdx) + GetEdgeCore(activeVertexIdx + 1, AdjacentVertexesId->Get(j)));
            parentId->Set(AdjacentVertexesId->Get(j) - 1, activeVertexIdx);
          }
        }
        delete AdjacentVertexesId;
      }
      
      DijkstraWay<EdgeCore>* result = new DijkstraWay<EdgeCore>();
      result->vertexesIdsWay = new ArraySequence<int>();
      result->wayStats = waysEdgesStats->Get(endVertexId - 1);
      int currentVertexId = endVertexId - 1;
      while (currentVertexId != startVertexId - 1)
      {
        result->vertexesIdsWay->Append(currentVertexId + 1);
        currentVertexId = parentId->Get(currentVertexId);
      }
      result->vertexesIdsWay->Append(startVertexId);

      delete waysEdgesStats;
      delete parentId;
      delete vertexesCheckStatus;

      return result;
    }

    Sequence<Sequence<int>*>* GetConnectedComponents()
    {
      Sequence<Sequence<int>*>* res = new ArraySequence<Sequence  <int>*>();
      Sequence<bool>* checkedVertexes = new ArraySequence<bool>();

      for (int i = 0; i < vertexesCount; checkedVertexes->Append(false), i++);
      while (checkedVertexes->Contains(false))
      {
        Sequence<int>* component = new ArraySequence<int>();
        int unCheckVertexId = checkedVertexes->IndexOf(false) + 1;
        checkedVertexes->Set(unCheckVertexId - 1, true);
        LinkedList<int> queue;
        queue.Append(unCheckVertexId);
        
        while(queue.GetLength())
        {
          Sequence<int>* adjacentVertexes = GetAdjacentVertexIdList(queue.Get(0));
          for (int i = 0; i < adjacentVertexes->GetLength(); i++)
          {
            if (!checkedVertexes->Get(adjacentVertexes->Get(i) - 1))
            {
              queue.Append(adjacentVertexes->Get(i));
              checkedVertexes->Set(adjacentVertexes->Get(i) - 1, true);
            }
          }
          delete adjacentVertexes;
          component->Append(queue.Get(0));
          queue.Delete(0);
        }

        res->Append(component);
      }

      delete checkedVertexes;
      return res;
    }

    ~Graph()
    {
      delete map;
    }
  
};
