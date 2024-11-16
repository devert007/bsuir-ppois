#include "gtest/gtest.h"
#include "OrientedGraph.cpp"
TEST(test_orientedgraph_class, oriented_graph_test) {
	OrientedGraph<string> graph;
	graph.addVertex("a");
	graph.addVertex("b");
	graph.addVertex("c");
	graph.addEdge("a", "b");
	graph.addEdge("b", "c");
	graph.addEdge("c", "c");
	
	string expectedOutput = "";
	testing::internal::CaptureStdout();
	graph.printMatrix();
	string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(graph.getCountEdges(), 3);
	EXPECT_EQ(graph.getCountEdges(), 3);
	graph.removeEdge("a","b");
	EXPECT_EQ(graph.getCountEdges(), 2);
	graph.removeVertex("a");
	EXPECT_EQ(graph.getCountEdges(), 2);
	EXPECT_EQ(graph.isHaveEdge("c", "c"), true);
	EXPECT_EQ(graph.isHaveVertex("c"), true);


	EXPECT_TRUE(true);
}