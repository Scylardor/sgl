/**
 * \file SGLGraph.h
 * \brief Class of the generic template class SGLGraph
 * \author Alexandre Baron
 * \version 0.1
 * \date 2013, October
 *
 * SGLGraph definition.
 */

#ifndef _SGLGRAPH_H
#define _SGLGRAPH_H

#include <utility> // pair
#include <iostream> // cout
#include <stdexcept>
#include <vector>
#include <list>

namespace SGL {
/**
 * \class SGLGraph
 *
 * \brief Class representing a generic graph
 * The goal of this class is to implement a graph as generic as it can be.
 * To do it, it intends to permit extensive parameterization, including :
 * - making the graph directed or not, or mixed (with edges directed and some not)
 * - making it weighted or not
 * - allowing of choosing the internal representation of data (adjacency matrix, adjacency list, edge list...)
 */
template<typename T>
class SGLGraph {
public:
	// Constructors
	explicit SGLGraph();
	SGLGraph(const SGLGraph& p_src);
	SGLGraph(const SGLGraph& p_src, const std::vector<T>& p_filter);
	// Destructor
	~SGLGraph();
	// Operator =
	const SGLGraph& operator =(const SGLGraph &p_src);

	// Getters (const)
	/**
	 * \brief Tells whether the vertex is a source or not
	 * i.e. if it has no edges coming to it (in-degree = 0)
	 * \post The graph remains unchanged
	 * \return (boolean) whether the vertex is a source or not
	 */
	inline bool vertexIsSource(const T &p_v) const {
		return (vertexInDegree(p_v) == 0);
	}

	/**
	 * \brief Tells whether the vertex is a sink or not
	 * i.e. if it has no edges starting from it (out-degree = 0)
	 * \post The graph remains unchanged
	 * \return (boolean) whether the vertex is a sink or not
	 */
	inline bool vertexIsSink(const T &p_v) const {
		return (vertexOutDegree(p_v) == 0);
	}

	/**
	 * \brief Returns the number of vertices in the graph
	 * \post The graph remains unchanged
	 * \return the number of vertices in the graph
	 */
	inline unsigned int order() const {
		return m_nodes.size();
	}

	bool			hasVertex(const T &) const;
	unsigned int	vertexInDegree(const T &) const;
	unsigned int	vertexOutDegree(const T &) const;
	std::vector<T>	vertexNeighborhood(const T&, bool p_closed = false) const;
	bool			hasEdge(const T &, const T &) const;
	unsigned int	size() const;
	std::vector<T>	vertices() const;
	std::vector<std::pair<T, T> > edges() const;

	// Setters (mutators)
	void			addVertex(const T &);
	void			deleteVertex(const T &);
	void			addEdge(const T&, const T&);
	void			deleteEdge(const T&, const T&);

	// Others
	void	display() const;
	/**
	 * \brief Static member function to check the structural equality of two graphs
	 * i.e. same vertices, and same edges
	 * \param[in] p_g1 the first graph
	 * \param[in] p_g2 the second graph
	 * \return whether the two graphs are structurally equal or not
	 */
	static bool	areEqual(const SGLGraph &p_g1, const SGLGraph &p_g2) {
		bool areEqual = true;

		if ((p_g1.order() != p_g2.order()) || (p_g1.size() != p_g2.size())) {
			areEqual = false;
		}
		if (areEqual) {
			std::vector<T> elems = p_g1.vertices();

			for (unsigned int i = 0; i < elems.size(); i++) {
				if (!p_g2.hasVertex(elems[i])) {
					areEqual = false;
					break;
				}
			}
			std::vector<std::pair <T, T> > edges = p_g1.edges();

			for (unsigned int i = 0; i < edges.size(); i++) {
				if (!p_g2.hasEdge(edges[i].first, edges[i].second)) {
					areEqual = false;
					break;
				}
			}
		}
		return areEqual;
	}

private:
	/**
	 * \class Node
	 * \brief Class used by the internal adjacency list of the graph.
	 */
	class Node {
	public:
		T m_data; /*!< data of a vertex */
		std::list<T> m_neighbors; /*!< this list contains all the data of all vertex's neighbors */

		Node(const T& p_data) : m_data(p_data) {}
	};
	std::vector<Node *> m_nodes; /*!< internal container for the adjacency list nodes */

	void	_copyAdjacencyList(const SGLGraph &p_src);
	int		_index(const T &p_v) const;
};

} // namespace SGL

#include "SGLGraph.hpp"

#endif
