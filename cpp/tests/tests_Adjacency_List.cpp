//! \file tests_Adjacency_List.cpp
//! \brief Adjacency_List class unit tests
//! \author baron_a
//! \version 0.1
//! \date Oct 19, 2013

#include <stdexcept>
#include <algorithm>
#include "gtest/gtest.h"
#include "AdjacencyList.h"

using namespace SGL;
using namespace std;

//*********************************FIXTURES************************************
//*****************************************************************************
//  AdjacencyListTest fixture
// *****************************************************************************
class AdjacencyListTest: public ::testing::Test {
public:
	Adjacency_List<int> list;

protected:
	void addVertices(int nbr, int p_from);
};

void AdjacencyListTest::addVertices(int p_nbr, int p_from) {
	for (int i = 0; i < p_nbr; i++) {
		list.addVertex(p_from);
		p_from++;
	}
}

TEST_F(AdjacencyListTest, constructor) {
	EXPECT_EQ((int)list.nbVertices(), 0);
	EXPECT_EQ((int)list.nbEdges(), 0);
}

TEST_F(AdjacencyListTest, LogicOnEmptylist) {
	EXPECT_THROW(list.deleteEdge(42, 21), logic_error);
	EXPECT_THROW(list.deleteVertex(42), logic_error);
	EXPECT_THROW(list.hasEdge(42, 21), logic_error);
	EXPECT_THROW(list.vertexInDegree(42), logic_error);
	EXPECT_THROW(list.vertexOutDegree(42), logic_error);
	EXPECT_THROW(list.vertexNeighborhood(42), logic_error);
}

TEST_F(AdjacencyListTest, addVertex) {
	list.addVertex(42);
	EXPECT_THROW(list.addVertex(42), logic_error);
	list.addVertex(21);
}

TEST_F(AdjacencyListTest, deleteVertex) {
	list.addVertex(42);
	EXPECT_THROW(list.deleteVertex(41), logic_error);
	list.deleteVertex(42);
	EXPECT_THROW(list.deleteVertex(42), logic_error);
}

TEST_F(AdjacencyListTest, hasVertex) {
	EXPECT_FALSE(list.hasVertex(42));
	list.addVertex(42);
	EXPECT_TRUE(list.hasVertex(42));
	list.deleteVertex(42);
	EXPECT_FALSE(list.hasVertex(42));
	addVertices(2, 42);
	EXPECT_TRUE(list.hasVertex(42));
	EXPECT_TRUE(list.hasVertex(43));
}

TEST_F(AdjacencyListTest, vertexInDegree) {
	list.addVertex(42);
	EXPECT_EQ((int)list.vertexInDegree(42), 0);
	list.addVertex(21);
	list.addEdge(21, 42);
	EXPECT_EQ((int)list.vertexInDegree(42), 1);
	list.addVertex(84);
	list.addEdge(84, 42);
	EXPECT_EQ((int)list.vertexInDegree(42), 2);
	list.deleteVertex(84);
	EXPECT_EQ((int)list.vertexInDegree(42), 1);
	list.deleteVertex(21);
	EXPECT_EQ((int)list.vertexInDegree(42), 0);
	list.deleteVertex(42);
	EXPECT_THROW(list.vertexInDegree(42), logic_error);
}

TEST_F(AdjacencyListTest, vertexOutDegree) {
	list.addVertex(42);
	EXPECT_EQ((int)list.vertexOutDegree(42), 0);
	list.addVertex(21);
	list.addEdge(42, 21);
	EXPECT_EQ((int)list.vertexOutDegree(42), 1);
	list.addVertex(84);
	list.addEdge(42, 84);
	EXPECT_EQ((int)list.vertexOutDegree(42), 2);
	list.deleteVertex(84);
	EXPECT_EQ((int)list.vertexOutDegree(42), 1);
	list.deleteVertex(21);
	EXPECT_EQ((int)list.vertexOutDegree(42), 0);
	list.deleteVertex(42);
	EXPECT_THROW(list.vertexOutDegree(42), logic_error);
}

TEST_F(AdjacencyListTest, vertexIsSource) {
	EXPECT_THROW(list.vertexIsSource(42), logic_error);
	list.addVertex(42);
	EXPECT_TRUE(list.vertexIsSource(42));
	list.addVertex(21);
	list.addEdge(21, 42);
	EXPECT_FALSE(list.vertexIsSource(42));
	list.deleteVertex(21);
	EXPECT_TRUE(list.vertexIsSource(42));
	list.addVertex(21);
	list.addEdge(42, 21);
	EXPECT_TRUE(list.vertexIsSource(42));
}

TEST_F(AdjacencyListTest, vertexIsSink) {
	EXPECT_THROW(list.vertexIsSink(42), logic_error);
	list.addVertex(42);
	EXPECT_TRUE(list.vertexIsSink(42));
	list.addVertex(21);
	list.addEdge(21, 42);
	EXPECT_TRUE(list.vertexIsSink(42));
	list.deleteVertex(21);
	EXPECT_TRUE(list.vertexIsSink(42));
	list.addVertex(21);
	list.addEdge(42, 21);
	EXPECT_FALSE(list.vertexIsSink(42));
}

TEST_F(AdjacencyListTest, vertexNeighborhood) {
	addVertices(6, 42);
	// Two edges coming to 42
	list.addEdge(43, 42);
	list.addEdge(44, 42);
	// Two edges coming from 42
	list.addEdge(42, 44);
	list.addEdge(42, 45);

	vector<int> neighbors = list.vertexNeighborhood(42);
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
	neighbors = list.vertexNeighborhood(42, true);
	for (unsigned i = 0; i < neighbors.size(); i++) cout << neighbors[i] << endl;
	EXPECT_EQ((int)neighbors.size(), 4);
	for (int i = 42; i < 46; i++) {
		// each of the concerned vertices should be in the vector
		found = std::find(neighbors.begin(), neighbors.end(), i);
		EXPECT_NE(found, neighbors.end());
	}
	// Vertices which aren't in 42's neighborhood shouldn't be in the vector
	list.addEdge(46, 43);
	found = std::find(neighbors.begin(), neighbors.end(), 46);
	EXPECT_EQ(found, neighbors.end());
	found = std::find(neighbors.begin(), neighbors.end(), 47);
	EXPECT_EQ(found, neighbors.end());
}

TEST_F(AdjacencyListTest, vertices) {
	vector<int> vertices = list.vertices();
	EXPECT_EQ((int)vertices.size(), 0);
	addVertices(6, 42);
	vertices = list.vertices();

	vector<int>::const_iterator found;

	EXPECT_EQ((int)vertices.size(), 6);
	for (int i = 42; i < 48; i++) {
		// each of the concerned vertices should be in the vector
		found = std::find(vertices.begin(), vertices.end(), i);
		EXPECT_NE(found, vertices.end());
	}
}

TEST_F(AdjacencyListTest, addEdge) {
	EXPECT_THROW(list.addEdge(41, 42), logic_error);
	addVertices(2, 42);
	list.addEdge(42, 43);
	list.addEdge(43, 42);
	EXPECT_THROW(list.addEdge(42, 41), logic_error);
	EXPECT_THROW(list.addEdge(41, 43), logic_error);
}

TEST_F(AdjacencyListTest, deleteEdge) {
	EXPECT_THROW(list.deleteEdge(42, 41), logic_error);
	addVertices(2, 42);
	EXPECT_THROW(list.deleteEdge(42, 41), logic_error);
	EXPECT_THROW(list.deleteEdge(41, 43), logic_error);
	list.addEdge(42, 43);
	EXPECT_THROW(list.deleteEdge(43, 42), logic_error);
	list.addEdge(43, 42);
	list.deleteEdge(42, 43);
	list.deleteEdge(43, 42);
	EXPECT_THROW(list.deleteEdge(42, 43), logic_error);
	EXPECT_THROW(list.deleteEdge(43, 42), logic_error);
}

TEST_F(AdjacencyListTest, hasEdge) {
	EXPECT_THROW(list.addEdge(41, 42), logic_error);
	addVertices(2, 42);
	EXPECT_FALSE(list.hasEdge(42, 43));
	list.addEdge(42, 43);
	EXPECT_FALSE(list.hasEdge(43, 42));
	EXPECT_TRUE(list.hasEdge(42, 43));
	list.addEdge(43, 42);
	EXPECT_TRUE(list.hasEdge(43, 42));
	EXPECT_TRUE(list.hasEdge(42, 43));
	list.deleteEdge(42, 43);
	EXPECT_TRUE(list.hasEdge(43, 42));
	EXPECT_FALSE(list.hasEdge(42, 43));
	list.deleteEdge(43, 42);
	EXPECT_FALSE(list.hasEdge(43, 42));
	EXPECT_FALSE(list.hasEdge(42, 43));
}

TEST_F(AdjacencyListTest, display) {
	list.display();
	addVertices(6, 42);
	list.display();
	list.addEdge(42, 43);
	list.addEdge(42, 45);
	list.addEdge(43, 46);
	list.addEdge(43, 42);
	list.addEdge(46, 45);
	list.addEdge(46, 42);
	list.addEdge(47, 42);
	list.addEdge(47, 43);
	list.addEdge(47, 44);
	list.addEdge(47, 45);
	list.addEdge(47, 46);
	list.addEdge(47, 47);
	list.display();
}

TEST_F(AdjacencyListTest, CopyConstructor) {
	Adjacency_List<int>	copy(list);

	EXPECT_EQ((int)copy.nbVertices(), 0);
	EXPECT_EQ((int)copy.nbEdges(), 0);

	addVertices(6, 42);
	EXPECT_EQ((int)list.nbVertices(), 6);

	Adjacency_List<int>	copy2(list);
	vector<int> vertices = copy2.vertices();
	vector<int>::const_iterator found;

	EXPECT_EQ(list.nbVertices(), copy2.nbVertices());
	for (int i = 42; i < 48; i++) {
		// each of the concerned vertices should be in the vector
		found = std::find(vertices.begin(), vertices.end(), i);
		EXPECT_NE(found, vertices.end());
	}
}

TEST_F(AdjacencyListTest, AssignmentOperator) {
	// from empty list to empty list
	Adjacency_List<int>	copy;

	EXPECT_EQ((int)list.nbVertices(), 0);
	EXPECT_EQ((int)list.nbEdges(), 0);
	copy = list;
	EXPECT_EQ((int)copy.nbVertices(), 0);
	EXPECT_EQ((int)copy.nbEdges(), 0);

	// from full list to empty list
	addVertices(6, 42);
	list.addEdge(42, 43);
	list.addEdge(42, 45);
	list.addEdge(43, 46);

	copy = list;
	EXPECT_TRUE(list == copy);

	// from empty list to full list
	Adjacency_List<int>	copy2;

	copy = copy2;
	EXPECT_TRUE(copy == copy2);

	// from full list to full list
	copy = list;
	addVertices(2, 1);
	list.addEdge(46, 45);
	list.addEdge(46, 42);
	copy = list;
	EXPECT_TRUE(copy == list);
}
