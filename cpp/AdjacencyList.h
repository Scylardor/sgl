//! \file AdjacencyList.h
//! \brief Declaration of a generic adjacency list for usage in a graph
//! \author baron_a
//! \version 0.1
//! \date Oct 19, 2013

#ifndef ADJACENCYLIST_H_
#define ADJACENCYLIST_H_

#include <vector>
#include <string>

#include "AbstractGraph.h"
#include "components.h"

namespace SGL {

template<typename T>
class adjacency_list : public IGraph<T> {
public:

	////////////////////////////////////////////////////////////////
	// Coplien Form
	////////////////////////////////////////////////////////////////
	adjacency_list(configuration p_f = 0);
	adjacency_list(const adjacency_list &);
	~adjacency_list() {}
	adjacency_list &operator=(const adjacency_list &);

	////////////////////////////////////////////////////////////////
	// Getters (const)
	////////////////////////////////////////////////////////////////
	/**
	 * \brief Returns the number of vertices in the matrix
	 * \return the number of vertices in the matrix
	 */
	inline unsigned nb_vertices() const { return m_nodes.size(); }

	/**
	 * \brief Returns the number of edges in the list
	 * \return the number of edges in the list
	 */
	unsigned nb_edges() const { return edges().size(); };

	/**
	 * \brief Alias of the nbVertices method
	 * "order" is the mathematical term for "number of vertices"
	 * \return the number of vertices in the list
	 */
	inline unsigned int order() const { return nb_vertices(); }

	/**
	 * \brief Alias of the nbEdges method
	 * "size" is the mathematical term for "number of edges" (not to be mistaken with order, the number of vertices)
	 * \return the number of edges in the list
	 */
	inline unsigned int size() const { return nb_edges(); }

	/**
	 * \brief Retrieve the configuration of the graph
	 * It roughly is an int which you can bitwise-and and bitwise-or to know which configuration stands for this graph
	 * \return the configuration of the graph
	 */
	inline configuration getConfiguration() const { return this->m_config; }

	/**
	 * \brief Lets the user know whether a graph has a given configuration (e.g. if it's directed, weighted...)
	 * \param[in] p_config the configuration we want to know the graph has or not
	 * \return true if the graph holds this configuration
	 */
	inline bool hasConfiguration(configuration p_config) const { return (this->m_config & p_config); }

	bool has_vertex(const T &) const;
	bool vertex_is_source(const T &) const;
	bool vertex_is_sink(const T &) const;
	unsigned vertex_in_degree(const T &) const;
	unsigned vertex_out_degree(const T &) const;
	std::vector<T> vertex_neighborhood(const T&, bool p_closed = false) const;
	std::vector<T> vertices() const;
	bool has_edge(const T &, const T &) const;
	std::vector<std::pair<T, T> > edges() const;


	////////////////////////////////////////////////////////////////
	// Setters (mutators)
	////////////////////////////////////////////////////////////////
	void add_vertex(const T &);
	void delete_vertex(const T &);
	void add_edge(const T&, const T&);
	void delete_edge(const T&, const T&);

	////////////////////////////////////////////////////////////////
	// Others
	////////////////////////////////////////////////////////////////
	bool operator==(const adjacency_list &p_rhs) const;

//	friend inline std::ostream &operator<<(std::ostream &p_stream, const adjacency_list &p_list) { p_stream << p_list._repr(); return p_stream; }

private:
	/**
	 * \class Edge
	 * \brief Internal representation of an edge in the adjacency list.
	 */
	class Edge {
	public:
		Edge(unsigned p_dest_idx, int p_weight=0) : m_dest(p_dest_idx), m_weight(p_weight) {}
		~Edge() {}

		unsigned m_dest;
		int	m_weight;
	};

	/**
	 * \class Node
	 * \brief Internal representation of a vertex in the adjacency list.
	 */
	class Node {
	public:
		T m_data; /*!< data of a vertex */
		std::vector<Edge> m_edges; /*!< this list contains all the edges the vertex is the source of */

		Node(const T& p_data) : m_data(p_data) {}
		Node(const Node & p_src) : m_data(p_src.m_data), m_edges(p_src.m_edges) {}
	};
	std::vector<Node> m_nodes; /*!< internal container for the adjacency list nodes */

	void	_copyAdjacencyList(const adjacency_list &p_src);
	unsigned _index(const T &p_v) const;
	unsigned _edgeIndex(unsigned, unsigned) const;
	const std::string _repr() const;
};


}

#include "AdjacencyList.hpp"

#endif /* ADJACENCYLIST_H_ */
