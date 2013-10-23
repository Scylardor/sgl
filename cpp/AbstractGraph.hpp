//! \file AbstractGraph.hpp
//! \brief Definition of methods usable by any sort of graph (totally abstracted)
//! \author baron_a
//! \version 0.1
//! \date Oct 22, 2013

#include "AbstractGraph.h"

using namespace std;

//! \brief Checks the structural equality of the current graph with another (same vertices, same edges)
//! \param[in] p_other another graph
//! \exception bad_alloc if not enough memory
//! \return true if the graphs are equal, or false
template <typename T>
bool AbstractGraph<T>::equals(const AbstractGraph &p_other) const {
		bool areEqual = true;

		if ((nbVertices() != p_g2.nbVertices()) || (nbEdges() != p_g2.nbEdges())) {
			areEqual = false;
		}
		if (areEqual) {
			vector<T> elems = vertices();

			for (unsigned int i = 0; i < elems.size(); i++) {
				if (!p_g2.hasVertex(elems[i])) {
					areEqual = false;
					break;
				}
			}
			vector<std::pair <T, T> > theEdges = edges();

			for (unsigned int i = 0; i < theEdges.size(); i++) {
				if (!p_g2.hasEdge(theEdges[i].first, theEdges[i].second)) {
					areEqual = false;
					break;
				}
			}
		}
		return areEqual;
	}
