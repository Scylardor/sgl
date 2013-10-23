//! \file AbstractGraph.hpp
//! \brief Definition of methods usable by any sort of graph (totally abstracted)
//! \author baron_a
//! \version 0.1
//! \date Oct 22, 2013

#include "SGL.h"

//! \brief Un commentaire générique d'exemple
//! \param[in] un paramètre d'entrée
//! param[out] un paramètre de sortie
//! \pre une précondition
//! \post État une fois que la fonction a terminé
//! \exception Exception lancée
//! \return Ce que retourne la fonction
template <typename T>
bool AbstractGraph<T>::equals(const AbstractGraph &p_other) const {
		bool areEqual = true;

		if ((nbVertices() != p_g2.nbVertices()) || (nbEdges() != p_g2.nbEdges())) {
			areEqual = false;
		}
		if (areEqual) {
			std::vector<T> elems = vertices();

			for (unsigned int i = 0; i < elems.size(); i++) {
				if (!p_g2.hasVertex(elems[i])) {
					areEqual = false;
					break;
				}
			}
			std::vector<std::pair <T, T> > theEdges = edges();

			for (unsigned int i = 0; i < theEdges.size(); i++) {
				if (!p_g2.hasEdge(theEdges[i].first, theEdges[i].second)) {
					areEqual = false;
					break;
				}
			}
		}
		return areEqual;
	}
