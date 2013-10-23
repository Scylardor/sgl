//! \file AdjacencyList.h
//! \brief Declaration of a generic adjacency list for usage in a graph
//! \author baron_a
//! \version 0.1
//! \date Oct 19, 2013

#ifndef ADJACENCYLIST_H_
#define ADJACENCYLIST_H_

#include <vector>
#include <string>
#include <list>

#include "AbstractGraph.h"

namespace SGL {

template<typename T>
class Adjacency_List : public AbstractGraph<T> {
public:
	// Constructors
	explicit Adjacency_List(int p_flags = 0);
	Adjacency_List(const Adjacency_List& p_src);
	Adjacency_List(const Adjacency_List& p_src, const std::vector<T>& p_filter);
	// Destructor
	~Adjacency_List();
	// Operator =
	const Adjacency_List& operator =(const Adjacency_List &p_src);

	// Getters (const)
	/**
	 * \brief Tells if a vertex is a source (no edges coming to it = in-degree 0)
	 * \return (boolean) whether the vertex is a source or not
	 */
	inline bool vertexIsSource(const T &p_v) const {
		return (vertexInDegree(p_v) == 0);
	}

	/**
	 * \brief Tells if a vertex is a sink (no edges starting from it = out-degree = 0)
	 * \return (boolean) whether the vertex is a sink or not
	 */
	inline bool vertexIsSink(const T &p_v) const {
		return (vertexOutDegree(p_v) == 0);
	}

	/**
	 * \brief Returns the number of vertices in the list
	 * \return the number of vertices in the list
	 */
	inline unsigned int nbVertices() const {
		return m_nodes.size();
	}

	/**
	 * \brief Alias of the nbVertices method
	 * "order" is the mathematical term for "number of vertices"
	 * \return the number of vertices in the list
	 */
	inline unsigned int order() const {
		return m_nodes.size();
	}

	/**
	 * \brief Returns the number of edges in the list
	 * \return the number of edges in the list
	 */
	inline unsigned int nbEdges() const {
		return edges().size();
	}

	/**
	 * \brief Alias of the nbEdges method
	 * "size" is the mathematical term for "number of edges" (not to be mistaken with order, the number of vertices)
	 * \return the number of edges in the list
	 */
	inline unsigned int size() const {
		return edges().size();
	}

	bool			hasVertex(const T &) const;
	unsigned int	vertexInDegree(const T &) const;
	unsigned int	vertexOutDegree(const T &) const;
	std::vector<T>	vertexNeighborhood(const T&, bool p_closed = false) const;
	bool			hasEdge(const T &, const T &) const;
	std::vector<T>	vertices() const;
	std::vector<std::pair<T, T> > edges() const;

	// Setters (mutators)
	void addVertex(const T &);
	void deleteVertex(const T &);
	void addEdge(const T&, const T&);
	void deleteEdge(const T&, const T&);

	// Others
	void display() const;
	bool equals(const Adjacency_List &p_g2) const;

	/**
	 * \brief Overloads the == operator to check structural equality of two graphs. Calls equals method.
	 * \param[in] p_g2 the second graph
	 * \return whether the two lists are structurally equal or not
	 */
	inline bool operator==(const Adjacency_List &p_g2) { return equals(p_g2); }


	friend inline std::ostream &operator<<(std::ostream &p_stream,
			const Adjacency_List &p_graph) {
		p_stream << p_graph._repr();
		return p_stream;
	}


private:
	/**
	 * \class Node
	 * \brief Internal class of the list.
	 */
	class Node {
	public:
		T m_data; /*!< data of a vertex */
		std::list<T> m_neighbors; /*!< this list contains all the data of all vertex's neighbors */

		Node(const T& p_data) : m_data(p_data) {}
	};
	std::vector<Node *> m_nodes; /*!< internal container for the adjacency list nodes */

	void	_copyAdjacencyList(const Adjacency_List &p_src);
	int		_index(const T &p_v) const;
	const std::string _repr() const;
};


}

#include "AdjacencyList.hpp"

#endif /* ADJACENCYLIST_H_ */
