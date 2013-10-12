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

#include <iostream>
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
	SGLGraph(const SGLGraph&);
	SGLGraph(const SGLGraph&, const std::vector<T>&);

	// Destructor
	~SGLGraph();

	// Operator =
	const SGLGraph& operator =(const SGLGraph&);

	// Vertices related operations
	void			addVertex(const T &);
	void			deleteVertex(const T &);
	bool			hasVertex(const T &) const;
	unsigned int	vertexInDegree(const T &) const;
	unsigned int	vertexOutDegree(const T &) const;
	inline bool		vertexIsSource(const T &p_v) const {
		return (vertexInDegree(p_v) == 0);
	}
	inline bool		vertexIsSink(const T &p_v) const {
		return (vertexOutDegree(p_v) == 0);
	}
	std::vector<T>	vertexNeighborhood(const T&, bool p_closed = false) const;
	std::vector<T>	vertices() const;

	// Edges related operations
	void			addEdge(const T&, const T&);
	void			deleteEdge(const T&, const T&);
	bool			hasEdge(const T &, const T &) const;
	unsigned int	order() const;
	unsigned int	size() const;

	// Other
	void	display() const;

private:
	/**
	 * \class Node
	 *
	 * \brief Class used by the internal adjacency list of the graph.
	 */
	class Node {
	public:
		T m_data; /*!< data of a vertex */
		std::list<T> m_neighbors; /*!< this list contains all the neighbors nodes' indexes of the vertex */

		Node(const T& p_data) : m_data(p_data) {}
	};
	std::vector<Node *> m_nodes; /*!< internal container for the adjacency list nodes */

	void	_copyAdjacencyList(const SGLGraph &p_src);
	int		_index(const T &p_v) const;
};

} // namespace SGL

#include "SGLGraph.hpp"

#endif
