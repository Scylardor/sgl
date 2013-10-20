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
	Adjacency_Matrix<int> matrix;

protected:
	void addVertices(int nbr, int p_from);
};

void AdjacencyMatrixTest::addVertices(int p_nbr, int p_from) {
	for (int i = 0; i < p_nbr; i++) {
		matrix.addVertex(p_from);
		p_from++;
	}
}

TEST_F(AdjacencyMatrixTest, constructor) {
	EXPECT_EQ((int)matrix.nbVertices(), 0);
	EXPECT_EQ((int)matrix.nbEdges(), 0);
}

TEST_F(AdjacencyMatrixTest, LogicOnEmptymatrix) {
	EXPECT_THROW(matrix.deleteEdge(42, 21), logic_error);
	EXPECT_THROW(matrix.deleteVertex(42), logic_error);
	EXPECT_THROW(matrix.hasEdge(42, 21), logic_error);
	EXPECT_THROW(matrix.vertexInDegree(42), logic_error);
	EXPECT_THROW(matrix.vertexOutDegree(42), logic_error);
	EXPECT_THROW(matrix.vertexNeighborhood(42), logic_error);
}

TEST_F(AdjacencyMatrixTest, addVertex) {
	matrix.addVertex(42);
	EXPECT_THROW(matrix.addVertex(42), logic_error);
	matrix.addVertex(21);
}

TEST_F(AdjacencyMatrixTest, deleteVertex) {
	matrix.addVertex(42);
	EXPECT_THROW(matrix.deleteVertex(41), logic_error);
	matrix.deleteVertex(42);
	EXPECT_THROW(matrix.deleteVertex(42), logic_error);
}

TEST_F(AdjacencyMatrixTest, hasVertex) {
	EXPECT_FALSE(matrix.hasVertex(42));
	matrix.addVertex(42);
	EXPECT_TRUE(matrix.hasVertex(42));
	matrix.deleteVertex(42);
	EXPECT_FALSE(matrix.hasVertex(42));
	addVertices(2, 42);
	EXPECT_TRUE(matrix.hasVertex(42));
	EXPECT_TRUE(matrix.hasVertex(43));
}

TEST_F(AdjacencyMatrixTest, vertexInDegree) {
	matrix.addVertex(42);
	EXPECT_EQ((int)matrix.vertexInDegree(42), 0);
	matrix.addVertex(21);
	matrix.addEdge(21, 42);
	EXPECT_EQ((int)matrix.vertexInDegree(42), 1);
	matrix.addVertex(84);
	matrix.addEdge(84, 42);
	EXPECT_EQ((int)matrix.vertexInDegree(42), 2);
	matrix.deleteVertex(84);
	EXPECT_EQ((int)matrix.vertexInDegree(42), 1);
	matrix.deleteVertex(21);
	EXPECT_EQ((int)matrix.vertexInDegree(42), 0);
	matrix.deleteVertex(42);
	EXPECT_THROW(matrix.vertexInDegree(42), logic_error);
}

TEST_F(AdjacencyMatrixTest, vertexOutDegree) {
	matrix.addVertex(42);
	EXPECT_EQ((int)matrix.vertexOutDegree(42), 0);
	matrix.addVertex(21);
	matrix.addEdge(42, 21);
	EXPECT_EQ((int)matrix.vertexOutDegree(42), 1);
	matrix.addVertex(84);
	matrix.addEdge(42, 84);
	EXPECT_EQ((int)matrix.vertexOutDegree(42), 2);
	matrix.deleteVertex(84);
	EXPECT_EQ((int)matrix.vertexOutDegree(42), 1);
	matrix.deleteVertex(21);
	EXPECT_EQ((int)matrix.vertexOutDegree(42), 0);
	matrix.deleteVertex(42);
	EXPECT_THROW(matrix.vertexOutDegree(42), logic_error);
}

TEST_F(AdjacencyMatrixTest, vertexIsSource) {
	EXPECT_THROW(matrix.vertexIsSource(42), logic_error);
	matrix.addVertex(42);
	EXPECT_TRUE(matrix.vertexIsSource(42));
	matrix.addVertex(21);
	matrix.addEdge(21, 42);
	EXPECT_FALSE(matrix.vertexIsSource(42));
	matrix.deleteVertex(21);
	EXPECT_TRUE(matrix.vertexIsSource(42));
	matrix.addVertex(21);
	matrix.addEdge(42, 21);
	EXPECT_TRUE(matrix.vertexIsSource(42));
}

TEST_F(AdjacencyMatrixTest, vertexIsSink) {
	EXPECT_THROW(matrix.vertexIsSink(42), logic_error);
	matrix.addVertex(42);
	EXPECT_TRUE(matrix.vertexIsSink(42));
	matrix.addVertex(21);
	matrix.addEdge(21, 42);
	EXPECT_TRUE(matrix.vertexIsSink(42));
	matrix.deleteVertex(21);
	EXPECT_TRUE(matrix.vertexIsSink(42));
	matrix.addVertex(21);
	matrix.addEdge(42, 21);
	EXPECT_FALSE(matrix.vertexIsSink(42));
}

TEST_F(AdjacencyMatrixTest, vertexNeighborhood) {
	addVertices(6, 42);
	// Two edges coming to 42
	matrix.addEdge(43, 42);
	matrix.addEdge(44, 42);
	// Two edges coming from 42
	matrix.addEdge(42, 44);
	matrix.addEdge(42, 45);

	vector<int> neighbors = matrix.vertexNeighborhood(42);
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
	neighbors = matrix.vertexNeighborhood(42, true);
	for (unsigned i = 0; i < neighbors.size(); i++) cout << neighbors[i] << endl;
	EXPECT_EQ((int)neighbors.size(), 4);
	for (int i = 42; i < 46; i++) {
		// each of the concerned vertices should be in the vector
		found = std::find(neighbors.begin(), neighbors.end(), i);
		EXPECT_NE(found, neighbors.end());
	}
	// Vertices which aren't in 42's neighborhood shouldn't be in the vector
	matrix.addEdge(46, 43);
	found = std::find(neighbors.begin(), neighbors.end(), 46);
	EXPECT_EQ(found, neighbors.end());
	found = std::find(neighbors.begin(), neighbors.end(), 47);
	EXPECT_EQ(found, neighbors.end());
}

TEST_F(AdjacencyMatrixTest, vertices) {
	vector<int> vertices = matrix.vertices();
	EXPECT_EQ((int)vertices.size(), 0);
	addVertices(6, 42);
	vertices = matrix.vertices();

	vector<int>::const_iterator found;

	EXPECT_EQ((int)vertices.size(), 6);
	for (int i = 42; i < 48; i++) {
		// each of the concerned vertices should be in the vector
		found = std::find(vertices.begin(), vertices.end(), i);
		EXPECT_NE(found, vertices.end());
	}
}

TEST_F(AdjacencyMatrixTest, addEdge) {
	EXPECT_THROW(matrix.addEdge(41, 42), logic_error);
	addVertices(2, 42);
	matrix.addEdge(42, 43);
	matrix.addEdge(43, 42);
	EXPECT_THROW(matrix.addEdge(42, 41), logic_error);
	EXPECT_THROW(matrix.addEdge(41, 43), logic_error);
}

TEST_F(AdjacencyMatrixTest, deleteEdge) {
	EXPECT_THROW(matrix.deleteEdge(42, 41), logic_error);
	addVertices(2, 42);
	EXPECT_THROW(matrix.deleteEdge(42, 41), logic_error);
	EXPECT_THROW(matrix.deleteEdge(41, 43), logic_error);
	matrix.addEdge(42, 43);
	EXPECT_THROW(matrix.deleteEdge(43, 42), logic_error);
	matrix.addEdge(43, 42);
	matrix.deleteEdge(42, 43);
	matrix.deleteEdge(43, 42);
	EXPECT_THROW(matrix.deleteEdge(42, 43), logic_error);
	EXPECT_THROW(matrix.deleteEdge(43, 42), logic_error);
}

TEST_F(AdjacencyMatrixTest, hasEdge) {
	EXPECT_THROW(matrix.addEdge(41, 42), logic_error);
	addVertices(2, 42);
	EXPECT_FALSE(matrix.hasEdge(42, 43));
	matrix.addEdge(42, 43);
	EXPECT_FALSE(matrix.hasEdge(43, 42));
	EXPECT_TRUE(matrix.hasEdge(42, 43));
	matrix.addEdge(43, 42);
	EXPECT_TRUE(matrix.hasEdge(43, 42));
	EXPECT_TRUE(matrix.hasEdge(42, 43));
	matrix.deleteEdge(42, 43);
	EXPECT_TRUE(matrix.hasEdge(43, 42));
	EXPECT_FALSE(matrix.hasEdge(42, 43));
	matrix.deleteEdge(43, 42);
	EXPECT_FALSE(matrix.hasEdge(43, 42));
	EXPECT_FALSE(matrix.hasEdge(42, 43));
}

TEST_F(AdjacencyMatrixTest, display) {
	cout << matrix;
	addVertices(6, 42);
	cout << matrix;
	matrix.addEdge(42, 43);
	matrix.addEdge(42, 45);
	matrix.addEdge(43, 46);
	matrix.addEdge(43, 42);
	matrix.addEdge(46, 45);
	matrix.addEdge(46, 42);
	matrix.addEdge(47, 42);
	matrix.addEdge(47, 43);
	matrix.addEdge(47, 44);
	matrix.addEdge(47, 45);
	matrix.addEdge(47, 46);
	matrix.addEdge(47, 47);
	cout << matrix;
}

TEST_F(AdjacencyMatrixTest, CopyConstructor) {
	Adjacency_Matrix<int>	copy(matrix);

	EXPECT_EQ((int)copy.nbVertices(), 0);
	EXPECT_EQ((int)copy.nbEdges(), 0);

	addVertices(6, 42);
	EXPECT_EQ((int)matrix.nbVertices(), 6);

	Adjacency_Matrix<int>	copy2(matrix);
	vector<int> vertices = copy2.vertices();
	vector<int>::const_iterator found;

	EXPECT_EQ(matrix.nbVertices(), copy2.nbVertices());
	for (int i = 42; i < 48; i++) {
		// each of the concerned vertices should be in the vector
		found = std::find(vertices.begin(), vertices.end(), i);
		EXPECT_NE(found, vertices.end());
	}
}

TEST_F(AdjacencyMatrixTest, AssignmentOperator) {
	// from empty matrix to empty matrix
	Adjacency_Matrix<int>	copy;

	EXPECT_EQ((int)matrix.nbVertices(), 0);
	EXPECT_EQ((int)matrix.nbEdges(), 0);
	copy = matrix;
	EXPECT_EQ((int)copy.nbVertices(), 0);
	EXPECT_EQ((int)copy.nbEdges(), 0);

	// from full matrix to empty matrix
	addVertices(6, 42);
	matrix.addEdge(42, 43);
	matrix.addEdge(42, 45);
	matrix.addEdge(43, 46);

	copy = matrix;
	EXPECT_TRUE(matrix == copy);

	// from empty matrix to full matrix
	Adjacency_Matrix<int>	copy2;

	copy = copy2;
	EXPECT_TRUE(copy == copy2);

	// from full matrix to full matrix
	copy = matrix;
	addVertices(2, 1);
	matrix.addEdge(46, 45);
	matrix.addEdge(46, 42);
	copy = matrix;
	EXPECT_TRUE(copy == matrix);
}


