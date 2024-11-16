#include <iostream>
#include <map>
#include <vector>

using namespace std;

template <typename T>
class EdgeIterator
{
  using VectorIterator = typename vector<pair<int, int>>::iterator;

public:
  EdgeIterator(VectorIterator it, VectorIterator end_it) : current(it), end(end_it) {}

  EdgeIterator &operator++()
  {
    if (current != end)
    {
      ++current;
    }
    return *this;
  }

  EdgeIterator &operator--()
  {
    if (current != end)
    {
      --current;
    }
    return *this;
  }

  pair<int, int> operator*() const
  {
    return *current;
  }

  bool operator==(const EdgeIterator &other) const
  {
    return current == other.current;
  }

  bool operator!=(const EdgeIterator &other) const
  {
    return current != other.current;
  }

private:
  VectorIterator current;
  VectorIterator end;
};
