/*
 *  tests_SGLGraph.cpp
 *
 *  Created on: Oct 11, 2013
 *
 *  Author: Alexandre Baron
 */

#include "gtest/gtest.h"
#include "SGLGraph.h"

using namespace SGL;
using namespace std;

//*********************************FIXTURES************************************
//*****************************************************************************
//  GraphTest fixture
// *****************************************************************************
class GraphTest: public ::testing::Test {
public:
	SGLGraph<int> graph;

protected:
	void addVertices(int nbr, int p_from);
};

void GraphTest::addVertices(int p_nbr, int p_from) {
	for (int i = 0; i < p_nbr; i++) {
		graph.addVertex(p_from);
		p_from++;
	}
}

TEST_F(GraphTest, constructor) {
	EXPECT_EQ((int)graph.size(), 0);
	EXPECT_EQ((int)graph.order(), 0);
}

TEST_F(GraphTest, LogicOnEmptyGraph) {
	EXPECT_THROW(graph.deleteEdge(42, 21), logic_error);
	EXPECT_THROW(graph.deleteVertex(42), logic_error);
	EXPECT_THROW(graph.hasEdge(42, 21), logic_error);
	EXPECT_THROW(graph.vertexInDegree(42), logic_error);
	EXPECT_THROW(graph.vertexOutDegree(42), logic_error);
	EXPECT_THROW(graph.vertexNeighborhood(42), logic_error);
}

TEST_F(GraphTest, addVertex) {
	graph.addVertex(42);
	EXPECT_THROW(graph.addVertex(42), logic_error);
	graph.addVertex(21);
}

TEST_F(GraphTest, deleteVertex) {
	graph.addVertex(42);
	EXPECT_THROW(graph.deleteVertex(41), logic_error);
	graph.deleteVertex(42);
	EXPECT_THROW(graph.deleteVertex(42), logic_error);
}

TEST_F(GraphTest, hasVertex) {
	EXPECT_FALSE(graph.hasVertex(42));
	graph.addVertex(42);
	EXPECT_TRUE(graph.hasVertex(42));
	graph.deleteVertex(42);
	EXPECT_FALSE(graph.hasVertex(42));
	addVertices(2, 42);
	EXPECT_TRUE(graph.hasVertex(42));
	EXPECT_TRUE(graph.hasVertex(43));
}

TEST_F(GraphTest, vertexInDegree) {
	graph.addVertex(42);
	EXPECT_EQ((int)graph.vertexInDegree(42), 0);
	graph.addVertex(21);
	graph.addEdge(21, 42);
	EXPECT_EQ((int)graph.vertexInDegree(42), 1);
	graph.addVertex(84);
	graph.addEdge(84, 42);
	EXPECT_EQ((int)graph.vertexInDegree(42), 2);
	graph.deleteVertex(84);
	EXPECT_EQ((int)graph.vertexInDegree(42), 1);
	graph.deleteVertex(21);
	EXPECT_EQ((int)graph.vertexInDegree(42), 0);
	graph.deleteVertex(42);
	EXPECT_THROW(graph.vertexInDegree(42), logic_error);
}

TEST_F(GraphTest, vertexOutDegree) {
	graph.addVertex(42);
	EXPECT_EQ((int)graph.vertexOutDegree(42), 0);
	graph.addVertex(21);
	graph.addEdge(42, 21);
	EXPECT_EQ((int)graph.vertexOutDegree(42), 1);
	graph.addVertex(84);
	graph.addEdge(42, 84);
	EXPECT_EQ((int)graph.vertexOutDegree(42), 2);
	graph.deleteVertex(84);
	EXPECT_EQ((int)graph.vertexOutDegree(42), 1);
	graph.deleteVertex(21);
	EXPECT_EQ((int)graph.vertexOutDegree(42), 0);
	graph.deleteVertex(42);
	EXPECT_THROW(graph.vertexOutDegree(42), logic_error);
}

TEST_F(GraphTest, vertexIsSource) {
	EXPECT_THROW(graph.vertexIsSource(42), logic_error);
	graph.addVertex(42);
	EXPECT_TRUE(graph.vertexIsSource(42));
	graph.addVertex(21);
	graph.addEdge(21, 42);
	EXPECT_FALSE(graph.vertexIsSource(42));
	graph.deleteVertex(21);
	EXPECT_TRUE(graph.vertexIsSource(42));
	graph.addVertex(21);
	graph.addEdge(42, 21);
	EXPECT_TRUE(graph.vertexIsSource(42));
}

TEST_F(GraphTest, vertexIsSink) {
	EXPECT_THROW(graph.vertexIsSink(42), logic_error);
	graph.addVertex(42);
	EXPECT_TRUE(graph.vertexIsSink(42));
	graph.addVertex(21);
	graph.addEdge(21, 42);
	EXPECT_TRUE(graph.vertexIsSink(42));
	graph.deleteVertex(21);
	EXPECT_TRUE(graph.vertexIsSink(42));
	graph.addVertex(21);
	graph.addEdge(42, 21);
	EXPECT_FALSE(graph.vertexIsSink(42));
}

TEST_F(GraphTest, vertexNeighborhood) {
	addVertices(6, 42);
	// Two edges coming to 42
	graph.addEdge(43, 42);
	graph.addEdge(44, 42);
	// Two edges coming from 42
	graph.addEdge(42, 44);
	graph.addEdge(42, 45);

	vector<int> neighbors = graph.vertexNeighborhood(42);
	vector<int>::const_iterator found;

	// Neighborhood of 42 should be 4 vertices
	EXPECT_EQ((int)neighbors.size(), 3);
	for (int i = 43; i < 46; i++) {
		// each of the concerned vertices should be in the vector
		found = std::find(neighbors.begin(), neighbors.end(), i);
		EXPECT_NE(found, neighbors.end());
	}
	// Vertices which aren't in 42's neighborhood shouldn't be in the vector
	found = std::find(neighbors.begin(), neighbors.end(), 46);
	EXPECT_EQ(found, neighbors.end());

	// Let's test the "closed" parameter (should include the vertex itself in the vector)
	neighbors = graph.vertexNeighborhood(42, true);
	EXPECT_EQ((int)neighbors.size(), 4);
	for (int i = 42; i < 46; i++) {
		// each of the concerned vertices should be in the vector
		found = std::find(neighbors.begin(), neighbors.end(), i);
		EXPECT_NE(found, neighbors.end());
	}
	// Vertices which aren't in 42's neighborhood shouldn't be in the vector
	graph.addEdge(46, 43);
	found = std::find(neighbors.begin(), neighbors.end(), 46);
	EXPECT_EQ(found, neighbors.end());
	found = std::find(neighbors.begin(), neighbors.end(), 47);
	EXPECT_EQ(found, neighbors.end());
}

TEST_F(GraphTest, vertices) {
	vector<int> vertices = graph.vertices();
	EXPECT_EQ((int)vertices.size(), 0);
	addVertices(6, 42);
	vertices = graph.vertices();

	vector<int>::const_iterator found;

	EXPECT_EQ((int)vertices.size(), 6);
	for (int i = 42; i < 48; i++) {
		// each of the concerned vertices should be in the vector
		found = std::find(vertices.begin(), vertices.end(), i);
		EXPECT_NE(found, vertices.end());
	}
}

TEST_F(GraphTest, addEdge) {
	EXPECT_THROW(graph.addEdge(41, 42), logic_error);
	addVertices(2, 42);
	graph.addEdge(42, 43);
	graph.addEdge(43, 42);
	EXPECT_THROW(graph.addEdge(42, 41), logic_error);
	EXPECT_THROW(graph.addEdge(41, 43), logic_error);
}

TEST_F(GraphTest, deleteEdge) {
	EXPECT_THROW(graph.deleteEdge(42, 41), logic_error);
	addVertices(2, 42);
	EXPECT_THROW(graph.deleteEdge(42, 41), logic_error);
	EXPECT_THROW(graph.deleteEdge(41, 43), logic_error);
	graph.addEdge(42, 43);
	EXPECT_THROW(graph.deleteEdge(43, 42), logic_error);
	graph.addEdge(43, 42);
	graph.deleteEdge(42, 43);
	graph.deleteEdge(43, 42);
	EXPECT_THROW(graph.deleteEdge(42, 43), logic_error);
	EXPECT_THROW(graph.deleteEdge(43, 42), logic_error);
}

TEST_F(GraphTest, hasEdge) {
	EXPECT_THROW(graph.addEdge(41, 42), logic_error);
	addVertices(2, 42);
	EXPECT_FALSE(graph.hasEdge(42, 43));
	graph.addEdge(42, 43);
	EXPECT_FALSE(graph.hasEdge(43, 42));
	EXPECT_TRUE(graph.hasEdge(42, 43));
	graph.addEdge(43, 42);
	EXPECT_TRUE(graph.hasEdge(43, 42));
	EXPECT_TRUE(graph.hasEdge(42, 43));
	graph.deleteEdge(42, 43);
	EXPECT_TRUE(graph.hasEdge(43, 42));
	EXPECT_FALSE(graph.hasEdge(42, 43));
	graph.deleteEdge(43, 42);
	EXPECT_FALSE(graph.hasEdge(43, 42));
	EXPECT_FALSE(graph.hasEdge(42, 43));
}

TEST_F(GraphTest, display) {
	graph.display();
	addVertices(6, 42);
	graph.display();
	graph.addEdge(42, 43);
	graph.addEdge(42, 45);
	graph.addEdge(43, 46);
	graph.addEdge(43, 42);
	graph.addEdge(46, 45);
	graph.addEdge(46, 42);
	graph.addEdge(47, 42);
	graph.addEdge(47, 43);
	graph.addEdge(47, 44);
	graph.addEdge(47, 45);
	graph.addEdge(47, 46);
	graph.addEdge(47, 47);
	graph.display();
}

TEST_F(GraphTest, areEqual) {
	SGLGraph<int>	copy(graph);

	EXPECT_TRUE(SGLGraph<int>::areEqual(copy, graph));
	graph.addVertex(42);
	graph.addVertex(43);
	EXPECT_FALSE(SGLGraph<int>::areEqual(copy, graph));
	copy.addVertex(42);
	copy.addVertex(43);
	EXPECT_TRUE(SGLGraph<int>::areEqual(copy, graph));
	graph.addEdge(42, 43);
	graph.addEdge(43, 42);
	EXPECT_FALSE(SGLGraph<int>::areEqual(copy, graph));
	copy.addEdge(42, 43);
	EXPECT_FALSE(SGLGraph<int>::areEqual(copy, graph));
	copy.addEdge(43, 42);
	EXPECT_TRUE(SGLGraph<int>::areEqual(copy, graph));
}

TEST_F(GraphTest, CopyConstructor) {
	SGLGraph<int>	copy(graph);

	EXPECT_EQ((int)copy.size(), 0);
	EXPECT_EQ((int)copy.order(), 0);

	addVertices(6, 42);
	EXPECT_EQ((int)graph.order(), 6);

	SGLGraph<int>	copy2(graph);
	vector<int> vertices = copy2.vertices();
	vector<int>::const_iterator found;

	EXPECT_EQ(graph.order(), copy2.order());
	for (int i = 42; i < 48; i++) {
		// each of the concerned vertices should be in the vector
		found = std::find(vertices.begin(), vertices.end(), i);
		EXPECT_NE(found, vertices.end());
	}
}

TEST_F(GraphTest, AssignmentOperator) {
	// from empty graph to empty graph
	SGLGraph<int>	copy;

	EXPECT_EQ((int)graph.size(), 0);
	EXPECT_EQ((int)graph.order(), 0);
	copy = graph;
	EXPECT_EQ((int)copy.size(), 0);
	EXPECT_EQ((int)copy.order(), 0);

	// from full graph to empty graph
	addVertices(6, 42);
	graph.addEdge(42, 43);
	graph.addEdge(42, 45);
	graph.addEdge(43, 46);

	copy = graph;
	EXPECT_TRUE(SGLGraph<int>::areEqual(copy, graph));

	// from empty graph to full graph
	SGLGraph<int>	copy2;

	copy = copy2;
	EXPECT_TRUE(SGLGraph<int>::areEqual(copy, copy2));

	// from full graph to full graph
	copy = graph;
	addVertices(2, 1);
	graph.addEdge(46, 45);
	graph.addEdge(46, 42);
	copy = graph;
	EXPECT_TRUE(SGLGraph<int>::areEqual(copy, graph));
}
