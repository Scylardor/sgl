/**
 * \file AdjacencyMatrix.h
 * \brief Class of the generic template class adjacency_matrix used to parameterize the SGLGraph class
 * \author Alexandre Baron
 * \version 0.1
 * \date 2013, October
 *
 * An adjacency matrix definition.
 */

#ifndef _ADJACENCYMATRIX_H
#define _ADJACENCYMATRIX_H

#include <vector>
#include <string>

#include "AbstractGraph.h"

namespace SGL {
/**
 * \class adjacency_matrix
 *
 * \brief Class representing an adjacency matrix
 * for internal use by a graph
 */
template <typename T>
class Adjacency_Matrix : public AbstractGraph<T> {
public:
	Adjacency_Matrix();
	~Adjacency_Matrix();

	// Getters (const)

	/**
	 * \brief \brief Tells if a vertex is a source (no edges coming to it = in-degree 0)
	 * \return (boolean) whether the vertex is a source or not
	 */
	inline bool vertexIsSource(const T &p_v) const { return (vertexInDegree(p_v) == 0); }

	/**
	 * \brief Tells if a vertex is a sink (no edges starting from it = out-degree = 0)
	 * \return (boolean) whether the vertex is a sink or not
	 */
	inline bool vertexIsSink(const T &p_v) const { return (vertexOutDegree(p_v) == 0); }

	/**
	 * \brief Returns the number of vertices in the matrix
	 * \return the number of vertices in the matrix
	 */
	inline unsigned nbVertices() const { return m_elems.size(); }

	/**
	 * \brief Returns the number of edges in the list
	 * \return the number of edges in the list
	 */
	inline unsigned nbEdges() const { return edges().size(); }

	/**
	 * \brief Alias of the nbVertices method
	 * "order" is the mathematical term for "number of vertices"
	 * \return the number of vertices in the list
	 */
	inline unsigned int order() const {
		return nbVertices();
	}

	/**
	 * \brief Alias of the nbEdges method
	 * "size" is the mathematical term for "number of edges" (not to be mistaken with order, the number of vertices)
	 * \return the number of edges in the list
	 */
	inline unsigned int size() const {
		return nbEdges();
	}

	bool hasVertex(const T &) const;
	unsigned vertexInDegree(const T &) const;
	unsigned vertexOutDegree(const T &) const;
	std::vector<T> vertexNeighborhood(const T&, bool p_closed = false) const;
	std::vector<T> vertices() const;
	bool hasEdge(const T &, const T &) const;
	std::vector<std::pair<T, T> > edges() const;

	// Setters (mutators)
	void addVertex(const T &);
	void deleteVertex(const T &);
	void addEdge(const T&, const T&);
	void deleteEdge(const T&, const T&);

	// Others
	bool operator==(const Adjacency_Matrix &p_rhs) const;

	friend inline std::ostream &operator<<(std::ostream &p_stream, const Adjacency_Matrix &p_matrix) {
		p_stream << p_matrix._repr(); return p_stream;
	}


private:
	std::vector<T> m_elems; /*!< all the vertices */
	std::vector<std::vector<int> > m_matrix; /*!< the adjacency matrix itself */

	int _index(const T &p_v) const;
	const std::string _repr() const;
};

} // namespace SGL

#include "AdjacencyMatrix.hpp"

#endif
