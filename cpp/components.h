//! \file components.h
//! \brief ÉDITEZ-MOI
//! \author baron_a
//! \version 0.1
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


typedef enum Configuration {
	UNDIRECTED = 1,
	DIRECTED = 2,
	MIXED = 4,
	WEIGHTED = 8,
	NOT_WEIGHTED = 16,
	ADJACENCY_MATRIX = 32,
	ADJACENCY_LIST = 64
} Configuration;

typedef int configuration;

}


#endif /* COMPONENTS_H_ */
