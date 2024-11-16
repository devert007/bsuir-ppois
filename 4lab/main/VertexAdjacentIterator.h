#include <iostream>
#include <map>
#include <vector>

using namespace std;

template <typename T>
class VertexAdjacentIterator
{
private:
  const vector<pair<int, int>> edges;
  const map<int, T> vertices;
  int vertexID;
  size_t currentEdgeIndex;

public:
  VertexAdjacentIterator(const vector<pair<int, int>> &edg, int vertexID, const map<int, T> &vertices, size_t currentEdgeIndex = 0)
      : edges(edg), vertexID(vertexID), vertices(vertices), currentEdgeIndex(currentEdgeIndex) {}

  bool operator!=(const VertexAdjacentIterator &other)
  {
    return currentEdgeIndex != other.currentEdgeIndex;
  }

  // Оператор разыменования
  T operator*()
  {

    if (edges[currentEdgeIndex].first == vertexID)
      return vertices.at(edges[currentEdgeIndex].second);
    else
      return vertices.at(edges[currentEdgeIndex].first);
  }
  // Оператор инкремента
  VertexAdjacentIterator &operator++()
  {
    // Перебор рёбер, смежных вершине
    do
    {
      ++currentEdgeIndex;
    } while (currentEdgeIndex < edges.size() &&
             !(edges[currentEdgeIndex].first == vertexID || edges[currentEdgeIndex].second == vertexID));
    return *this;
  }
};
