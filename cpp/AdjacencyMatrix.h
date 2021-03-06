/**
 * \file AdjacencyMatrix.h
 * \brief Class of the generic template class Adjacency_Matrix inheriting from AbstractGraph
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
#include <set>

#include "AbstractGraph.h"
#include "components.h"

namespace SGL {
/**
 * \class Adjacency_Matrix
 *
 * \brief Class representing an adjacency matrix
 * for internal use by a graph
 */
template <typename T>
class Adjacency_Matrix : public AbstractGraph<T> {
public:
	////////////////////////////////////////////////////////////////
	// Coplien Form
	////////////////////////////////////////////////////////////////
	Adjacency_Matrix(configuration p_f = 0);
	Adjacency_Matrix(const Adjacency_Matrix &);
	~Adjacency_Matrix() { delete m_matrix; }
	Adjacency_Matrix &operator=(const Adjacency_Matrix &);

	////////////////////////////////////////////////////////////////
	// Getters (const)
	////////////////////////////////////////////////////////////////
	/**
	 * \brief Returns the number of vertices in the matrix
	 * \return the number of vertices in the matrix
	 */
	inline unsigned nbVertices() const { return this->m_nbVertices; }

	/**
	 * \brief Returns the number of edges in the list
	 * \return the number of edges in the list
	 */
	inline unsigned nbEdges() const { return m_matrix->nbEdges(); }

	/**
	 * \brief Alias of the nbVertices method
	 * "order" is the mathematical term for "number of vertices"
	 * \return the number of vertices in the list
	 */
	inline unsigned int order() const { return nbVertices(); }

	/**
	 * \brief Alias of the nbEdges method
	 * "size" is the mathematical term for "number of edges" (not to be mistaken with order, the number of vertices)
	 * \return the number of edges in the list
	 */
	inline unsigned int size() const { return nbEdges(); }

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

	bool hasVertex(const T &) const;
	bool vertexIsSource(const T &) const;
	bool vertexIsSink(const T &) const;
	unsigned vertexInDegree(const T &) const;
	unsigned vertexOutDegree(const T &) const;
	std::vector<T> vertexNeighborhood(const T&, bool p_closed = false) const;
	std::vector<T> vertices() const;
	bool hasEdge(const T &, const T &) const;
	std::vector<std::pair<T, T> > edges() const;


	////////////////////////////////////////////////////////////////
	// Setters (mutators)
	////////////////////////////////////////////////////////////////
	void addVertex(const T &);
	void deleteVertex(const T &);
	void addEdge(const T&, const T&);
	void deleteEdge(const T&, const T&);

	////////////////////////////////////////////////////////////////
	// Others
	////////////////////////////////////////////////////////////////
	bool operator==(const Adjacency_Matrix &p_rhs) const;

	friend inline std::ostream &operator<<(std::ostream &p_stream, const Adjacency_Matrix &p_matrix) { p_stream << p_matrix._repr(); return p_stream; }


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
