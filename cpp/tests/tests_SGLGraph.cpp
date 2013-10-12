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
class GraphTest: public ::testing::Test
{
public:
   SGLGraph<int> graph;
};

TEST_F(GraphTest, constructor)
{
   EXPECT_EQ((int)graph.size(), 0);
   EXPECT_EQ((int)graph.order(), 0);
}

TEST_F(GraphTest, LogicOnEmptyGraph)
{
	EXPECT_THROW(graph.deleteEdge(42, 21), logic_error);
	EXPECT_THROW(graph.deleteVertex(42), logic_error);
	EXPECT_THROW(graph.hasEdge(42, 21), logic_error);
	EXPECT_THROW(graph.vertexInDegree(42), logic_error);
	EXPECT_THROW(graph.vertexOutDegree(42), logic_error);
	EXPECT_THROW(graph.vertexNeighborhood(42), logic_error);
}
