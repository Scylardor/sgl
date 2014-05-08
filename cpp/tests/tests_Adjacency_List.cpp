//! \file tests_adjacency_list.cpp
//! \brief adjacency_list class unit tests
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
	AdjacencyListTest() : list(0), undirected_list(UNDIRECTED) {}

	adjacency_list<int> list;
	adjacency_list<int> undirected_list;

protected:
	void addVertices(int nbr, int p_from);
};

void AdjacencyListTest::addVertices(int p_nbr, int p_from) {
	for (int i = 0; i < p_nbr; i++) {
		list.add_vertex(p_from);
		p_from++;
	}
}

TEST_F(AdjacencyListTest, constructor) {
	EXPECT_TRUE(list.nb_vertices() == 0);
	EXPECT_TRUE(list.nb_edges() == 0);

	EXPECT_TRUE(undirected_list.nb_vertices() == 0);
	EXPECT_TRUE(undirected_list.nb_edges() == 0);
}

TEST_F(AdjacencyListTest, LogicOnEmptyList) {
	EXPECT_THROW(list.delete_edge(42, 21), logic_error);
	EXPECT_THROW(list.delete_vertex(42), logic_error);
	EXPECT_THROW(list.has_edge(42, 21), logic_error);
	EXPECT_THROW(list.vertex_in_degree(42), logic_error);
	EXPECT_THROW(list.vertex_out_degree(42), logic_error);
	EXPECT_THROW(list.vertex_neighborhood(42), logic_error);

	EXPECT_THROW(undirected_list.delete_edge(42, 21), logic_error);
	EXPECT_THROW(undirected_list.delete_vertex(42), logic_error);
	EXPECT_THROW(undirected_list.has_edge(42, 21), logic_error);
	EXPECT_THROW(undirected_list.vertex_in_degree(42), logic_error);
	EXPECT_THROW(undirected_list.vertex_out_degree(42), logic_error);
	EXPECT_THROW(undirected_list.vertex_neighborhood(42), logic_error);
}

TEST_F(AdjacencyListTest, add_vertex) {
	list.add_vertex(42);
	EXPECT_TRUE(list.nb_vertices() == 1);
	EXPECT_THROW(list.add_vertex(42), logic_error);
	list.add_vertex(21);
	list.add_vertex(34);
	EXPECT_TRUE(list.nb_vertices() == 3);
	EXPECT_THROW(list.add_vertex(42), logic_error);
	EXPECT_THROW(list.add_vertex(21), logic_error);
	EXPECT_THROW(list.add_vertex(34), logic_error);

	undirected_list.add_vertex(42);
	EXPECT_TRUE(undirected_list.nb_vertices() == 1);
	EXPECT_THROW(undirected_list.add_vertex(42), logic_error);
	undirected_list.add_vertex(21);
	undirected_list.add_vertex(34);
	EXPECT_TRUE(undirected_list.nb_vertices() == 3);
	EXPECT_THROW(undirected_list.add_vertex(42), logic_error);
	EXPECT_THROW(undirected_list.add_vertex(21), logic_error);
	EXPECT_THROW(undirected_list.add_vertex(34), logic_error);
}

TEST_F(AdjacencyListTest, delete_vertex) {
	list.add_vertex(42);
	EXPECT_THROW(list.delete_vertex(41), logic_error);
	list.delete_vertex(42);
	EXPECT_TRUE(list.nb_vertices() == 0);
	EXPECT_THROW(list.delete_vertex(42), logic_error);
	list.add_vertex(21);
	list.add_vertex(42);
	list.add_vertex(84);
	list.delete_vertex(21);
	EXPECT_TRUE(list.nb_vertices() == 2);
	list.add_vertex(21);
	list.delete_vertex(42);
	EXPECT_TRUE(list.nb_vertices() == 2);
	list.add_vertex(42);
	list.delete_vertex(84);
	list.delete_vertex(42);
	list.delete_vertex(21);
	EXPECT_TRUE(list.nb_vertices() == 0);

	undirected_list.add_vertex(42);
	EXPECT_THROW(undirected_list.delete_vertex(41), logic_error);
	undirected_list.delete_vertex(42);
	EXPECT_TRUE(undirected_list.nb_vertices() == 0);
	EXPECT_THROW(undirected_list.delete_vertex(42), logic_error);
	undirected_list.add_vertex(21);
	undirected_list.add_vertex(42);
	undirected_list.add_vertex(84);
	undirected_list.delete_vertex(21);
	EXPECT_TRUE(undirected_list.nb_vertices() == 2);
	undirected_list.add_vertex(21);
	undirected_list.delete_vertex(42);
	EXPECT_TRUE(undirected_list.nb_vertices() == 2);
	undirected_list.add_vertex(42);
	undirected_list.delete_vertex(84);
	undirected_list.delete_vertex(42);
	undirected_list.delete_vertex(21);
	EXPECT_TRUE(undirected_list.nb_vertices() == 0);
}

TEST_F(AdjacencyListTest, has_vertex) {
	EXPECT_FALSE(list.has_vertex(42));
	list.add_vertex(42);
	EXPECT_TRUE(list.has_vertex(42));
	list.delete_vertex(42);
	EXPECT_FALSE(list.has_vertex(42));
	list.add_vertex(21);
	list.add_vertex(42);
	EXPECT_TRUE(list.has_vertex(21));
	EXPECT_TRUE(list.has_vertex(42));

	EXPECT_FALSE(undirected_list.has_vertex(42));
	undirected_list.add_vertex(42);
	EXPECT_TRUE(undirected_list.has_vertex(42));
	undirected_list.delete_vertex(42);
	EXPECT_FALSE(undirected_list.has_vertex(42));
	undirected_list.add_vertex(21);
	undirected_list.add_vertex(42);
	EXPECT_TRUE(undirected_list.has_vertex(21));
	EXPECT_TRUE(undirected_list.has_vertex(42));
}

TEST_F(AdjacencyListTest, vertex_in_degree) {
	list.add_vertex(42);
	EXPECT_TRUE(list.vertex_in_degree(42) == 0);
	list.add_vertex(21);
	list.add_edge(21, 42);
	EXPECT_TRUE(list.vertex_in_degree(42) == 1);
	list.add_vertex(84);
	list.add_edge(84, 42);
	EXPECT_TRUE(list.vertex_in_degree(42) == 2);
	list.add_edge(42, 42);
	EXPECT_TRUE(list.vertex_in_degree(42) == 3);
	list.delete_vertex(84);
	EXPECT_TRUE(list.vertex_in_degree(42) == 2);
	list.delete_vertex(21);
	EXPECT_TRUE(list.vertex_in_degree(42) == 1);
	list.delete_vertex(42);
	EXPECT_THROW(list.vertex_in_degree(42), logic_error);

	undirected_list.add_vertex(42);
	EXPECT_TRUE(undirected_list.vertex_in_degree(42) == 0);
	undirected_list.add_vertex(21);
	undirected_list.add_edge(21, 42);
	EXPECT_TRUE(undirected_list.vertex_in_degree(42) == 1);
	EXPECT_TRUE(undirected_list.vertex_in_degree(21) == 1);
	undirected_list.add_vertex(84);
	undirected_list.add_edge(84, 42);
	EXPECT_TRUE(undirected_list.vertex_in_degree(42) == 2);
	EXPECT_TRUE(undirected_list.vertex_in_degree(84) == 1);
	undirected_list.add_edge(42, 42);
	EXPECT_TRUE(undirected_list.vertex_in_degree(42) == 4);
	undirected_list.delete_vertex(84);
	EXPECT_TRUE(undirected_list.vertex_in_degree(42) == 3);
	undirected_list.delete_vertex(21);
	EXPECT_TRUE(undirected_list.vertex_in_degree(42) == 2);
	undirected_list.delete_vertex(42);
	EXPECT_THROW(undirected_list.vertex_in_degree(42), logic_error);
}

TEST_F(AdjacencyListTest, vertex_out_degree) {
	list.add_vertex(42);
	EXPECT_TRUE(list.vertex_out_degree(42) == 0);
	list.add_vertex(21);
	list.add_edge(42, 21);
	EXPECT_TRUE(list.vertex_out_degree(42) == 1);
	list.add_vertex(84);
	list.add_edge(42, 84);
	EXPECT_TRUE(list.vertex_out_degree(42) == 2);
	list.add_edge(42, 42);
	EXPECT_TRUE(list.vertex_out_degree(42) == 3);
	list.delete_vertex(84);
	EXPECT_TRUE(list.vertex_out_degree(42) == 2);
	list.delete_vertex(21);
	EXPECT_TRUE(list.vertex_out_degree(42) == 1);
	list.delete_vertex(42);
	EXPECT_THROW(list.vertex_out_degree(42), logic_error);

	undirected_list.add_vertex(42);
	EXPECT_TRUE(undirected_list.vertex_out_degree(42) == 0);
	undirected_list.add_vertex(21);
	undirected_list.add_edge(42, 21);
	EXPECT_TRUE(undirected_list.vertex_out_degree(42) == 1);
	undirected_list.add_vertex(84);
	undirected_list.add_edge(42, 84);
	EXPECT_TRUE(undirected_list.vertex_out_degree(42) == 2);
	undirected_list.add_edge(42, 42);
	EXPECT_TRUE(undirected_list.vertex_out_degree(42) == 4);
	undirected_list.delete_vertex(84);
	EXPECT_TRUE(undirected_list.vertex_out_degree(42) == 3);
	undirected_list.delete_vertex(21);
	EXPECT_TRUE(undirected_list.vertex_out_degree(42) == 2);
	undirected_list.delete_vertex(42);
	EXPECT_THROW(undirected_list.vertex_out_degree(42), logic_error);
}

TEST_F(AdjacencyListTest, vertex_is_source) {
	EXPECT_THROW(list.vertex_is_source(42), logic_error);
	list.add_vertex(42);
	EXPECT_TRUE(list.vertex_is_source(42));
	list.add_vertex(21);
	list.add_edge(21, 42);
	EXPECT_FALSE(list.vertex_is_source(42));
	list.delete_vertex(21);
	EXPECT_TRUE(list.vertex_is_source(42));
	list.add_vertex(21);
	list.add_edge(42, 21);
	EXPECT_TRUE(list.vertex_is_source(42));
	list.add_edge(42, 42);
	EXPECT_FALSE(list.vertex_is_source(42));

	// it has no sense to search a source in an undirected graph !
	EXPECT_THROW(undirected_list.vertex_is_source(42), logic_error);
	undirected_list.add_vertex(42);
	EXPECT_THROW(undirected_list.vertex_is_source(42), logic_error);
	undirected_list.add_vertex(21);
	undirected_list.add_edge(21, 42);
	EXPECT_THROW(undirected_list.vertex_is_source(42), logic_error);
}

TEST_F(AdjacencyListTest, vertex_is_sink) {
	EXPECT_THROW(list.vertex_is_sink(42), logic_error);
	list.add_vertex(42);
	EXPECT_TRUE(list.vertex_is_sink(42));
	list.add_vertex(21);
	list.add_edge(21, 42);
	EXPECT_TRUE(list.vertex_is_sink(42));
	list.delete_vertex(21);
	EXPECT_TRUE(list.vertex_is_sink(42));
	list.add_vertex(21);
	list.add_edge(42, 21);
	EXPECT_FALSE(list.vertex_is_sink(42));

	// it has no sense to search a sink in an undirected graph !
	EXPECT_THROW(undirected_list.vertex_is_sink(42), logic_error);
	undirected_list.add_vertex(42);
	EXPECT_THROW(undirected_list.vertex_is_sink(42), logic_error);
	undirected_list.add_vertex(21);
	undirected_list.add_edge(21, 42);
	EXPECT_THROW(undirected_list.vertex_is_sink(42), logic_error);
}

TEST_F(AdjacencyListTest, vertex_neighborhood) {
	list.add_vertex(42);
	list.add_vertex(43);
	list.add_vertex(44);
	list.add_vertex(45);
	list.add_vertex(46);
	// Two edges coming to 42
	list.add_edge(43, 42);
	list.add_edge(44, 42);
	// Two edges coming from 42
	list.add_edge(42, 43);
	list.add_edge(42, 44);

	vector<int> neighbors = list.vertex_neighborhood(42);
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
	neighbors = list.vertex_neighborhood(42, true);
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

	list.add_edge(42, 42);
	// if there is a loop on 42, it should be in its own neighborhood even when we don't want it closed
	EXPECT_TRUE(neighbors.size() == 3);
	found = std::find(neighbors.begin(), neighbors.end(), 42);
	EXPECT_NE(found, neighbors.end());
}
//
//	undirected_list.add_vertex(42);
//	undirected_list.add_vertex(43);
//	undirected_list.add_vertex(44);
//	undirected_list.add_vertex(45);
//	undirected_list.add_vertex(46);
//	// Two edges coming to 42
//	undirected_list.add_edge(43, 42);
//	undirected_list.add_edge(45, 42);
//	// One coming from 42
//	undirected_list.add_edge(42, 44);
//
//	neighbors = undirected_list.vertex_neighborhood(42);
//
//	// Neighborhood of 42 should be 3 vertices : the graph is undirected
//	EXPECT_TRUE(neighbors.size() == 3);
//	for (int i = 43; i < 46; i++) {
//		// each of the concerned vertices should be in the vector
//		found = std::find(neighbors.begin(), neighbors.end(), i);
//		EXPECT_NE(found, neighbors.end());
//	}
//	// Vertices which aren't in 42's neighborhood shouldn't be in the vector
//	found = std::find(neighbors.begin(), neighbors.end(), 46);
//	EXPECT_EQ(found, neighbors.end());
//
//	// Let's test the "closed" parameter (should include the vertex itself in the vector)
//	neighbors = undirected_list.vertex_neighborhood(42, true);
//	EXPECT_TRUE(neighbors.size() == 4);
//	for (int i = 42; i < 46; i++) {
//		// each of the concerned vertices should be in the vector
//		found = std::find(neighbors.begin(), neighbors.end(), i);
//		EXPECT_NE(found, neighbors.end());
//	}
//	// Vertices which aren't in 42's neighborhood shouldn't be in the vector
//	found = std::find(neighbors.begin(), neighbors.end(), 46);
//	EXPECT_EQ(found, neighbors.end());
//
//	undirected_list.add_edge(42, 42);
//	// if there is a loop on 42, it should be in its own neighborhood even when we don't want it closed
//	EXPECT_TRUE(neighbors.size() == 4);
//	found = std::find(neighbors.begin(), neighbors.end(), 42);
//	EXPECT_NE(found, neighbors.end());
//}
//
TEST_F(AdjacencyListTest, vertices) {
	vector<int> vertices = list.vertices();

	EXPECT_TRUE(vertices.size() == 0);
	list.add_vertex(42);
	list.add_vertex(43);
	list.add_vertex(44);
	list.add_vertex(45);
	list.add_vertex(46);
	list.add_vertex(47);
	vertices = list.vertices();
	EXPECT_TRUE(vertices.size() == 6);
	for (int i = 42; i < 48; i++) {
		// each of the concerned vertices should be in the vector
		vector<int>::const_iterator found = std::find(vertices.begin(), vertices.end(), i);
		EXPECT_NE(found, vertices.end());
	}
}

//	vertices = undirected_list.vertices();
//	EXPECT_TRUE(vertices.size() == 0);
//	undirected_list.add_vertex(42);
//	undirected_list.add_vertex(43);
//	undirected_list.add_vertex(44);
//	undirected_list.add_vertex(45);
//	undirected_list.add_vertex(46);
//	undirected_list.add_vertex(47);
//	vertices = undirected_list.vertices();
//	EXPECT_TRUE(vertices.size() == 6);
//	for (int i = 42; i < 48; i++) {
//		// each of the concerned vertices should be in the vector
//		vector<int>::const_iterator found = std::find(vertices.begin(), vertices.end(), i);
//		EXPECT_NE(found, vertices.end());
//	}
//}
//
TEST_F(AdjacencyListTest, add_edge) {
	EXPECT_THROW(list.add_edge(41, 42), logic_error);
	list.add_vertex(42);
	list.add_vertex(43);
	list.add_vertex(44);
	list.add_vertex(45);
	list.add_vertex(46);
	list.add_vertex(47);
	list.add_edge(42, 43);
	list.add_edge(43, 42);
	list.add_edge(44, 45);
	list.add_edge(45, 46);
	list.add_edge(42, 42);
	list.add_edge(47, 43);
	list.add_edge(46, 44);
	EXPECT_THROW(list.add_edge(42, 41), logic_error); // no dest vertex '41'
	EXPECT_THROW(list.add_edge(41, 43), logic_error); // no src vertex '41'
	EXPECT_THROW(list.add_edge(42, 42), logic_error); // already exists
}
//
//	EXPECT_THROW(undirected_list.add_edge(41, 42), logic_error);
//	undirected_list.add_vertex(42);
//	undirected_list.add_vertex(43);
//	undirected_list.add_vertex(44);
//	undirected_list.add_vertex(45);
//	undirected_list.add_vertex(46);
//	undirected_list.add_vertex(47);
//	undirected_list.add_edge(42, 43);
//	undirected_list.add_edge(44, 45);
//	undirected_list.add_edge(45, 46);
//	undirected_list.add_edge(42, 42);
//	undirected_list.add_edge(47, 43);
//	undirected_list.add_edge(46, 44);
//	EXPECT_THROW(undirected_list.add_edge(42, 41), logic_error); // no dest vertex '41'
//	EXPECT_THROW(undirected_list.add_edge(41, 43), logic_error); // no src vertex '41'
//	EXPECT_THROW(undirected_list.add_edge(42, 42), logic_error); // already exists
//	EXPECT_THROW(undirected_list.add_edge(43, 42), logic_error); // it has been added the other way around, but as the graph is undirected, it already exists
//}
//
TEST_F(AdjacencyListTest, delete_edge) {
	EXPECT_THROW(list.delete_edge(42, 41), logic_error);
	list.add_vertex(42);
	list.add_vertex(43);
	list.add_vertex(44);
	list.add_vertex(45);
	list.add_vertex(46);
	list.add_vertex(47);
	EXPECT_THROW(list.delete_edge(42, 43), logic_error); // no such edge
	EXPECT_THROW(list.delete_edge(42, 41), logic_error); // no such vertex '41'
	EXPECT_THROW(list.delete_edge(41, 43), logic_error); // idem
	list.add_edge(42, 43);
	EXPECT_THROW(list.delete_edge(43, 42), logic_error); // no such edge
	list.add_edge(43, 42);
	list.delete_edge(42, 43);
	list.delete_edge(43, 42);
	EXPECT_THROW(list.delete_edge(42, 43), logic_error); // no such edge
	EXPECT_THROW(list.delete_edge(43, 42), logic_error); // no such edge
}
//
//	EXPECT_THROW(undirected_list.delete_edge(42, 41), logic_error);
//	undirected_list.add_vertex(42);
//	undirected_list.add_vertex(43);
//	undirected_list.add_vertex(44);
//	undirected_list.add_vertex(45);
//	undirected_list.add_vertex(46);
//	undirected_list.add_vertex(47);
//	EXPECT_THROW(undirected_list.delete_edge(42, 41), logic_error);
//	EXPECT_THROW(undirected_list.delete_edge(41, 43), logic_error);
//	undirected_list.add_edge(42, 43);
//	undirected_list.delete_edge(43, 42); // should be fine: the graph is undirected
//	undirected_list.add_edge(43, 42);
//	undirected_list.delete_edge(42, 43); // the other way around
//	EXPECT_THROW(undirected_list.delete_edge(42, 43), logic_error); // no longer exists
//	EXPECT_THROW(undirected_list.delete_edge(43, 42), logic_error); // idem
//
//}
//
TEST_F(AdjacencyListTest, has_edge) {
	EXPECT_THROW(list.add_edge(41, 42), logic_error);
	list.add_vertex(42);
	list.add_vertex(43);
	list.add_vertex(44);
	list.add_vertex(45);
	list.add_vertex(46);
	list.add_vertex(47);
	EXPECT_FALSE(list.has_edge(42, 43));
	list.add_edge(42, 43);
	list.add_edge(43, 42);
	list.add_edge(44, 45);
	list.add_edge(45, 46);
	list.add_edge(42, 42);
	list.add_edge(47, 43);
	list.add_edge(46, 44);
	EXPECT_FALSE(list.has_edge(43, 44));
	EXPECT_TRUE(list.has_edge(42, 43));
	list.add_edge(43, 44);
	EXPECT_TRUE(list.has_edge(43, 44));
	EXPECT_TRUE(list.has_edge(42, 43));
	list.delete_edge(42, 43);
	EXPECT_TRUE(list.has_edge(43, 42));
	EXPECT_FALSE(list.has_edge(42, 43));
	list.delete_edge(43, 42);
	EXPECT_FALSE(list.has_edge(43, 42));
	EXPECT_FALSE(list.has_edge(42, 43));
	EXPECT_TRUE(list.has_edge(46, 44));
}

//	// tests of the undirected list are slightly different as the internal mechanisms are not the same at all
//	EXPECT_THROW(undirected_list.add_edge(41, 42), logic_error);
//	undirected_list.add_vertex(42);
//	undirected_list.add_vertex(43);
//	undirected_list.add_vertex(44);
//	undirected_list.add_vertex(45);
//	undirected_list.add_vertex(46);
//	undirected_list.add_vertex(47);
//	EXPECT_FALSE(undirected_list.has_edge(42, 43));
//	undirected_list.add_edge(42, 43);
//	undirected_list.add_edge(42, 44);
//	undirected_list.add_edge(42, 46);
//	undirected_list.add_edge(43, 44);
//	undirected_list.add_edge(43, 45);
//	undirected_list.add_edge(43, 46);
//	undirected_list.add_edge(43, 47);
//	undirected_list.add_edge(44, 45);
//	undirected_list.add_edge(44, 47);
//	EXPECT_TRUE(undirected_list.has_edge(42, 43));
//	EXPECT_TRUE(undirected_list.has_edge(42, 44));
//	EXPECT_TRUE(undirected_list.has_edge(42, 46));
//	EXPECT_TRUE(undirected_list.has_edge(43, 42));
//	EXPECT_TRUE(undirected_list.has_edge(43, 44));
//	EXPECT_TRUE(undirected_list.has_edge(43, 45));
//	EXPECT_TRUE(undirected_list.has_edge(43, 46));
//	EXPECT_TRUE(undirected_list.has_edge(43, 47));
//	EXPECT_TRUE(undirected_list.has_edge(44, 43));
//	EXPECT_TRUE(undirected_list.has_edge(42, 44));
//	EXPECT_TRUE(undirected_list.has_edge(44, 42));
//	EXPECT_TRUE(undirected_list.has_edge(44, 45));
//	EXPECT_TRUE(undirected_list.has_edge(44, 47));
//	undirected_list.delete_edge(44, 43);
//	EXPECT_TRUE(undirected_list.has_edge(42, 43));
//	EXPECT_TRUE(undirected_list.has_edge(44, 42));
//	EXPECT_FALSE(undirected_list.has_edge(43, 44));
//	undirected_list.delete_vertex(43);
//	EXPECT_THROW(undirected_list.add_edge(42, 43), logic_error);
//	EXPECT_THROW(undirected_list.add_edge(43, 44), logic_error);
//	EXPECT_TRUE(undirected_list.has_edge(42, 44));
//	EXPECT_TRUE(undirected_list.has_edge(42, 46));
//	EXPECT_TRUE(undirected_list.has_edge(42, 44));
//	EXPECT_TRUE(undirected_list.has_edge(44, 42));
//	EXPECT_TRUE(undirected_list.has_edge(44, 45));
//	EXPECT_TRUE(undirected_list.has_edge(44, 47));
//}
//
////TEST_F(AdjacencyListTest, display) {
////	cout << list;
////	addVertices(6, 42);
////	cout << list;
////	list.add_edge(42, 43);
////	list.add_edge(42, 45);
////	list.add_edge(43, 46);
////	list.add_edge(43, 42);
////	list.add_edge(46, 45);
////	list.add_edge(46, 42);
////	list.add_edge(47, 42);
////	list.add_edge(47, 43);
////	list.add_edge(47, 44);
////	list.add_edge(47, 45);
////	list.add_edge(47, 46);
////	list.add_edge(47, 47);
////	cout << list;
////}
//
TEST_F(AdjacencyListTest, CopyConstructor) {
	adjacency_list<int>	copy(list);

	EXPECT_TRUE(copy.nb_vertices() == 0);
	EXPECT_TRUE(copy.nb_edges() == 0);
	list.add_vertex(42);
	list.add_vertex(43);
	list.add_vertex(44);
	list.add_vertex(45);
	list.add_vertex(46);
	list.add_vertex(47);
	list.add_edge(42, 42);
	list.add_edge(42, 43);
	list.add_edge(43, 46);
	list.add_edge(43, 47);
	list.add_edge(46, 43);
	EXPECT_TRUE(list.nb_vertices() == 6);

	adjacency_list<int>	copy2(list);
	vector<int> vertices = copy2.vertices();
	vector<int>::const_iterator found;

	EXPECT_EQ(list.nb_vertices(), copy2.nb_vertices());
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

}
//	adjacency_list<int>	copy3(undirected_list);
//
//	EXPECT_TRUE(copy3.nb_vertices() == 0);
//	EXPECT_TRUE(copy3.nb_edges() == 0);
//	undirected_list.add_vertex(42);
//	undirected_list.add_vertex(43);
//	undirected_list.add_vertex(44);
//	undirected_list.add_vertex(45);
//	undirected_list.add_vertex(46);
//	undirected_list.add_vertex(47);
//	undirected_list.add_edge(42, 42);
//	undirected_list.add_edge(42, 43);
//	undirected_list.add_edge(43, 46);
//	undirected_list.add_edge(43, 47);
//	EXPECT_TRUE(undirected_list.nb_vertices() == 6);
//	EXPECT_TRUE(undirected_list.has_edge(46, 43));
//	EXPECT_TRUE(undirected_list.has_edge(47, 43));
//
//	adjacency_list<int>	copy4(undirected_list);
//	vertices = copy4.vertices();
//
//	EXPECT_EQ(undirected_list.nb_vertices(), copy4.nb_vertices());
//	EXPECT_EQ(vertices.size(), copy4.nb_vertices());
//	for (int i = 42; i < 48; i++) {
//		// each of the concerned vertices should be in the vector
//		found = std::find(vertices.begin(), vertices.end(), i);
//		EXPECT_NE(found, vertices.end());
//	}
//	EXPECT_TRUE(copy4.nb_edges() == 4);
//	EXPECT_TRUE(copy4.has_edge(42, 42));
//	EXPECT_TRUE(copy4.has_edge(42, 43));
//	EXPECT_TRUE(copy4.has_edge(43, 46));
//	EXPECT_TRUE(copy4.has_edge(43, 47));
//}
//
//TEST_F(AdjacencyListTest, AssignmentOperator) {
//	// from empty list to empty list
//	adjacency_list<int>	copy;
//
//	EXPECT_TRUE(list.nb_vertices() == 0);
//	EXPECT_TRUE(list.nb_edges() == 0);
//	// empty list = empty list
//	copy = list;
//	EXPECT_TRUE(copy.nb_vertices() == 0);
//	EXPECT_TRUE(copy.nb_edges() == 0);
//
//	// empty list = full list
//	list.add_vertex(42);
//	list.add_vertex(43);
//	list.add_vertex(44);
//	list.add_vertex(45);
//	list.add_vertex(46);
//	list.add_vertex(47);
//	list.add_edge(42, 43);
//	list.add_edge(42, 45);
//	list.add_edge(43, 46);
//
//	copy = list;
//	EXPECT_TRUE(copy == list); // testing the == operator overloading at the same time :)
//
//	// full list = full list
//	adjacency_list<int>	copy2;
//	vector<int> vertices;
//	vector<pair<int, int> > edges;
//
//	copy = copy2;
//	EXPECT_TRUE(copy == copy2);
//
//	// full list = full list pt. 2
//	copy = list;
//	list.add_vertex(1);
//	list.add_vertex(2);
//	list.add_edge(46, 45);
//	list.add_edge(46, 42);
//	copy = list;
//	EXPECT_TRUE(copy == list);
//}
