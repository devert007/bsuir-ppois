#include "gtest/gtest.h"
#include "OrientedGraph.cpp"
TEST(test_edgeIncidentIterator_class, edgeIncidentIterator_test) {
	OrientedGraph<string> graph;
	graph.addVertex("a");
	graph.addVertex("b");
	graph.addVertex("c");
	graph.addEdge("a", "b");
	graph.addEdge("b", "c");
	graph.addEdge("c", "c");
	string expectedOutput = "";

	for (auto it = graph.begin_incidentEdges("b"); it != graph.end_incidentEdges("b"); ++it)
	{
	    auto edge = *it;
		expectedOutput+= edge.first + edge.second + " ";
	}
	//// ���������
	//for (auto it = graph.begin_adjacentVertices("b"); it != graph.end_adjacentVertices("b"); ++it)
	//{
	//    cout << *it << endl;
	//}


	EXPECT_EQ(expectedOutput, "");

}