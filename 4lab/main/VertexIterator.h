#include "vector"
#include <map>
#include <set>

template <typename T>
class VertexIterator
{ public:
   using MapIterator = typename std::map<int, T>::iterator;

    VertexIterator(MapIterator it, MapIterator end_it)
        : current(it), end(end_it) {}

    VertexIterator& operator++() {
        if (current != end) {
            ++current;
        }
        return *this;
    }

    VertexIterator& operator--() {
        if (current != end) {
            --current;
        }
        return *this;
    }

    T operator*() const {
        return current->second;
    }

    bool operator==(const VertexIterator& other) const {
        return current == other.current;
    }

    bool operator!=(const VertexIterator& other) const {
        return current != other.current;
    }

private:
    MapIterator current;
    MapIterator end;


};