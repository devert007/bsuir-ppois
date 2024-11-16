#include <iostream>
#include <map>
#include <vector>
using namespace std;
#include "VertexIterator.h"
#include "EdgeIterator.h"
#include "EdgeIncidentIterator.h"
#include "VertexAdjacentIterator.h"
template <typename T>
class OrientedGraph
{
public:
  typedef T vertexData;
  typedef int vertexID;
  typedef int edgeID;

private:
  vertexID nextVertexID = 0;
  edgeID nextEdgeID = 0;
  map<vertexID, vertexData> vertices;
  vector<pair<vertexID, vertexID>> edges;
  vector<vector<int>> matrix_incident;
  friend class VertexIterator<T>;

public:
  vertexID addVertex(const vertexData &data);
  edgeID addEdge(const vertexData &data1, const vertexData &data2);
  vertexID findVertexID(const vertexData &data);
  bool isHaveVertex(const vertexData &dataForFindVertex);
  bool isHaveEdge(const vertexData &data1, const vertexData &data2);
  int getCountVertices();
  int getCountEdges();
  void removeVertex(const vertexData &dataRemove);
  void removeEdge(const vertexData &data1ForDelete, const vertexData &data2ForDelete);
  void printMatrix();
  VertexIterator<T> beginVertices();
  VertexIterator<T> endVertices();
  EdgeIterator<T> beginEdges();
  EdgeIterator<T> endEdges();
  EdgeIncidentIterator<T> begin_incidentEdges(const vertexData &vertex);
  EdgeIncidentIterator<T> end_incidentEdges(const vertexData &vertex);
  VertexAdjacentIterator<T> begin_adjacentVertices(const vertexData &vertex);
  VertexAdjacentIterator<T> end_adjacentVertices(const vertexData &vertex);
};