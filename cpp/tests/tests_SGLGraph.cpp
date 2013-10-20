/*
 *  tests_theGraph.cpp
 *
 *  Created on: Oct 11, 2013
 *
 *  Author: Alexandre Baron
 */

#include "gtest/gtest.h"
#include "SGL.h"

using namespace SGL;
using namespace std;

//*********************************FIXTURES************************************
//*****************************************************************************
//  GraphTest fixture
// *****************************************************************************
class GraphTest: public ::testing::Test {
public:
	graph<int> theGraph;

protected:
	void addVertices(int nbr, int p_from);
};

void GraphTest::addVertices(int p_nbr, int p_from) {
	for (int i = 0; i < p_nbr; i++) {
		theGraph.addVertex(p_from);
		p_from++;
	}
}

TEST_F(GraphTest, constructor) {
	EXPECT_EQ((int)theGraph.size(), 0);
	EXPECT_EQ((int)theGraph.order(), 0);
}

TEST_F(GraphTest, LogicOnEmptyGraph) {
	EXPECT_THROW(theGraph.deleteEdge(42, 21), logic_error);
	EXPECT_THROW(theGraph.deleteVertex(42), logic_error);
	EXPECT_THROW(theGraph.hasEdge(42, 21), logic_error);
	EXPECT_THROW(theGraph.vertexInDegree(42), logic_error);
	EXPECT_THROW(theGraph.vertexOutDegree(42), logic_error);
	EXPECT_THROW(theGraph.vertexNeighborhood(42), logic_error);
}

TEST_F(GraphTest, addVertex) {
	theGraph.addVertex(42);
	EXPECT_THROW(theGraph.addVertex(42), logic_error);
	theGraph.addVertex(21);
}

TEST_F(GraphTest, deleteVertex) {
	theGraph.addVertex(42);
	EXPECT_THROW(theGraph.deleteVertex(41), logic_error);
	theGraph.deleteVertex(42);
	EXPECT_THROW(theGraph.deleteVertex(42), logic_error);
}

TEST_F(GraphTest, hasVertex) {
	EXPECT_FALSE(theGraph.hasVertex(42));
	theGraph.addVertex(42);
	EXPECT_TRUE(theGraph.hasVertex(42));
	theGraph.deleteVertex(42);
	EXPECT_FALSE(theGraph.hasVertex(42));
	addVertices(2, 42);
	EXPECT_TRUE(theGraph.hasVertex(42));
	EXPECT_TRUE(theGraph.hasVertex(43));
}

TEST_F(GraphTest, vertexInDegree) {
	theGraph.addVertex(42);
	EXPECT_EQ((int)theGraph.vertexInDegree(42), 0);
	theGraph.addVertex(21);
	theGraph.addEdge(21, 42);
	EXPECT_EQ((int)theGraph.vertexInDegree(42), 1);
	theGraph.addVertex(84);
	theGraph.addEdge(84, 42);
	EXPECT_EQ((int)theGraph.vertexInDegree(42), 2);
	theGraph.deleteVertex(84);
	EXPECT_EQ((int)theGraph.vertexInDegree(42), 1);
	theGraph.deleteVertex(21);
	EXPECT_EQ((int)theGraph.vertexInDegree(42), 0);
	theGraph.deleteVertex(42);
	EXPECT_THROW(theGraph.vertexInDegree(42), logic_error);
}

TEST_F(GraphTest, vertexOutDegree) {
	theGraph.addVertex(42);
	EXPECT_EQ((int)theGraph.vertexOutDegree(42), 0);
	theGraph.addVertex(21);
	theGraph.addEdge(42, 21);
	EXPECT_EQ((int)theGraph.vertexOutDegree(42), 1);
	theGraph.addVertex(84);
	theGraph.addEdge(42, 84);
	EXPECT_EQ((int)theGraph.vertexOutDegree(42), 2);
	theGraph.deleteVertex(84);
	EXPECT_EQ((int)theGraph.vertexOutDegree(42), 1);
	theGraph.deleteVertex(21);
	EXPECT_EQ((int)theGraph.vertexOutDegree(42), 0);
	theGraph.deleteVertex(42);
	EXPECT_THROW(theGraph.vertexOutDegree(42), logic_error);
}

TEST_F(GraphTest, vertexIsSource) {
	EXPECT_THROW(theGraph.vertexIsSource(42), logic_error);
	theGraph.addVertex(42);
	EXPECT_TRUE(theGraph.vertexIsSource(42));
	theGraph.addVertex(21);
	theGraph.addEdge(21, 42);
	EXPECT_FALSE(theGraph.vertexIsSource(42));
	theGraph.deleteVertex(21);
	EXPECT_TRUE(theGraph.vertexIsSource(42));
	theGraph.addVertex(21);
	theGraph.addEdge(42, 21);
	EXPECT_TRUE(theGraph.vertexIsSource(42));
}

TEST_F(GraphTest, vertexIsSink) {
	EXPECT_THROW(theGraph.vertexIsSink(42), logic_error);
	theGraph.addVertex(42);
	EXPECT_TRUE(theGraph.vertexIsSink(42));
	theGraph.addVertex(21);
	theGraph.addEdge(21, 42);
	EXPECT_TRUE(theGraph.vertexIsSink(42));
	theGraph.deleteVertex(21);
	EXPECT_TRUE(theGraph.vertexIsSink(42));
	theGraph.addVertex(21);
	theGraph.addEdge(42, 21);
	EXPECT_FALSE(theGraph.vertexIsSink(42));
}

TEST_F(GraphTest, vertexNeighborhood) {
	addVertices(6, 42);
	// Two edges coming to 42
	theGraph.addEdge(43, 42);
	theGraph.addEdge(44, 42);
	// Two edges coming from 42
	theGraph.addEdge(42, 44);
	theGraph.addEdge(42, 45);

	vector<int> neighbors = theGraph.vertexNeighborhood(42);
	vector<int>::const_iterator found;

	// Neighborhood of 42 should be 3 vertices
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
	neighbors = theGraph.vertexNeighborhood(42, true);
	EXPECT_EQ((int)neighbors.size(), 4);
	for (int i = 42; i < 46; i++) {
		// each of the concerned vertices should be in the vector
		found = std::find(neighbors.begin(), neighbors.end(), i);
		EXPECT_NE(found, neighbors.end());
	}
	// Vertices which aren't in 42's neighborhood shouldn't be in the vector
	theGraph.addEdge(46, 43);
	found = std::find(neighbors.begin(), neighbors.end(), 46);
	EXPECT_EQ(found, neighbors.end());
	found = std::find(neighbors.begin(), neighbors.end(), 47);
	EXPECT_EQ(found, neighbors.end());
}

TEST_F(GraphTest, vertices) {
	vector<int> vertices = theGraph.vertices();
	EXPECT_EQ((int)vertices.size(), 0);
	addVertices(6, 42);
	vertices = theGraph.vertices();

	vector<int>::const_iterator found;

	EXPECT_EQ((int)vertices.size(), 6);
	for (int i = 42; i < 48; i++) {
		// each of the concerned vertices should be in the vector
		found = std::find(vertices.begin(), vertices.end(), i);
		EXPECT_NE(found, vertices.end());
	}
}

TEST_F(GraphTest, addEdge) {
	EXPECT_THROW(theGraph.addEdge(41, 42), logic_error);
	addVertices(2, 42);
	theGraph.addEdge(42, 43);
	theGraph.addEdge(43, 42);
	EXPECT_THROW(theGraph.addEdge(42, 41), logic_error);
	EXPECT_THROW(theGraph.addEdge(41, 43), logic_error);
}

TEST_F(GraphTest, deleteEdge) {
	EXPECT_THROW(theGraph.deleteEdge(42, 41), logic_error);
	addVertices(2, 42);
	EXPECT_THROW(theGraph.deleteEdge(42, 41), logic_error);
	EXPECT_THROW(theGraph.deleteEdge(41, 43), logic_error);
	theGraph.addEdge(42, 43);
	EXPECT_THROW(theGraph.deleteEdge(43, 42), logic_error);
	theGraph.addEdge(43, 42);
	theGraph.deleteEdge(42, 43);
	theGraph.deleteEdge(43, 42);
	EXPECT_THROW(theGraph.deleteEdge(42, 43), logic_error);
	EXPECT_THROW(theGraph.deleteEdge(43, 42), logic_error);
}

TEST_F(GraphTest, hasEdge) {
	EXPECT_THROW(theGraph.addEdge(41, 42), logic_error);
	addVertices(2, 42);
	EXPECT_FALSE(theGraph.hasEdge(42, 43));
	theGraph.addEdge(42, 43);
	EXPECT_FALSE(theGraph.hasEdge(43, 42));
	EXPECT_TRUE(theGraph.hasEdge(42, 43));
	theGraph.addEdge(43, 42);
	EXPECT_TRUE(theGraph.hasEdge(43, 42));
	EXPECT_TRUE(theGraph.hasEdge(42, 43));
	theGraph.deleteEdge(42, 43);
	EXPECT_TRUE(theGraph.hasEdge(43, 42));
	EXPECT_FALSE(theGraph.hasEdge(42, 43));
	theGraph.deleteEdge(43, 42);
	EXPECT_FALSE(theGraph.hasEdge(43, 42));
	EXPECT_FALSE(theGraph.hasEdge(42, 43));
}

TEST_F(GraphTest, display) {
	cout << theGraph;
	addVertices(6, 42);
	cout << theGraph;
	theGraph.addEdge(42, 43);
	theGraph.addEdge(42, 45);
	theGraph.addEdge(43, 46);
	theGraph.addEdge(43, 42);
	theGraph.addEdge(46, 45);
	theGraph.addEdge(46, 42);
	theGraph.addEdge(47, 42);
	theGraph.addEdge(47, 43);
	theGraph.addEdge(47, 44);
	theGraph.addEdge(47, 45);
	theGraph.addEdge(47, 46);
	theGraph.addEdge(47, 47);
	cout << theGraph;
}

TEST_F(GraphTest, areEqual) {
	graph<int>	copy(theGraph);

	EXPECT_TRUE(copy == theGraph);
	theGraph.addVertex(42);
	theGraph.addVertex(43);
	EXPECT_FALSE(copy == theGraph);
	copy.addVertex(42);
	copy.addVertex(43);
	EXPECT_TRUE(copy == theGraph);
	theGraph.addEdge(42, 43);
	theGraph.addEdge(43, 42);
	EXPECT_FALSE(copy == theGraph);
	copy.addEdge(42, 43);
	EXPECT_FALSE(copy == theGraph);
	copy.addEdge(43, 42);
	EXPECT_TRUE(copy == theGraph);
}

TEST_F(GraphTest, CopyConstructor) {
	graph<int>	copy(theGraph);

	EXPECT_EQ((int)copy.size(), 0);
	EXPECT_EQ((int)copy.order(), 0);

	addVertices(6, 42);
	EXPECT_EQ((int)theGraph.order(), 6);

	graph<int>	copy2(theGraph);
	vector<int> vertices = copy2.vertices();
	vector<int>::const_iterator found;

	EXPECT_EQ(theGraph.order(), copy2.order());
	for (int i = 42; i < 48; i++) {
		// each of the concerned vertices should be in the vector
		found = std::find(vertices.begin(), vertices.end(), i);
		EXPECT_NE(found, vertices.end());
	}
}

TEST_F(GraphTest, AssignmentOperator) {
	// from empty graph to empty graph
	graph<int>	copy;

	EXPECT_EQ((int)theGraph.size(), 0);
	EXPECT_EQ((int)theGraph.order(), 0);
	copy = theGraph;
	EXPECT_EQ((int)copy.size(), 0);
	EXPECT_EQ((int)copy.order(), 0);

	// from full graph to empty graph
	addVertices(6, 42);
	theGraph.addEdge(42, 43);
	theGraph.addEdge(42, 45);
	theGraph.addEdge(43, 46);

	copy = theGraph;
	EXPECT_TRUE(copy == theGraph);

	// from empty graph to full graph
	graph<int>	copy2;

	copy = copy2;
	EXPECT_TRUE(copy == copy2);

	// from full graph to full graph
	copy = theGraph;
	addVertices(2, 1);
	theGraph.addEdge(46, 45);
	theGraph.addEdge(46, 42);
	copy = theGraph;
	EXPECT_TRUE(copy == theGraph);
}
