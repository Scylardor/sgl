/**
 * \file AdjacencyMatrix.h
 * \brief Class of the generic template class adjacency_matrix inheriting from AbstractGraph
 * \author Alexandre Baron
 * \version 0.2
 * \date 2013, October
 *
 * An adjacency matrix definition.
 */

#ifndef _ADJACENCYMATRIX_H
#define _ADJACENCYMATRIX_H

#include <vector>
#include <string>

#include "AbstractGraph.h"
#include "components.h"

namespace SGL {
/**
 * \class adjacency_matrix
 *
 * \brief Class representing an adjacency matrix
 * for internal use by a graph
 */
template <typename T, int graph_traits>
class adjacency_matrix : public IGraph<T> {
public:
	////////////////////////////////////////////////////////////////
	// Coplien Form
	////////////////////////////////////////////////////////////////
	adjacency_matrix(configuration p_f = 0);
	adjacency_matrix(const adjacency_matrix &);
	~adjacency_matrix() { delete m_matrix; }
	adjacency_matrix &operator=(const adjacency_matrix &);

	////////////////////////////////////////////////////////////////
	// Getters (const)
	////////////////////////////////////////////////////////////////
	/**
	 * \brief Returns the number of vertices in the matrix
	 * \return the number of vertices in the matrix
	 */
	inline unsigned nb_vertices() const { return this->m_nbVertices; }

	/**
	 * \brief Returns the number of edges in the list
	 * \return the number of edges in the list
	 */
	inline unsigned nb_edges() const { return m_matrix->nbEdges(); }

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
	bool operator==(const adjacency_matrix &p_rhs) const;

	friend inline std::ostream &operator<<(std::ostream &p_stream, const adjacency_matrix &p_matrix) { p_stream << p_matrix._repr(); return p_stream; }


private:
	class IMatrix {
	public:
		virtual ~IMatrix() {}

		virtual bool hasEdge(unsigned, unsigned) const = 0;
		virtual unsigned nbEdges() const = 0;
		virtual void edges(std::vector<std::vector<int> > &) const = 0;

		virtual void addVertex() = 0;
		virtual void deleteVertex(unsigned) = 0;
		virtual void addEdge(unsigned, unsigned) = 0;
		virtual void deleteEdge(unsigned, unsigned) = 0;
	};

	class DirectedMatrix : public IMatrix {
	public:
		DirectedMatrix() {}
		~DirectedMatrix() {}

		bool hasEdge(unsigned, unsigned) const;
		unsigned nbEdges() const;
		void edges(std::vector<std::vector<int> > &) const;

		void addVertex();
		void deleteVertex(unsigned);
		void addEdge(unsigned, unsigned);
		void deleteEdge(unsigned, unsigned);

	private:
		std::vector<std::vector<int> > m_matrix;
	};

	class UndirectedMatrix : public IMatrix {
	public:
		UndirectedMatrix() {}
		~UndirectedMatrix() {}

		bool hasEdge(unsigned, unsigned) const;
		unsigned nbEdges() const;
		void edges(std::vector<std::vector<int> > &) const;

		void addVertex();
		void deleteVertex(unsigned);
		void addEdge(unsigned, unsigned);
		void deleteEdge(unsigned, unsigned);

	private:
		unsigned _calcActualIndex(unsigned, unsigned) const;
		unsigned _nbVertices() const;

		std::vector<int> m_matrix;
	};

	std::vector<T> m_elems; /*!< all the vertices */
	IMatrix *m_matrix; /*!< the adjacency matrix itself */

	unsigned _index(const T &p_v) const;
	const std::string _repr() const;
};


} // namespace SGL

#include "AdjacencyMatrix.hpp"

#endif
