//! \file AbstractGraph.h
//! \brief The interface for abstract generic graphs (including adjacency matrix and list)
//! \author baron_a
//! \version 0.1
//! \date Oct 23, 2013

/*
 * AbstractGraph.h
 *
 *  Created on: Oct 23, 2013
 *      Author: baron_a
 */

#ifndef ABSTRACTGRAPH_H_
#define ABSTRACTGRAPH_H_

namespace SGL {
/**
 * \class AbstractGraph
 *
 * \brief Class representing a generic graph
 * The goal of this class is to implement a graph as generic as it can be.
 * To do it, it intends to permit extensive parameterization, including :
 * - making the graph directed or not, or mixed (with edges directed and some not)
 * - making it weighted or not
 * - allowing of choosing the internal representation of data (adjacency matrix, adjacency list, edge list...)
 */
template <typename T>
class AbstractGraph {
public:
	virtual ~AbstractGraph() {}

	// Getters (const)
	virtual bool vertexIsSource(const T &p_v) const = 0;
	virtual bool vertexIsSink(const T &p_v) const = 0;
	virtual bool hasVertex(const T &) const = 0;
	virtual unsigned vertexInDegree(const T &) const = 0;
	virtual unsigned vertexOutDegree(const T &) const = 0;
	virtual std::vector<T> vertexNeighborhood(const T&,
			bool p_closed = false) const = 0;
	virtual std::vector<T> vertices() const = 0;
	virtual unsigned nbVertices() const = 0;
	virtual unsigned order() const = 0;

	virtual bool hasEdge(const T &, const T &) const = 0;
	virtual std::vector<std::pair<T, T> > edges() const = 0;
	virtual unsigned nbEdges() const = 0;
	virtual unsigned size() const = 0;

	bool equals(const AbstractGraph &p_other) const;

	// Setters (mutators)
	virtual void addVertex(const T &) = 0;
	virtual void deleteVertex(const T &) = 0;

	virtual void addEdge(const T&, const T&) = 0;
	virtual void deleteEdge(const T&, const T&) = 0;

	// Others
	/**
	 * \brief Overloads the == operator to check structural equality of two graphs. Calls equals method.
	 * \param[in] p_g2 the second graph
	 * \return whether the two lists are structurally equal or not
	 */
	inline bool operator==(const AbstractGraph &p_g2) {
		return equals(p_g2);
	}

	friend inline std::ostream &operator<<(std::ostream &p_stream,
			const AbstractGraph &p_graph) {
		p_stream << p_graph._repr();
		return p_stream;
	}

protected:

	virtual const std::string _repr() const = 0;

	int m_config;

};

}

#endif /* ABSTRACTGRAPH_H_ */
