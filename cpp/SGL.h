/**
 * \file SGL.h
 * \brief Class of the generic template class graph
 * \author Alexandre Baron
 * \version 0.1
 * \date 2013, October
 *
 * graph definition.
 */

#ifndef _SGL_H
#define _SGL_H

namespace SGL {

typedef enum Configuration {
	UNDIRECTED = 1,
	DIRECTED = 2,
	MIXED = 4,
	WEIGHTED = 8,
	NOT_WEIGHTED = 16,
	ADJACENCY_MATRIX = 32,
	ADJACENCY_LIST = 64
} Configuration;

typedef int configuration_flags;

} // namespace SGL

//#include "AdjacencyMatrix.h"
#include "AdjacencyList.h"

#endif
