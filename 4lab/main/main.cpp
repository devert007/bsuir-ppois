//#include <iostream>
//#include <vector>
//#include <string>
//#include "OrientedGraph.cpp"
//
//using namespace std;
//int main()
//{
//   OrientedGraph<string> graph;
//   graph.addVertex("a");
//   graph.addVertex("b");
//   graph.addVertex("c");
//   graph.addEdge("a", "b");
//   graph.addEdge("b", "c");
//   graph.addEdge("c", "c");
//   cout << graph.isHaveEdge("a", "b") << endl;
//   cout << graph.getCountVertices() << endl;
//   graph.printMatrix();
//
//   for (auto it = graph.beginVertices(); it != graph.endVertices(); ++it)
//   {
//       std::cout << *it << " ";
//   }
//
//   for (auto it = graph.beginEdges(); it != graph.endEdges(); ++it)
//   {
//       auto edge = *it;
//       std::cout << "(" << edge.first << ", " << edge.second << ") ";
//   }
//
//   for (auto it = graph.begin_incidentEdges("b"); it != graph.end_incidentEdges("b"); ++it)
//   {
//       auto edge = *it;
//       cout << "Edge: " << edge.first << " -> " << edge.second << endl;
//   }
//   // смежность
//   for (auto it = graph.begin_adjacentVertices("b"); it != graph.end_adjacentVertices("b"); ++it)
//   {
//       cout << *it << endl;
//   }
//
//   return 0;
//}