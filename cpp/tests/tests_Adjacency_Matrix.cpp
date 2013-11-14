/*
 * tests_Adjacency_Matrix.cpp
 *
 *  Created on: Oct 19, 2013
 *      Author: baron_a
 */

#include <stdexcept>
#include <algorithm>
#include "gtest/gtest.h"
#include "AdjacencyMatrix.h"

using namespace SGL;
using namespace std;

//*********************************FIXTURES************************************
//*****************************************************************************
//  AdjacencyMatrixTest fixture
// *****************************************************************************
class AdjacencyMatrixTest: public ::testing::Test {
public:
	AdjacencyMatrixTest();
	Adjacency_Matrix<int> directed_matrix;
	Adjacency_Matrix<int> undirected_matrix;
};

AdjacencyMatrixTest::AdjacencyMatrixTest() : directed_matrix(), undirected_matrix(UNDIRECTED) {}

TEST_F(AdjacencyMatrixTest, constructor) {
	EXPECT_TRUE(directed_matrix.nbVertices() == 0);
	EXPECT_TRUE(directed_matrix.nbEdges() == 0);

	EXPECT_TRUE(undirected_matrix.nbVertices() == 0);
	EXPECT_TRUE(undirected_matrix.nbEdges() == 0);
}

TEST_F(AdjacencyMatrixTest, LogicOnEmptyMatrix) {
	EXPECT_THROW(directed_matrix.deleteEdge(42, 21), logic_error);
	EXPECT_THROW(directed_matrix.deleteVertex(42), logic_error);
	EXPECT_THROW(directed_matrix.hasEdge(42, 21), logic_error);
	EXPECT_THROW(directed_matrix.vertexInDegree(42), logic_error);
	EXPECT_THROW(directed_matrix.vertexOutDegree(42), logic_error);
	EXPECT_THROW(directed_matrix.vertexNeighborhood(42), logic_error);

	EXPECT_THROW(undirected_matrix.deleteEdge(42, 21), logic_error);
	EXPECT_THROW(undirected_matrix.deleteVertex(42), logic_error);
	EXPECT_THROW(undirected_matrix.hasEdge(42, 21), logic_error);
	EXPECT_THROW(undirected_matrix.vertexInDegree(42), logic_error);
	EXPECT_THROW(undirected_matrix.vertexOutDegree(42), logic_error);
	EXPECT_THROW(undirected_matrix.vertexNeighborhood(42), logic_error);
}

TEST_F(AdjacencyMatrixTest, addVertex) {
	directed_matrix.addVertex(42);
	EXPECT_TRUE(directed_matrix.nbVertices() == 1);
	EXPECT_THROW(directed_matrix.addVertex(42), logic_error);
	directed_matrix.addVertex(21);
	directed_matrix.addVertex(34);
	EXPECT_TRUE(directed_matrix.nbVertices() == 3);
	EXPECT_THROW(directed_matrix.addVertex(42), logic_error);
	EXPECT_THROW(directed_matrix.addVertex(21), logic_error);
	EXPECT_THROW(directed_matrix.addVertex(34), logic_error);

	undirected_matrix.addVertex(42);
	EXPECT_TRUE(undirected_matrix.nbVertices() == 1);
	EXPECT_THROW(undirected_matrix.addVertex(42), logic_error);
	undirected_matrix.addVertex(21);
	undirected_matrix.addVertex(34);
	EXPECT_TRUE(undirected_matrix.nbVertices() == 3);
	EXPECT_THROW(undirected_matrix.addVertex(42), logic_error);
	EXPECT_THROW(undirected_matrix.addVertex(21), logic_error);
	EXPECT_THROW(undirected_matrix.addVertex(34), logic_error);
}

TEST_F(AdjacencyMatrixTest, deleteVertex) {
	directed_matrix.addVertex(42);
	EXPECT_THROW(directed_matrix.deleteVertex(41), logic_error);
	directed_matrix.deleteVertex(42);
	EXPECT_TRUE(directed_matrix.nbVertices() == 0);
	EXPECT_THROW(directed_matrix.deleteVertex(42), logic_error);
	directed_matrix.addVertex(21);
	directed_matrix.addVertex(42);
	directed_matrix.addVertex(84);
	directed_matrix.deleteVertex(21);
	EXPECT_TRUE(directed_matrix.nbVertices() == 2);
	directed_matrix.addVertex(21);
	directed_matrix.deleteVertex(42);
	EXPECT_TRUE(directed_matrix.nbVertices() == 2);
	directed_matrix.addVertex(42);
	directed_matrix.deleteVertex(84);
	directed_matrix.deleteVertex(42);
	directed_matrix.deleteVertex(21);
	EXPECT_TRUE(directed_matrix.nbVertices() == 0);

	undirected_matrix.addVertex(42);
	EXPECT_THROW(undirected_matrix.deleteVertex(41), logic_error);
	undirected_matrix.deleteVertex(42);
	EXPECT_TRUE(directed_matrix.nbVertices() == 0);
	EXPECT_THROW(undirected_matrix.deleteVertex(42), logic_error);
	undirected_matrix.addVertex(21);
	undirected_matrix.addVertex(42);
	undirected_matrix.addVertex(84);
	undirected_matrix.deleteVertex(21);
	EXPECT_TRUE(undirected_matrix.nbVertices() == 2);
	undirected_matrix.addVertex(21);
	undirected_matrix.deleteVertex(42);
	EXPECT_TRUE(undirected_matrix.nbVertices() == 2);
	undirected_matrix.addVertex(42);
	undirected_matrix.deleteVertex(84);
	undirected_matrix.deleteVertex(42);
	undirected_matrix.deleteVertex(21);
	EXPECT_TRUE(undirected_matrix.nbVertices() == 0);
}

TEST_F(AdjacencyMatrixTest, hasVertex) {
	EXPECT_FALSE(directed_matrix.hasVertex(42));
	directed_matrix.addVertex(42);
	EXPECT_TRUE(directed_matrix.hasVertex(42));
	directed_matrix.deleteVertex(42);
	EXPECT_FALSE(directed_matrix.hasVertex(42));
	directed_matrix.addVertex(21);
	directed_matrix.addVertex(42);
	EXPECT_TRUE(directed_matrix.hasVertex(21));
	EXPECT_TRUE(directed_matrix.hasVertex(42));

	EXPECT_FALSE(undirected_matrix.hasVertex(42));
	undirected_matrix.addVertex(42);
	EXPECT_TRUE(undirected_matrix.hasVertex(42));
	undirected_matrix.deleteVertex(42);
	EXPECT_FALSE(undirected_matrix.hasVertex(42));
	undirected_matrix.addVertex(21);
	undirected_matrix.addVertex(42);
	EXPECT_TRUE(undirected_matrix.hasVertex(21));
	EXPECT_TRUE(undirected_matrix.hasVertex(42));
}

TEST_F(AdjacencyMatrixTest, vertexInDegree) {
	directed_matrix.addVertex(42);
	EXPECT_TRUE(directed_matrix.vertexInDegree(42) == 0);
	directed_matrix.addVertex(21);
	directed_matrix.addEdge(21, 42);
	EXPECT_TRUE(directed_matrix.vertexInDegree(42) == 1);
	directed_matrix.addVertex(84);
	directed_matrix.addEdge(84, 42);
	EXPECT_TRUE(directed_matrix.vertexInDegree(42) == 2);
	directed_matrix.addEdge(42, 42);
	EXPECT_TRUE(directed_matrix.vertexInDegree(42) == 3);
	directed_matrix.deleteVertex(84);
	EXPECT_TRUE(directed_matrix.vertexInDegree(42) == 2);
	directed_matrix.deleteVertex(21);
	EXPECT_TRUE(directed_matrix.vertexInDegree(42) == 1);
	directed_matrix.deleteVertex(42);
	EXPECT_THROW(directed_matrix.vertexInDegree(42), logic_error);

	undirected_matrix.addVertex(42);
	EXPECT_TRUE(undirected_matrix.vertexInDegree(42) == 0);
	undirected_matrix.addVertex(21);
	undirected_matrix.addEdge(21, 42);
	EXPECT_TRUE(undirected_matrix.vertexInDegree(42) == 1);
	undirected_matrix.addVertex(84);
	undirected_matrix.addEdge(84, 42);
	EXPECT_TRUE(undirected_matrix.vertexInDegree(42) == 2);
	undirected_matrix.addEdge(42, 42);
	EXPECT_TRUE(undirected_matrix.vertexInDegree(42) == 4);
	undirected_matrix.deleteVertex(84);
	EXPECT_TRUE(undirected_matrix.vertexInDegree(42) == 3);
	undirected_matrix.deleteVertex(21);
	EXPECT_TRUE(undirected_matrix.vertexInDegree(42) == 2);
	undirected_matrix.deleteVertex(42);
	EXPECT_THROW(undirected_matrix.vertexInDegree(42), logic_error);
}

TEST_F(AdjacencyMatrixTest, vertexOutDegree) {
	directed_matrix.addVertex(42);
	EXPECT_TRUE(directed_matrix.vertexOutDegree(42) == 0);
	directed_matrix.addVertex(21);
	directed_matrix.addEdge(42, 21);
	EXPECT_TRUE(directed_matrix.vertexOutDegree(42) == 1);
	directed_matrix.addVertex(84);
	directed_matrix.addEdge(42, 84);
	EXPECT_TRUE(directed_matrix.vertexOutDegree(42) == 2);
	directed_matrix.addEdge(42, 42);
	EXPECT_TRUE(directed_matrix.vertexOutDegree(42) == 3);
	directed_matrix.deleteVertex(84);
	EXPECT_TRUE(directed_matrix.vertexOutDegree(42) == 2);
	directed_matrix.deleteVertex(21);
	EXPECT_TRUE(directed_matrix.vertexOutDegree(42) == 1);
	directed_matrix.deleteVertex(42);
	EXPECT_THROW(directed_matrix.vertexOutDegree(42), logic_error);

	undirected_matrix.addVertex(42);
	EXPECT_TRUE(undirected_matrix.vertexOutDegree(42) == 0);
	undirected_matrix.addVertex(21);
	undirected_matrix.addEdge(42, 21);
	EXPECT_TRUE(undirected_matrix.vertexOutDegree(42) == 1);
	undirected_matrix.addVertex(84);
	undirected_matrix.addEdge(42, 84);
	EXPECT_TRUE(undirected_matrix.vertexOutDegree(42) == 2);
	undirected_matrix.addEdge(42, 42);
	EXPECT_TRUE(undirected_matrix.vertexOutDegree(42) == 4);
	undirected_matrix.deleteVertex(84);
	EXPECT_TRUE(undirected_matrix.vertexOutDegree(42) == 3);
	undirected_matrix.deleteVertex(21);
	EXPECT_TRUE(undirected_matrix.vertexOutDegree(42) == 2);
	undirected_matrix.deleteVertex(42);
	EXPECT_THROW(undirected_matrix.vertexOutDegree(42), logic_error);
}

TEST_F(AdjacencyMatrixTest, vertexIsSource) {
	EXPECT_THROW(directed_matrix.vertexIsSource(42), logic_error);
	directed_matrix.addVertex(42);
	EXPECT_TRUE(directed_matrix.vertexIsSource(42));
	directed_matrix.addVertex(21);
	directed_matrix.addEdge(21, 42);
	EXPECT_FALSE(directed_matrix.vertexIsSource(42));
	directed_matrix.deleteVertex(21);
	EXPECT_TRUE(directed_matrix.vertexIsSource(42));
	directed_matrix.addVertex(21);
	directed_matrix.addEdge(42, 21);
	EXPECT_TRUE(directed_matrix.vertexIsSource(42));
	directed_matrix.addEdge(42, 42);
	EXPECT_FALSE(directed_matrix.vertexIsSource(42));

	// it has no sense to search a source in an undirected graph !
	EXPECT_THROW(undirected_matrix.vertexIsSource(42), logic_error);
	undirected_matrix.addVertex(42);
	EXPECT_THROW(undirected_matrix.vertexIsSource(42), logic_error);
	undirected_matrix.addVertex(21);
	undirected_matrix.addEdge(21, 42);
	EXPECT_THROW(undirected_matrix.vertexIsSource(42), logic_error);
}

TEST_F(AdjacencyMatrixTest, vertexIsSink) {
	EXPECT_THROW(directed_matrix.vertexIsSink(42), logic_error);
	directed_matrix.addVertex(42);
	EXPECT_TRUE(directed_matrix.vertexIsSink(42));
	directed_matrix.addVertex(21);
	directed_matrix.addEdge(21, 42);
	EXPECT_TRUE(directed_matrix.vertexIsSink(42));
	directed_matrix.deleteVertex(21);
	EXPECT_TRUE(directed_matrix.vertexIsSink(42));
	directed_matrix.addVertex(21);
	directed_matrix.addEdge(42, 21);
	EXPECT_FALSE(directed_matrix.vertexIsSink(42));

	// it has no sense to search a sink in an undirected graph !
	EXPECT_THROW(undirected_matrix.vertexIsSink(42), logic_error);
	undirected_matrix.addVertex(42);
	EXPECT_THROW(undirected_matrix.vertexIsSink(42), logic_error);
	undirected_matrix.addVertex(21);
	undirected_matrix.addEdge(21, 42);
	EXPECT_THROW(undirected_matrix.vertexIsSink(42), logic_error);
}

TEST_F(AdjacencyMatrixTest, vertexNeighborhood) {
	directed_matrix.addVertex(42);
	directed_matrix.addVertex(43);
	directed_matrix.addVertex(44);
	directed_matrix.addVertex(45);
	directed_matrix.addVertex(46);
	// Two edges coming to 42
	directed_matrix.addEdge(43, 42);
	directed_matrix.addEdge(44, 42);
	// Two edges coming from 42
	directed_matrix.addEdge(42, 43);
	directed_matrix.addEdge(42, 44);

	vector<int> neighbors = directed_matrix.vertexNeighborhood(42);
	vector<int>::const_iterator found;

	// Neighborhood of 42 should be 2 vertices
	EXPECT_TRUE(neighbors.size() == 2);
	for (int i = 43; i < 45; i++) {
		// each of the concerned vertices should be in the vector
		found = std::find(neighbors.begin(), neighbors.end(), i);
		EXPECT_NE(found, neighbors.end());
	}
	// Vertices which aren't in 42's neighborhood shouldn't be in the vector
	found = std::find(neighbors.begin(), neighbors.end(), 46);
	EXPECT_EQ(found, neighbors.end());

	// Let's test the "closed" parameter (should include the vertex itself in the vector)
	neighbors = directed_matrix.vertexNeighborhood(42, true);
	EXPECT_TRUE(neighbors.size() == 3);
	for (int i = 42; i < 45; i++) {
		// each of the concerned vertices should be in the vector
		found = std::find(neighbors.begin(), neighbors.end(), i);
		EXPECT_NE(found, neighbors.end());
	}
	// Vertices which aren't in 42's neighborhood shouldn't be in the vector
	found = std::find(neighbors.begin(), neighbors.end(), 46);
	EXPECT_EQ(found, neighbors.end());
	found = std::find(neighbors.begin(), neighbors.end(), 45);
	EXPECT_EQ(found, neighbors.end());

	directed_matrix.addEdge(42, 42);
	// if there is a loop on 42, it should be in its own neighborhood even when we don't want it closed
	EXPECT_TRUE(neighbors.size() == 3);
	found = std::find(neighbors.begin(), neighbors.end(), 42);
	EXPECT_NE(found, neighbors.end());


	undirected_matrix.addVertex(42);
	undirected_matrix.addVertex(43);
	undirected_matrix.addVertex(44);
	undirected_matrix.addVertex(45);
	undirected_matrix.addVertex(46);
	// Two edges coming to 42
	undirected_matrix.addEdge(43, 42);
	undirected_matrix.addEdge(45, 42);
	// One coming from 42
	undirected_matrix.addEdge(42, 44);

	neighbors = undirected_matrix.vertexNeighborhood(42);

	// Neighborhood of 42 should be 3 vertices : the graph is undirected
	EXPECT_TRUE(neighbors.size() == 3);
	for (int i = 43; i < 46; i++) {
		// each of the concerned vertices should be in the vector
		found = std::find(neighbors.begin(), neighbors.end(), i);
		EXPECT_NE(found, neighbors.end());
	}
	// Vertices which aren't in 42's neighborhood shouldn't be in the vector
	found = std::find(neighbors.begin(), neighbors.end(), 46);
	EXPECT_EQ(found, neighbors.end());

	// Let's test the "closed" parameter (should include the vertex itself in the vector)
	neighbors = undirected_matrix.vertexNeighborhood(42, true);
	EXPECT_TRUE(neighbors.size() == 4);
	for (int i = 42; i < 46; i++) {
		// each of the concerned vertices should be in the vector
		found = std::find(neighbors.begin(), neighbors.end(), i);
		EXPECT_NE(found, neighbors.end());
	}
	// Vertices which aren't in 42's neighborhood shouldn't be in the vector
	found = std::find(neighbors.begin(), neighbors.end(), 46);
	EXPECT_EQ(found, neighbors.end());

	undirected_matrix.addEdge(42, 42);
	// if there is a loop on 42, it should be in its own neighborhood even when we don't want it closed
	EXPECT_TRUE(neighbors.size() == 4);
	found = std::find(neighbors.begin(), neighbors.end(), 42);
	EXPECT_NE(found, neighbors.end());
}

TEST_F(AdjacencyMatrixTest, vertices) {
	vector<int> vertices = directed_matrix.vertices();

	EXPECT_TRUE(vertices.size() == 0);
	directed_matrix.addVertex(42);
	directed_matrix.addVertex(43);
	directed_matrix.addVertex(44);
	directed_matrix.addVertex(45);
	directed_matrix.addVertex(46);
	directed_matrix.addVertex(47);
	vertices = directed_matrix.vertices();
	EXPECT_TRUE(vertices.size() == 6);
	for (int i = 42; i < 48; i++) {
		// each of the concerned vertices should be in the vector
		vector<int>::const_iterator found = std::find(vertices.begin(), vertices.end(), i);
		EXPECT_NE(found, vertices.end());
	}


	vertices = undirected_matrix.vertices();
	EXPECT_TRUE(vertices.size() == 0);
	undirected_matrix.addVertex(42);
	undirected_matrix.addVertex(43);
	undirected_matrix.addVertex(44);
	undirected_matrix.addVertex(45);
	undirected_matrix.addVertex(46);
	undirected_matrix.addVertex(47);
	vertices = undirected_matrix.vertices();
	EXPECT_TRUE(vertices.size() == 6);
	for (int i = 42; i < 48; i++) {
		// each of the concerned vertices should be in the vector
		vector<int>::const_iterator found = std::find(vertices.begin(), vertices.end(), i);
		EXPECT_NE(found, vertices.end());
	}
}

TEST_F(AdjacencyMatrixTest, addEdge) {
	EXPECT_THROW(directed_matrix.addEdge(41, 42), logic_error);
	directed_matrix.addVertex(42);
	directed_matrix.addVertex(43);
	directed_matrix.addVertex(44);
	directed_matrix.addVertex(45);
	directed_matrix.addVertex(46);
	directed_matrix.addVertex(47);
	directed_matrix.addEdge(42, 43);
	directed_matrix.addEdge(43, 42);
	directed_matrix.addEdge(44, 45);
	directed_matrix.addEdge(45, 46);
	directed_matrix.addEdge(42, 42);
	directed_matrix.addEdge(47, 43);
	directed_matrix.addEdge(46, 44);
	EXPECT_THROW(directed_matrix.addEdge(42, 41), logic_error); // no dest vertex '41'
	EXPECT_THROW(directed_matrix.addEdge(41, 43), logic_error); // no src vertex '41'
	EXPECT_THROW(directed_matrix.addEdge(42, 42), logic_error); // already exists


	EXPECT_THROW(undirected_matrix.addEdge(41, 42), logic_error);
	undirected_matrix.addVertex(42);
	undirected_matrix.addVertex(43);
	undirected_matrix.addVertex(44);
	undirected_matrix.addVertex(45);
	undirected_matrix.addVertex(46);
	undirected_matrix.addVertex(47);
	undirected_matrix.addEdge(42, 43);
	undirected_matrix.addEdge(44, 45);
	undirected_matrix.addEdge(45, 46);
	undirected_matrix.addEdge(42, 42);
	undirected_matrix.addEdge(47, 43);
	undirected_matrix.addEdge(46, 44);
	EXPECT_THROW(undirected_matrix.addEdge(42, 41), logic_error); // no dest vertex '41'
	EXPECT_THROW(undirected_matrix.addEdge(41, 43), logic_error); // no src vertex '41'
	EXPECT_THROW(undirected_matrix.addEdge(42, 42), logic_error); // already exists
	EXPECT_THROW(undirected_matrix.addEdge(43, 42), logic_error); // it has been added the other way around, but as the graph is undirected, it already exists
}

TEST_F(AdjacencyMatrixTest, deleteEdge) {
	EXPECT_THROW(directed_matrix.deleteEdge(42, 41), logic_error);
	directed_matrix.addVertex(42);
	directed_matrix.addVertex(43);
	directed_matrix.addVertex(44);
	directed_matrix.addVertex(45);
	directed_matrix.addVertex(46);
	directed_matrix.addVertex(47);
	EXPECT_THROW(undirected_matrix.deleteEdge(42, 43), logic_error); // no such edge
	EXPECT_THROW(directed_matrix.deleteEdge(42, 41), logic_error); // no such vertex '41'
	EXPECT_THROW(directed_matrix.deleteEdge(41, 43), logic_error); // idem
	directed_matrix.addEdge(42, 43);
	EXPECT_THROW(directed_matrix.deleteEdge(43, 42), logic_error); // no such edge
	directed_matrix.addEdge(43, 42);
	directed_matrix.deleteEdge(42, 43);
	directed_matrix.deleteEdge(43, 42);
	EXPECT_THROW(directed_matrix.deleteEdge(42, 43), logic_error); // no such edge
	EXPECT_THROW(directed_matrix.deleteEdge(43, 42), logic_error); // no such edge


	EXPECT_THROW(undirected_matrix.deleteEdge(42, 41), logic_error);
	undirected_matrix.addVertex(42);
	undirected_matrix.addVertex(43);
	undirected_matrix.addVertex(44);
	undirected_matrix.addVertex(45);
	undirected_matrix.addVertex(46);
	undirected_matrix.addVertex(47);
	EXPECT_THROW(undirected_matrix.deleteEdge(42, 41), logic_error);
	EXPECT_THROW(undirected_matrix.deleteEdge(41, 43), logic_error);
	undirected_matrix.addEdge(42, 43);
	undirected_matrix.deleteEdge(43, 42); // should be fine: the graph is undirected
	undirected_matrix.addEdge(43, 42);
	undirected_matrix.deleteEdge(42, 43); // the other way around
	EXPECT_THROW(undirected_matrix.deleteEdge(42, 43), logic_error); // no longer exists
	EXPECT_THROW(undirected_matrix.deleteEdge(43, 42), logic_error); // idem

}

TEST_F(AdjacencyMatrixTest, hasEdge) {
	EXPECT_THROW(directed_matrix.addEdge(41, 42), logic_error);
	directed_matrix.addVertex(42);
	directed_matrix.addVertex(43);
	directed_matrix.addVertex(44);
	directed_matrix.addVertex(45);
	directed_matrix.addVertex(46);
	directed_matrix.addVertex(47);
	EXPECT_FALSE(directed_matrix.hasEdge(42, 43));
	directed_matrix.addEdge(42, 43);
	directed_matrix.addEdge(43, 42);
	directed_matrix.addEdge(44, 45);
	directed_matrix.addEdge(45, 46);
	directed_matrix.addEdge(42, 42);
	directed_matrix.addEdge(47, 43);
	directed_matrix.addEdge(46, 44);
	EXPECT_FALSE(directed_matrix.hasEdge(43, 44));
	EXPECT_TRUE(directed_matrix.hasEdge(42, 43));
	directed_matrix.addEdge(43, 44);
	EXPECT_TRUE(directed_matrix.hasEdge(43, 44));
	EXPECT_TRUE(directed_matrix.hasEdge(42, 43));
	directed_matrix.deleteEdge(42, 43);
	EXPECT_TRUE(directed_matrix.hasEdge(43, 42));
	EXPECT_FALSE(directed_matrix.hasEdge(42, 43));
	directed_matrix.deleteEdge(43, 42);
	EXPECT_FALSE(directed_matrix.hasEdge(43, 42));
	EXPECT_FALSE(directed_matrix.hasEdge(42, 43));
	EXPECT_TRUE(directed_matrix.hasEdge(46, 44));


	// tests of the undirected matrix are slightly different as the internal mechanisms are not the same at all
	EXPECT_THROW(undirected_matrix.addEdge(41, 42), logic_error);
	undirected_matrix.addVertex(42);
	undirected_matrix.addVertex(43);
	undirected_matrix.addVertex(44);
	undirected_matrix.addVertex(45);
	undirected_matrix.addVertex(46);
	undirected_matrix.addVertex(47);
	EXPECT_FALSE(undirected_matrix.hasEdge(42, 43));
	undirected_matrix.addEdge(42, 43);
	undirected_matrix.addEdge(42, 44);
	undirected_matrix.addEdge(42, 46);
	undirected_matrix.addEdge(43, 44);
	undirected_matrix.addEdge(43, 45);
	undirected_matrix.addEdge(43, 46);
	undirected_matrix.addEdge(43, 47);
	undirected_matrix.addEdge(44, 45);
	undirected_matrix.addEdge(44, 47);
	EXPECT_TRUE(undirected_matrix.hasEdge(42, 43));
	EXPECT_TRUE(undirected_matrix.hasEdge(42, 44));
	EXPECT_TRUE(undirected_matrix.hasEdge(42, 46));
	EXPECT_TRUE(undirected_matrix.hasEdge(43, 42));
	EXPECT_TRUE(undirected_matrix.hasEdge(43, 44));
	EXPECT_TRUE(undirected_matrix.hasEdge(43, 45));
	EXPECT_TRUE(undirected_matrix.hasEdge(43, 46));
	EXPECT_TRUE(undirected_matrix.hasEdge(43, 47));
	EXPECT_TRUE(undirected_matrix.hasEdge(44, 43));
	EXPECT_TRUE(undirected_matrix.hasEdge(42, 44));
	EXPECT_TRUE(undirected_matrix.hasEdge(44, 42));
	EXPECT_TRUE(undirected_matrix.hasEdge(44, 45));
	EXPECT_TRUE(undirected_matrix.hasEdge(44, 47));
	undirected_matrix.deleteEdge(44, 43);
	EXPECT_TRUE(undirected_matrix.hasEdge(42, 43));
	EXPECT_TRUE(undirected_matrix.hasEdge(44, 42));
	EXPECT_FALSE(undirected_matrix.hasEdge(43, 44));
	undirected_matrix.deleteVertex(43);
	EXPECT_THROW(undirected_matrix.addEdge(42, 43), logic_error);
	EXPECT_THROW(undirected_matrix.addEdge(43, 44), logic_error);
	EXPECT_TRUE(undirected_matrix.hasEdge(42, 44));
	EXPECT_TRUE(undirected_matrix.hasEdge(42, 46));
	EXPECT_TRUE(undirected_matrix.hasEdge(42, 44));
	EXPECT_TRUE(undirected_matrix.hasEdge(44, 42));
	EXPECT_TRUE(undirected_matrix.hasEdge(44, 45));
	EXPECT_TRUE(undirected_matrix.hasEdge(44, 47));
}

//TEST_F(AdjacencyMatrixTest, display) {
//	cout << matrix;
//	addVertices(6, 42);
//	cout << matrix;
//	matrix.addEdge(42, 43);
//	matrix.addEdge(42, 45);
//	matrix.addEdge(43, 46);
//	matrix.addEdge(43, 42);
//	matrix.addEdge(46, 45);
//	matrix.addEdge(46, 42);
//	matrix.addEdge(47, 42);
//	matrix.addEdge(47, 43);
//	matrix.addEdge(47, 44);
//	matrix.addEdge(47, 45);
//	matrix.addEdge(47, 46);
//	matrix.addEdge(47, 47);
//	cout << matrix;
//}

TEST_F(AdjacencyMatrixTest, CopyConstructor) {
	Adjacency_Matrix<int>	copy(directed_matrix);

	EXPECT_TRUE(copy.nbVertices() == 0);
	EXPECT_TRUE(copy.nbEdges() == 0);
	directed_matrix.addVertex(42);
	directed_matrix.addVertex(43);
	directed_matrix.addVertex(44);
	directed_matrix.addVertex(45);
	directed_matrix.addVertex(46);
	directed_matrix.addVertex(47);
	directed_matrix.addEdge(42, 42);
	directed_matrix.addEdge(42, 43);
	directed_matrix.addEdge(43, 46);
	directed_matrix.addEdge(43, 47);
	directed_matrix.addEdge(46, 43);
	EXPECT_TRUE(directed_matrix.nbVertices() == 6);

	Adjacency_Matrix<int>	copy2(directed_matrix);
	vector<int> vertices = copy2.vertices();
	vector<int>::const_iterator found;

	EXPECT_EQ(directed_matrix.nbVertices(), copy2.nbVertices());
	for (int i = 42; i < 48; i++) {
		// each of the concerned vertices should be in the vector
		found = std::find(vertices.begin(), vertices.end(), i);
		EXPECT_NE(found, vertices.end());
	}
	EXPECT_TRUE(copy2.nbEdges() == 5);
	EXPECT_TRUE(copy2.hasEdge(42, 42));
	EXPECT_TRUE(copy2.hasEdge(42, 43));
	EXPECT_TRUE(copy2.hasEdge(43, 46));
	EXPECT_TRUE(copy2.hasEdge(43, 47));
	EXPECT_TRUE(copy2.hasEdge(46, 43));


	Adjacency_Matrix<int>	copy3(undirected_matrix);

	EXPECT_TRUE(copy3.nbVertices() == 0);
	EXPECT_TRUE(copy3.nbEdges() == 0);
	undirected_matrix.addVertex(42);
	undirected_matrix.addVertex(43);
	undirected_matrix.addVertex(44);
	undirected_matrix.addVertex(45);
	undirected_matrix.addVertex(46);
	undirected_matrix.addVertex(47);
	undirected_matrix.addEdge(42, 42);
	undirected_matrix.addEdge(42, 43);
	undirected_matrix.addEdge(43, 46);
	undirected_matrix.addEdge(43, 47);
	EXPECT_TRUE(undirected_matrix.nbVertices() == 6);
	EXPECT_TRUE(undirected_matrix.hasEdge(46, 43));
	EXPECT_TRUE(undirected_matrix.hasEdge(47, 43));

	Adjacency_Matrix<int>	copy4(undirected_matrix);
	vertices = copy4.vertices();

	EXPECT_EQ(undirected_matrix.nbVertices(), copy4.nbVertices());
	EXPECT_EQ(vertices.size(), copy4.nbVertices());
	for (int i = 42; i < 48; i++) {
		// each of the concerned vertices should be in the vector
		found = std::find(vertices.begin(), vertices.end(), i);
		EXPECT_NE(found, vertices.end());
	}
	EXPECT_TRUE(copy4.nbEdges() == 4);
	EXPECT_TRUE(copy4.hasEdge(42, 42));
	EXPECT_TRUE(copy4.hasEdge(42, 43));
	EXPECT_TRUE(copy4.hasEdge(43, 46));
	EXPECT_TRUE(copy4.hasEdge(43, 47));
}

TEST_F(AdjacencyMatrixTest, AssignmentOperator) {
	// from empty matrix to empty matrix
	Adjacency_Matrix<int>	copy;

	EXPECT_TRUE(directed_matrix.nbVertices() == 0);
	EXPECT_TRUE(directed_matrix.nbEdges() == 0);
	// empty matrix = empty matrix
	copy = directed_matrix;
	EXPECT_TRUE(copy.nbVertices() == 0);
	EXPECT_TRUE(copy.nbEdges() == 0);

	// empty matrix = full matrix
	directed_matrix.addVertex(42);
	directed_matrix.addVertex(43);
	directed_matrix.addVertex(44);
	directed_matrix.addVertex(45);
	directed_matrix.addVertex(46);
	directed_matrix.addVertex(47);
	directed_matrix.addEdge(42, 43);
	directed_matrix.addEdge(42, 45);
	directed_matrix.addEdge(43, 46);

	copy = directed_matrix;
	EXPECT_TRUE(copy == directed_matrix); // testing the == operator overloading at the same time :)

	// full matrix = full matrix
	Adjacency_Matrix<int>	copy2;
	vector<int> vertices;
	vector<pair<int, int> > edges;

	copy = copy2;
	EXPECT_TRUE(copy == copy2);

	// full matrix = full matrix pt. 2
	copy = directed_matrix;
	directed_matrix.addVertex(1);
	directed_matrix.addVertex(2);
	directed_matrix.addEdge(46, 45);
	directed_matrix.addEdge(46, 42);
	copy = directed_matrix;
	EXPECT_TRUE(copy == directed_matrix);
}


