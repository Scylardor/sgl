/*
 * tests_adjacency_matrix.cpp
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
	adjacency_matrix<int, 3> directed_matrix;
	adjacency_matrix<int, 3> undirected_matrix;
};

AdjacencyMatrixTest::AdjacencyMatrixTest() : directed_matrix(), undirected_matrix(UNDIRECTED) {}

TEST_F(AdjacencyMatrixTest, constructor) {
	EXPECT_TRUE(directed_matrix.nb_vertices() == 0);
	EXPECT_TRUE(directed_matrix.nb_edges() == 0);

	EXPECT_TRUE(undirected_matrix.nb_vertices() == 0);
	EXPECT_TRUE(undirected_matrix.nb_edges() == 0);
}

TEST_F(AdjacencyMatrixTest, LogicOnEmptyMatrix) {
	EXPECT_THROW(directed_matrix.delete_edge(42, 21), logic_error);
	EXPECT_THROW(directed_matrix.delete_vertex(42), logic_error);
	EXPECT_THROW(directed_matrix.has_edge(42, 21), logic_error);
	EXPECT_THROW(directed_matrix.vertex_in_degree(42), logic_error);
	EXPECT_THROW(directed_matrix.vertex_out_degree(42), logic_error);
	EXPECT_THROW(directed_matrix.vertex_neighborhood(42), logic_error);

	EXPECT_THROW(undirected_matrix.delete_edge(42, 21), logic_error);
	EXPECT_THROW(undirected_matrix.delete_vertex(42), logic_error);
	EXPECT_THROW(undirected_matrix.has_edge(42, 21), logic_error);
	EXPECT_THROW(undirected_matrix.vertex_in_degree(42), logic_error);
	EXPECT_THROW(undirected_matrix.vertex_out_degree(42), logic_error);
	EXPECT_THROW(undirected_matrix.vertex_neighborhood(42), logic_error);
}

TEST_F(AdjacencyMatrixTest, add_vertex) {
	directed_matrix.add_vertex(42);
	EXPECT_TRUE(directed_matrix.nb_vertices() == 1);
	EXPECT_THROW(directed_matrix.add_vertex(42), logic_error);
	directed_matrix.add_vertex(21);
	directed_matrix.add_vertex(34);
	EXPECT_TRUE(directed_matrix.nb_vertices() == 3);
	EXPECT_THROW(directed_matrix.add_vertex(42), logic_error);
	EXPECT_THROW(directed_matrix.add_vertex(21), logic_error);
	EXPECT_THROW(directed_matrix.add_vertex(34), logic_error);

	undirected_matrix.add_vertex(42);
	EXPECT_TRUE(undirected_matrix.nb_vertices() == 1);
	EXPECT_THROW(undirected_matrix.add_vertex(42), logic_error);
	undirected_matrix.add_vertex(21);
	undirected_matrix.add_vertex(34);
	EXPECT_TRUE(undirected_matrix.nb_vertices() == 3);
	EXPECT_THROW(undirected_matrix.add_vertex(42), logic_error);
	EXPECT_THROW(undirected_matrix.add_vertex(21), logic_error);
	EXPECT_THROW(undirected_matrix.add_vertex(34), logic_error);
}

TEST_F(AdjacencyMatrixTest, delete_vertex) {
	directed_matrix.add_vertex(42);
	EXPECT_THROW(directed_matrix.delete_vertex(41), logic_error);
	directed_matrix.delete_vertex(42);
	EXPECT_TRUE(directed_matrix.nb_vertices() == 0);
	EXPECT_THROW(directed_matrix.delete_vertex(42), logic_error);
	directed_matrix.add_vertex(21);
	directed_matrix.add_vertex(42);
	directed_matrix.add_vertex(84);
	directed_matrix.delete_vertex(21);
	EXPECT_TRUE(directed_matrix.nb_vertices() == 2);
	directed_matrix.add_vertex(21);
	directed_matrix.delete_vertex(42);
	EXPECT_TRUE(directed_matrix.nb_vertices() == 2);
	directed_matrix.add_vertex(42);
	directed_matrix.delete_vertex(84);
	directed_matrix.delete_vertex(42);
	directed_matrix.delete_vertex(21);
	EXPECT_TRUE(directed_matrix.nb_vertices() == 0);

	undirected_matrix.add_vertex(42);
	EXPECT_THROW(undirected_matrix.delete_vertex(41), logic_error);
	undirected_matrix.delete_vertex(42);
	EXPECT_TRUE(directed_matrix.nb_vertices() == 0);
	EXPECT_THROW(undirected_matrix.delete_vertex(42), logic_error);
	undirected_matrix.add_vertex(21);
	undirected_matrix.add_vertex(42);
	undirected_matrix.add_vertex(84);
	undirected_matrix.delete_vertex(21);
	EXPECT_TRUE(undirected_matrix.nb_vertices() == 2);
	undirected_matrix.add_vertex(21);
	undirected_matrix.delete_vertex(42);
	EXPECT_TRUE(undirected_matrix.nb_vertices() == 2);
	undirected_matrix.add_vertex(42);
	undirected_matrix.delete_vertex(84);
	undirected_matrix.delete_vertex(42);
	undirected_matrix.delete_vertex(21);
	EXPECT_TRUE(undirected_matrix.nb_vertices() == 0);
}

TEST_F(AdjacencyMatrixTest, has_vertex) {
	EXPECT_FALSE(directed_matrix.has_vertex(42));
	directed_matrix.add_vertex(42);
	EXPECT_TRUE(directed_matrix.has_vertex(42));
	directed_matrix.delete_vertex(42);
	EXPECT_FALSE(directed_matrix.has_vertex(42));
	directed_matrix.add_vertex(21);
	directed_matrix.add_vertex(42);
	EXPECT_TRUE(directed_matrix.has_vertex(21));
	EXPECT_TRUE(directed_matrix.has_vertex(42));

	EXPECT_FALSE(undirected_matrix.has_vertex(42));
	undirected_matrix.add_vertex(42);
	EXPECT_TRUE(undirected_matrix.has_vertex(42));
	undirected_matrix.delete_vertex(42);
	EXPECT_FALSE(undirected_matrix.has_vertex(42));
	undirected_matrix.add_vertex(21);
	undirected_matrix.add_vertex(42);
	EXPECT_TRUE(undirected_matrix.has_vertex(21));
	EXPECT_TRUE(undirected_matrix.has_vertex(42));
}

TEST_F(AdjacencyMatrixTest, vertex_in_degree) {
	directed_matrix.add_vertex(42);
	EXPECT_TRUE(directed_matrix.vertex_in_degree(42) == 0);
	directed_matrix.add_vertex(21);
	directed_matrix.add_edge(21, 42);
	EXPECT_TRUE(directed_matrix.vertex_in_degree(42) == 1);
	directed_matrix.add_vertex(84);
	directed_matrix.add_edge(84, 42);
	EXPECT_TRUE(directed_matrix.vertex_in_degree(42) == 2);
	directed_matrix.add_edge(42, 42);
	EXPECT_TRUE(directed_matrix.vertex_in_degree(42) == 3);
	directed_matrix.delete_vertex(84);
	EXPECT_TRUE(directed_matrix.vertex_in_degree(42) == 2);
	directed_matrix.delete_vertex(21);
	EXPECT_TRUE(directed_matrix.vertex_in_degree(42) == 1);
	directed_matrix.delete_vertex(42);
	EXPECT_THROW(directed_matrix.vertex_in_degree(42), logic_error);

	undirected_matrix.add_vertex(42);
	EXPECT_TRUE(undirected_matrix.vertex_in_degree(42) == 0);
	undirected_matrix.add_vertex(21);
	undirected_matrix.add_edge(21, 42);
	EXPECT_TRUE(undirected_matrix.vertex_in_degree(42) == 1);
	EXPECT_TRUE(undirected_matrix.vertex_in_degree(21) == 1);
	undirected_matrix.add_vertex(84);
	undirected_matrix.add_edge(84, 42);
	EXPECT_TRUE(undirected_matrix.vertex_in_degree(42) == 2);
	EXPECT_TRUE(undirected_matrix.vertex_in_degree(84) == 1);
	undirected_matrix.add_edge(42, 42);
	EXPECT_TRUE(undirected_matrix.vertex_in_degree(42) == 4);
	undirected_matrix.delete_vertex(84);
	EXPECT_TRUE(undirected_matrix.vertex_in_degree(42) == 3);
	undirected_matrix.delete_vertex(21);
	EXPECT_TRUE(undirected_matrix.vertex_in_degree(42) == 2);
	undirected_matrix.delete_vertex(42);
	EXPECT_THROW(undirected_matrix.vertex_in_degree(42), logic_error);
}

TEST_F(AdjacencyMatrixTest, vertex_out_degree) {
	directed_matrix.add_vertex(42);
	EXPECT_TRUE(directed_matrix.vertex_out_degree(42) == 0);
	directed_matrix.add_vertex(21);
	directed_matrix.add_edge(42, 21);
	EXPECT_TRUE(directed_matrix.vertex_out_degree(42) == 1);
	directed_matrix.add_vertex(84);
	directed_matrix.add_edge(42, 84);
	EXPECT_TRUE(directed_matrix.vertex_out_degree(42) == 2);
	directed_matrix.add_edge(42, 42);
	EXPECT_TRUE(directed_matrix.vertex_out_degree(42) == 3);
	directed_matrix.delete_vertex(84);
	EXPECT_TRUE(directed_matrix.vertex_out_degree(42) == 2);
	directed_matrix.delete_vertex(21);
	EXPECT_TRUE(directed_matrix.vertex_out_degree(42) == 1);
	directed_matrix.delete_vertex(42);
	EXPECT_THROW(directed_matrix.vertex_out_degree(42), logic_error);

	undirected_matrix.add_vertex(42);
	EXPECT_TRUE(undirected_matrix.vertex_out_degree(42) == 0);
	undirected_matrix.add_vertex(21);
	undirected_matrix.add_edge(42, 21);
	EXPECT_TRUE(undirected_matrix.vertex_out_degree(42) == 1);
	EXPECT_TRUE(undirected_matrix.vertex_out_degree(21) == 1);
	undirected_matrix.add_vertex(84);
	undirected_matrix.add_edge(42, 84);
	EXPECT_TRUE(undirected_matrix.vertex_out_degree(42) == 2);
	EXPECT_TRUE(undirected_matrix.vertex_out_degree(84) == 1);
	undirected_matrix.add_edge(42, 42);
	EXPECT_TRUE(undirected_matrix.vertex_out_degree(42) == 4);
	undirected_matrix.delete_vertex(84);
	EXPECT_TRUE(undirected_matrix.vertex_out_degree(42) == 3);
	undirected_matrix.delete_vertex(21);
	EXPECT_TRUE(undirected_matrix.vertex_out_degree(42) == 2);
	undirected_matrix.delete_vertex(42);
	EXPECT_THROW(undirected_matrix.vertex_out_degree(42), logic_error);
}

TEST_F(AdjacencyMatrixTest, vertex_is_source) {
	EXPECT_THROW(directed_matrix.vertex_is_source(42), logic_error);
	directed_matrix.add_vertex(42);
	EXPECT_TRUE(directed_matrix.vertex_is_source(42));
	directed_matrix.add_vertex(21);
	directed_matrix.add_edge(21, 42);
	EXPECT_FALSE(directed_matrix.vertex_is_source(42));
	directed_matrix.delete_vertex(21);
	EXPECT_TRUE(directed_matrix.vertex_is_source(42));
	directed_matrix.add_vertex(21);
	directed_matrix.add_edge(42, 21);
	EXPECT_TRUE(directed_matrix.vertex_is_source(42));
	directed_matrix.add_edge(42, 42);
	EXPECT_FALSE(directed_matrix.vertex_is_source(42));

	// it has no sense to search a source in an undirected graph !
	EXPECT_THROW(undirected_matrix.vertex_is_source(42), logic_error);
	undirected_matrix.add_vertex(42);
	EXPECT_THROW(undirected_matrix.vertex_is_source(42), logic_error);
	undirected_matrix.add_vertex(21);
	undirected_matrix.add_edge(21, 42);
	EXPECT_THROW(undirected_matrix.vertex_is_source(42), logic_error);
}

TEST_F(AdjacencyMatrixTest, vertex_is_sink) {
	EXPECT_THROW(directed_matrix.vertex_is_sink(42), logic_error);
	directed_matrix.add_vertex(42);
	EXPECT_TRUE(directed_matrix.vertex_is_sink(42));
	directed_matrix.add_vertex(21);
	directed_matrix.add_edge(21, 42);
	EXPECT_TRUE(directed_matrix.vertex_is_sink(42));
	directed_matrix.delete_vertex(21);
	EXPECT_TRUE(directed_matrix.vertex_is_sink(42));
	directed_matrix.add_vertex(21);
	directed_matrix.add_edge(42, 21);
	EXPECT_FALSE(directed_matrix.vertex_is_sink(42));

	// it has no sense to search a sink in an undirected graph !
	EXPECT_THROW(undirected_matrix.vertex_is_sink(42), logic_error);
	undirected_matrix.add_vertex(42);
	EXPECT_THROW(undirected_matrix.vertex_is_sink(42), logic_error);
	undirected_matrix.add_vertex(21);
	undirected_matrix.add_edge(21, 42);
	EXPECT_THROW(undirected_matrix.vertex_is_sink(42), logic_error);
}

TEST_F(AdjacencyMatrixTest, vertex_neighborhood) {
	directed_matrix.add_vertex(42);
	directed_matrix.add_vertex(43);
	directed_matrix.add_vertex(44);
	directed_matrix.add_vertex(45);
	directed_matrix.add_vertex(46);
	// Two edges coming to 42
	directed_matrix.add_edge(43, 42);
	directed_matrix.add_edge(44, 42);
	// Two edges coming from 42
	directed_matrix.add_edge(42, 43);
	directed_matrix.add_edge(42, 44);

	vector<int> neighbors = directed_matrix.vertex_neighborhood(42);
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
	neighbors = directed_matrix.vertex_neighborhood(42, true);
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

	directed_matrix.add_edge(42, 42);
	// if there is a loop on 42, it should be in its own neighborhood even when we don't want it closed
	EXPECT_TRUE(neighbors.size() == 3);
	found = std::find(neighbors.begin(), neighbors.end(), 42);
	EXPECT_NE(found, neighbors.end());


	undirected_matrix.add_vertex(42);
	undirected_matrix.add_vertex(43);
	undirected_matrix.add_vertex(44);
	undirected_matrix.add_vertex(45);
	undirected_matrix.add_vertex(46);
	// Two edges coming to 42
	undirected_matrix.add_edge(43, 42);
	undirected_matrix.add_edge(45, 42);
	// One coming from 42
	undirected_matrix.add_edge(42, 44);

	neighbors = undirected_matrix.vertex_neighborhood(42);

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
	neighbors = undirected_matrix.vertex_neighborhood(42, true);
	EXPECT_TRUE(neighbors.size() == 4);
	for (int i = 42; i < 46; i++) {
		// each of the concerned vertices should be in the vector
		found = std::find(neighbors.begin(), neighbors.end(), i);
		EXPECT_NE(found, neighbors.end());
	}
	// Vertices which aren't in 42's neighborhood shouldn't be in the vector
	found = std::find(neighbors.begin(), neighbors.end(), 46);
	EXPECT_EQ(found, neighbors.end());

	undirected_matrix.add_edge(42, 42);
	// if there is a loop on 42, it should be in its own neighborhood even when we don't want it closed
	EXPECT_TRUE(neighbors.size() == 4);
	found = std::find(neighbors.begin(), neighbors.end(), 42);
	EXPECT_NE(found, neighbors.end());
}

TEST_F(AdjacencyMatrixTest, vertices) {
	vector<int> vertices = directed_matrix.vertices();

	EXPECT_TRUE(vertices.size() == 0);
	directed_matrix.add_vertex(42);
	directed_matrix.add_vertex(43);
	directed_matrix.add_vertex(44);
	directed_matrix.add_vertex(45);
	directed_matrix.add_vertex(46);
	directed_matrix.add_vertex(47);
	vertices = directed_matrix.vertices();
	EXPECT_TRUE(vertices.size() == 6);
	for (int i = 42; i < 48; i++) {
		// each of the concerned vertices should be in the vector
		vector<int>::const_iterator found = std::find(vertices.begin(), vertices.end(), i);
		EXPECT_NE(found, vertices.end());
	}


	vertices = undirected_matrix.vertices();
	EXPECT_TRUE(vertices.size() == 0);
	undirected_matrix.add_vertex(42);
	undirected_matrix.add_vertex(43);
	undirected_matrix.add_vertex(44);
	undirected_matrix.add_vertex(45);
	undirected_matrix.add_vertex(46);
	undirected_matrix.add_vertex(47);
	vertices = undirected_matrix.vertices();
	EXPECT_TRUE(vertices.size() == 6);
	for (int i = 42; i < 48; i++) {
		// each of the concerned vertices should be in the vector
		vector<int>::const_iterator found = std::find(vertices.begin(), vertices.end(), i);
		EXPECT_NE(found, vertices.end());
	}
}

TEST_F(AdjacencyMatrixTest, add_edge) {
	EXPECT_THROW(directed_matrix.add_edge(41, 42), logic_error);
	directed_matrix.add_vertex(42);
	directed_matrix.add_vertex(43);
	directed_matrix.add_vertex(44);
	directed_matrix.add_vertex(45);
	directed_matrix.add_vertex(46);
	directed_matrix.add_vertex(47);
	directed_matrix.add_edge(42, 43);
	directed_matrix.add_edge(43, 42);
	directed_matrix.add_edge(44, 45);
	directed_matrix.add_edge(45, 46);
	directed_matrix.add_edge(42, 42);
	directed_matrix.add_edge(47, 43);
	directed_matrix.add_edge(46, 44);
	EXPECT_THROW(directed_matrix.add_edge(42, 41), logic_error); // no dest vertex '41'
	EXPECT_THROW(directed_matrix.add_edge(41, 43), logic_error); // no src vertex '41'
	EXPECT_THROW(directed_matrix.add_edge(42, 42), logic_error); // already exists


	EXPECT_THROW(undirected_matrix.add_edge(41, 42), logic_error);
	undirected_matrix.add_vertex(42);
	undirected_matrix.add_vertex(43);
	undirected_matrix.add_vertex(44);
	undirected_matrix.add_vertex(45);
	undirected_matrix.add_vertex(46);
	undirected_matrix.add_vertex(47);
	undirected_matrix.add_edge(42, 43);
	undirected_matrix.add_edge(44, 45);
	undirected_matrix.add_edge(45, 46);
	undirected_matrix.add_edge(42, 42);
	undirected_matrix.add_edge(47, 43);
	undirected_matrix.add_edge(46, 44);
	EXPECT_THROW(undirected_matrix.add_edge(42, 41), logic_error); // no dest vertex '41'
	EXPECT_THROW(undirected_matrix.add_edge(41, 43), logic_error); // no src vertex '41'
	EXPECT_THROW(undirected_matrix.add_edge(42, 42), logic_error); // already exists
	EXPECT_THROW(undirected_matrix.add_edge(43, 42), logic_error); // it has been added the other way around, but as the graph is undirected, it already exists
}

TEST_F(AdjacencyMatrixTest, delete_edge) {
	EXPECT_THROW(directed_matrix.delete_edge(42, 41), logic_error);
	directed_matrix.add_vertex(42);
	directed_matrix.add_vertex(43);
	directed_matrix.add_vertex(44);
	directed_matrix.add_vertex(45);
	directed_matrix.add_vertex(46);
	directed_matrix.add_vertex(47);
	EXPECT_THROW(directed_matrix.delete_edge(42, 43), logic_error); // no such edge
	EXPECT_THROW(directed_matrix.delete_edge(42, 41), logic_error); // no such vertex '41'
	EXPECT_THROW(directed_matrix.delete_edge(41, 43), logic_error); // idem
	directed_matrix.add_edge(42, 43);
	EXPECT_THROW(directed_matrix.delete_edge(43, 42), logic_error); // no such edge
	directed_matrix.add_edge(43, 42);
	directed_matrix.delete_edge(42, 43);
	directed_matrix.delete_edge(43, 42);
	EXPECT_THROW(directed_matrix.delete_edge(42, 43), logic_error); // no such edge
	EXPECT_THROW(directed_matrix.delete_edge(43, 42), logic_error); // no such edge


	EXPECT_THROW(undirected_matrix.delete_edge(42, 41), logic_error);
	undirected_matrix.add_vertex(42);
	undirected_matrix.add_vertex(43);
	undirected_matrix.add_vertex(44);
	undirected_matrix.add_vertex(45);
	undirected_matrix.add_vertex(46);
	undirected_matrix.add_vertex(47);
	EXPECT_THROW(undirected_matrix.delete_edge(42, 41), logic_error);
	EXPECT_THROW(undirected_matrix.delete_edge(41, 43), logic_error);
	undirected_matrix.add_edge(42, 43);
	undirected_matrix.delete_edge(43, 42); // should be fine: the graph is undirected
	undirected_matrix.add_edge(43, 42);
	undirected_matrix.delete_edge(42, 43); // the other way around
	EXPECT_THROW(undirected_matrix.delete_edge(42, 43), logic_error); // no longer exists
	EXPECT_THROW(undirected_matrix.delete_edge(43, 42), logic_error); // idem

}

TEST_F(AdjacencyMatrixTest, has_edge) {
	EXPECT_THROW(directed_matrix.add_edge(41, 42), logic_error);
	directed_matrix.add_vertex(42);
	directed_matrix.add_vertex(43);
	directed_matrix.add_vertex(44);
	directed_matrix.add_vertex(45);
	directed_matrix.add_vertex(46);
	directed_matrix.add_vertex(47);
	EXPECT_FALSE(directed_matrix.has_edge(42, 43));
	directed_matrix.add_edge(42, 43);
	directed_matrix.add_edge(43, 42);
	directed_matrix.add_edge(44, 45);
	directed_matrix.add_edge(45, 46);
	directed_matrix.add_edge(42, 42);
	directed_matrix.add_edge(47, 43);
	directed_matrix.add_edge(46, 44);
	EXPECT_FALSE(directed_matrix.has_edge(43, 44));
	EXPECT_TRUE(directed_matrix.has_edge(42, 43));
	directed_matrix.add_edge(43, 44);
	EXPECT_TRUE(directed_matrix.has_edge(43, 44));
	EXPECT_TRUE(directed_matrix.has_edge(42, 43));
	directed_matrix.delete_edge(42, 43);
	EXPECT_TRUE(directed_matrix.has_edge(43, 42));
	EXPECT_FALSE(directed_matrix.has_edge(42, 43));
	directed_matrix.delete_edge(43, 42);
	EXPECT_FALSE(directed_matrix.has_edge(43, 42));
	EXPECT_FALSE(directed_matrix.has_edge(42, 43));
	EXPECT_TRUE(directed_matrix.has_edge(46, 44));


	// tests of the undirected matrix are slightly different as the internal mechanisms are not the same at all
	EXPECT_THROW(undirected_matrix.add_edge(41, 42), logic_error);
	undirected_matrix.add_vertex(42);
	undirected_matrix.add_vertex(43);
	undirected_matrix.add_vertex(44);
	undirected_matrix.add_vertex(45);
	undirected_matrix.add_vertex(46);
	undirected_matrix.add_vertex(47);
	EXPECT_FALSE(undirected_matrix.has_edge(42, 43));
	undirected_matrix.add_edge(42, 43);
	undirected_matrix.add_edge(42, 44);
	undirected_matrix.add_edge(42, 46);
	undirected_matrix.add_edge(43, 44);
	undirected_matrix.add_edge(43, 45);
	undirected_matrix.add_edge(43, 46);
	undirected_matrix.add_edge(43, 47);
	undirected_matrix.add_edge(44, 45);
	undirected_matrix.add_edge(44, 47);
	EXPECT_TRUE(undirected_matrix.has_edge(42, 43));
	EXPECT_TRUE(undirected_matrix.has_edge(42, 44));
	EXPECT_TRUE(undirected_matrix.has_edge(42, 46));
	EXPECT_TRUE(undirected_matrix.has_edge(43, 42));
	EXPECT_TRUE(undirected_matrix.has_edge(43, 44));
	EXPECT_TRUE(undirected_matrix.has_edge(43, 45));
	EXPECT_TRUE(undirected_matrix.has_edge(43, 46));
	EXPECT_TRUE(undirected_matrix.has_edge(43, 47));
	EXPECT_TRUE(undirected_matrix.has_edge(44, 43));
	EXPECT_TRUE(undirected_matrix.has_edge(42, 44));
	EXPECT_TRUE(undirected_matrix.has_edge(44, 42));
	EXPECT_TRUE(undirected_matrix.has_edge(44, 45));
	EXPECT_TRUE(undirected_matrix.has_edge(44, 47));
	undirected_matrix.delete_edge(44, 43);
	EXPECT_TRUE(undirected_matrix.has_edge(42, 43));
	EXPECT_TRUE(undirected_matrix.has_edge(44, 42));
	EXPECT_FALSE(undirected_matrix.has_edge(43, 44));
	undirected_matrix.delete_vertex(43);
	EXPECT_THROW(undirected_matrix.add_edge(42, 43), logic_error);
	EXPECT_THROW(undirected_matrix.add_edge(43, 44), logic_error);
	EXPECT_TRUE(undirected_matrix.has_edge(42, 44));
	EXPECT_TRUE(undirected_matrix.has_edge(42, 46));
	EXPECT_TRUE(undirected_matrix.has_edge(42, 44));
	EXPECT_TRUE(undirected_matrix.has_edge(44, 42));
	EXPECT_TRUE(undirected_matrix.has_edge(44, 45));
	EXPECT_TRUE(undirected_matrix.has_edge(44, 47));
}

//TEST_F(AdjacencyMatrixTest, display) {
//	cout << matrix;
//	addVertices(6, 42);
//	cout << matrix;
//	matrix.add_edge(42, 43);
//	matrix.add_edge(42, 45);
//	matrix.add_edge(43, 46);
//	matrix.add_edge(43, 42);
//	matrix.add_edge(46, 45);
//	matrix.add_edge(46, 42);
//	matrix.add_edge(47, 42);
//	matrix.add_edge(47, 43);
//	matrix.add_edge(47, 44);
//	matrix.add_edge(47, 45);
//	matrix.add_edge(47, 46);
//	matrix.add_edge(47, 47);
//	cout << matrix;
//}

TEST_F(AdjacencyMatrixTest, CopyConstructor) {
	adjacency_matrix<int, 3>	copy(directed_matrix);

	EXPECT_TRUE(copy.nb_vertices() == 0);
	EXPECT_TRUE(copy.nb_edges() == 0);
	directed_matrix.add_vertex(42);
	directed_matrix.add_vertex(43);
	directed_matrix.add_vertex(44);
	directed_matrix.add_vertex(45);
	directed_matrix.add_vertex(46);
	directed_matrix.add_vertex(47);
	directed_matrix.add_edge(42, 42);
	directed_matrix.add_edge(42, 43);
	directed_matrix.add_edge(43, 46);
	directed_matrix.add_edge(43, 47);
	directed_matrix.add_edge(46, 43);
	EXPECT_TRUE(directed_matrix.nb_vertices() == 6);

	adjacency_matrix<int, 3>	copy2(directed_matrix);
	vector<int> vertices = copy2.vertices();
	vector<int>::const_iterator found;

	EXPECT_EQ(directed_matrix.nb_vertices(), copy2.nb_vertices());
	for (int i = 42; i < 48; i++) {
		// each of the concerned vertices should be in the vector
		found = std::find(vertices.begin(), vertices.end(), i);
		EXPECT_NE(found, vertices.end());
	}
	EXPECT_TRUE(copy2.nb_edges() == 5);
	EXPECT_TRUE(copy2.has_edge(42, 42));
	EXPECT_TRUE(copy2.has_edge(42, 43));
	EXPECT_TRUE(copy2.has_edge(43, 46));
	EXPECT_TRUE(copy2.has_edge(43, 47));
	EXPECT_TRUE(copy2.has_edge(46, 43));


	adjacency_matrix<int, 3>	copy3(undirected_matrix);

	EXPECT_TRUE(copy3.nb_vertices() == 0);
	EXPECT_TRUE(copy3.nb_edges() == 0);
	undirected_matrix.add_vertex(42);
	undirected_matrix.add_vertex(43);
	undirected_matrix.add_vertex(44);
	undirected_matrix.add_vertex(45);
	undirected_matrix.add_vertex(46);
	undirected_matrix.add_vertex(47);
	undirected_matrix.add_edge(42, 42);
	undirected_matrix.add_edge(42, 43);
	undirected_matrix.add_edge(43, 46);
	undirected_matrix.add_edge(43, 47);
	EXPECT_TRUE(undirected_matrix.nb_vertices() == 6);
	EXPECT_TRUE(undirected_matrix.has_edge(46, 43));
	EXPECT_TRUE(undirected_matrix.has_edge(47, 43));

	adjacency_matrix<int, 3>	copy4(undirected_matrix);
	vertices = copy4.vertices();

	EXPECT_EQ(undirected_matrix.nb_vertices(), copy4.nb_vertices());
	EXPECT_EQ(vertices.size(), copy4.nb_vertices());
	for (int i = 42; i < 48; i++) {
		// each of the concerned vertices should be in the vector
		found = std::find(vertices.begin(), vertices.end(), i);
		EXPECT_NE(found, vertices.end());
	}
	EXPECT_TRUE(copy4.nb_edges() == 4);
	EXPECT_TRUE(copy4.has_edge(42, 42));
	EXPECT_TRUE(copy4.has_edge(42, 43));
	EXPECT_TRUE(copy4.has_edge(43, 46));
	EXPECT_TRUE(copy4.has_edge(43, 47));
}

TEST_F(AdjacencyMatrixTest, AssignmentOperator) {
	// from empty matrix to empty matrix
	adjacency_matrix<int, 3>	copy;

	EXPECT_TRUE(directed_matrix.nb_vertices() == 0);
	EXPECT_TRUE(directed_matrix.nb_edges() == 0);
	// empty matrix = empty matrix
	copy = directed_matrix;
	EXPECT_TRUE(copy.nb_vertices() == 0);
	EXPECT_TRUE(copy.nb_edges() == 0);

	// empty matrix = full matrix
	directed_matrix.add_vertex(42);
	directed_matrix.add_vertex(43);
	directed_matrix.add_vertex(44);
	directed_matrix.add_vertex(45);
	directed_matrix.add_vertex(46);
	directed_matrix.add_vertex(47);
	directed_matrix.add_edge(42, 43);
	directed_matrix.add_edge(42, 45);
	directed_matrix.add_edge(43, 46);

	copy = directed_matrix;
	EXPECT_TRUE(copy == directed_matrix); // testing the == operator overloading at the same time :)

	// full matrix = full matrix
	adjacency_matrix<int, 3>	copy2;
	vector<int> vertices;
	vector<pair<int, int> > edges;

	copy = copy2;
	EXPECT_TRUE(copy == copy2);

	// full matrix = full matrix pt. 2
	copy = directed_matrix;
	directed_matrix.add_vertex(1);
	directed_matrix.add_vertex(2);
	directed_matrix.add_edge(46, 45);
	directed_matrix.add_edge(46, 42);
	copy = directed_matrix;
	EXPECT_TRUE(copy == directed_matrix);
}


