#include "OrientedGraph.h"
template <typename T>
typename OrientedGraph<T>::vertexID OrientedGraph<T>::addVertex(const vertexData &data)
{
  vertexID id = nextVertexID++;
  vertices[id] = data;
  for (auto row : matrix_incident)
  {
    row.push_back(0); // дополняем каждую строку нулем для нашей новой вершины
  }
  matrix_incident.emplace_back(edges.size(), 0); // дополняем еще одну строку нашей матрице и заполняем ее нулями
  return id;
}
template <typename T>
int OrientedGraph<T>::getCountVertices()
{
  return vertices.size();
}

template <typename T>
typename OrientedGraph<T>::vertexID OrientedGraph<T>::addEdge(const vertexData &data1, const vertexData &data2)
{
  vertexID from = findVertexID(data1); // находим первую вершину
  vertexID to = findVertexID(data2);   // находим вторую вершину

  edgeID edgeId = nextEdgeID++;
  edges.emplace_back(from, to);

  for (auto &row : matrix_incident)
  {
    row.push_back(0);
  }
  matrix_incident[from][edgeId] = 1;
  matrix_incident[to][edgeId] = -1;

  return edgeId;
}
template <typename T>
typename OrientedGraph<T>::vertexID OrientedGraph<T>::findVertexID(const vertexData &data)
{
  for (const auto &vertex : vertices)
  {
    if (vertex.second == data)
    {
      return vertex.first;
    }
  }
}

template <typename T>
int OrientedGraph<T>::getCountEdges()
{
  return edges.size();
}
template <typename T>
bool OrientedGraph<T>::isHaveVertex(const vertexData &dataForFindVertex)
{
  return findVertexID(dataForFindVertex) != -1;
}
template <typename T>
bool OrientedGraph<T>::isHaveEdge(const vertexData &data1, const vertexData &data2)
{
  vertexID id1 = findVertexID(data1);
  vertexID id2 = findVertexID(data2);
  return (id1 != -1 && id2 != -1) ? true : false;
}

template <typename T>
void OrientedGraph<T>::removeVertex(const vertexData &dataRemove)
{
  vertexID id = findVertexID(dataRemove);
  vector<pair<vertexID, vertexID>> newEdges; // временный массив рёбер, не связанных с удаляемой вершиной.
  for (auto &edge : edges)
  {
    if (edge.first != id && edge.second != id)
    {
      newEdges.push_back(edge);
    }
  }
  edges = newEdges; // заменяем старый список рёбер на новый.

  matrix_incident.erase(matrix_incident.begin() + id); // удаляем строку с вершиной
  for (auto &row : matrix_incident)
  { // удаляем столбец с этой вершиной, из каждой строки.
    row.erase(row.begin() + id);
  }
}

template <typename T>
void OrientedGraph<T>::removeEdge(const vertexData &data1ForDelete, const vertexData &data2ForDelete)
{
  vertexID id1 = findVertexID(data1ForDelete);
  vertexID id2 = findVertexID(data2ForDelete);
  edgeID edgeIndex = -1;
  for (size_t i = 0; i < edges.size(); ++i)
  { // находим ребро между id1 и id2
    if (edges[i].first == id1 && edges[i].second == id2)
    {
      edgeIndex = i; // сохраняем его индекс и выходим из цикла.
      break;
    }
  }

  if (edgeIndex != -1)
  {
    edges.erase(edges.begin() + edgeIndex);
    for (auto &row : matrix_incident)
    {
      row.erase(row.begin() + edgeIndex); // удаляем столбец с этим ребром
    }
    --nextEdgeID;
  }
}

template <typename T>
void OrientedGraph<T>::printMatrix()
{
  cout << "\t";
  for (size_t i = 0; i < edges.size(); ++i)
  {
    cout << "{" << vertices[edges[i].first] << "," << vertices[edges[i].second] << "} ";
  }
  cout << endl;
  for (size_t i = 0; i < matrix_incident.size(); ++i)
  {
    cout << "v:" << vertices[i] << " |     ";

    for (int val : matrix_incident[i])
    {
      cout << val << "\t";
    }
    cout << endl;
  }
}

template <typename T>
VertexIterator<T> OrientedGraph<T>::beginVertices()
{
  return VertexIterator<T>(vertices.begin(), vertices.end());
}
template <typename T>
VertexIterator<T> OrientedGraph<T>::endVertices()
{
  return VertexIterator<T>(vertices.end(), vertices.end());
}
template <typename T>
EdgeIterator<T> OrientedGraph<T>::beginEdges()
{
  return EdgeIterator<T>(edges.begin(), edges.end());
}
template <typename T>
EdgeIterator<T> OrientedGraph<T>::endEdges()
{
  return EdgeIterator<T>(edges.end(), edges.end());
}
template <typename T>

EdgeIncidentIterator<T> OrientedGraph<T>::begin_incidentEdges(const vertexData &vertex)
{
  vertexID vID = findVertexID(vertex);
  return EdgeIncidentIterator<T>(matrix_incident, edges, vID, 0);
}
template <typename T>

EdgeIncidentIterator<T> OrientedGraph<T>::end_incidentEdges(const vertexData &vertex)
{
  vertexID vID = findVertexID(vertex);

  return EdgeIncidentIterator<T>(matrix_incident, edges, vID, edges.size());
}
template <typename T>
VertexAdjacentIterator<T> OrientedGraph<T>::begin_adjacentVertices(const vertexData &vertex)
{
  vertexID vId = findVertexID(vertex);
  return VertexAdjacentIterator<T>(edges, vId, vertices, 0);
}
template <typename T>
VertexAdjacentIterator<T> OrientedGraph<T>::end_adjacentVertices(const vertexData &vertex)
{
  vertexID vId = findVertexID(vertex);
  return VertexAdjacentIterator<T>(edges, vId, vertices, edges.size());
}