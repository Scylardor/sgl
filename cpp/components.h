//! \file components.h
//! \brief The file containing all the SGL namespace-wide components (except classes)
//! \author baron_a
//! \version 0.2
//! \date Oct 23, 2013

/*
 * components.h
 *
 *  Created on: Oct 23, 2013
 *      Author: baron_a
 */

#ifndef COMPONENTS_H_
#define COMPONENTS_H_

namespace SGL {

/** \typedef typedef enum Configuration
 *  \brief Definition of the graph configuration flags
 *  so they can be bitwise-or'd at a graph creation to specify its configuration
 *  (weighted or not, directed or not...)
 *  The ADJACENCY_* flags aren't meant to do something yet, maybe later.
 */
typedef enum Configuration {
	UNDIRECTED = 1,
	DIRECTED = 2,
	MIXED = 4,
	WEIGHTED = 8,
	NOT_WEIGHTED = 16,
	ADJACENCY_MATRIX = 32,
	ADJACENCY_LIST = 64
} Configuration;

/** \typedef typedef int configuration
 *  \brief To make it very clear that the enum values you can bitwise-or are for configuration purposes.
 */
typedef int configuration;

}

#endif /* COMPONENTS_H_ */
