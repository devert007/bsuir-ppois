#include <iostream>
#include <map>
#include <vector>

using namespace std;

template <typename T>
class EdgeIncidentIterator
{
private:
  const vector<vector<int>> matrix_incident;
  const vector<pair<int, int>> edges;
  int vertexID;
  size_t currentEdgeIndex;

public:
  EdgeIncidentIterator(const vector<vector<int>> mat, const vector<pair<int, int>> edg, int vertexID, size_t currentEdgeIndex)
      : matrix_incident(mat), edges(edg), vertexID(vertexID), currentEdgeIndex(currentEdgeIndex) {}

  bool operator!=(const EdgeIncidentIterator &other)
  {
    return currentEdgeIndex != other.currentEdgeIndex;
  }

  // Оператор разыменования
  pair<int, int> operator*()
  {
    return edges[currentEdgeIndex];
  }

  EdgeIncidentIterator &operator++()
  {
    // Перебор рёбер, инцидентных вершине
    do
    {
      ++currentEdgeIndex;
    } while (currentEdgeIndex < edges.size() &&
             !(matrix_incident[vertexID][currentEdgeIndex] != 0));
    return *this;
  }
};
