//! \file AbstractGraph.h
//! \brief The interface for abstract generic graphs (including adjacency matrix and list)
//! \author baron_a
//! \version 0.2
//! \date Oct 23, 2013

#ifndef ABSTRACTGRAPH_H_
#define ABSTRACTGRAPH_H_

namespace SGL {

typedef enum Graph_Traits {
  Directed = 1,
  Dir = 1,
  D = 1,
  Undirected = 2,
  Undir = 2,
  Weighted = 4,
  Wei = 4,
  W = 4,
  Unweighted = 8,
  Unwei = 8,
  DirectedWeighted = Directed|Weighted,
  DirWei = DirectedWeighted,
  DW = DirectedWeighted
} Graph_Traits;



/**
 * \class IGraph
 *
 * \brief Interface of a generic graph.
 * The goal of this class is to implement a graph as generic as it can be.
 * Note: this class is purely virtual. It is only used for inheritance purposes and can't be used on itself.
 */
template <typename T>
class IGraph {
public:
	virtual ~IGraph() {}

	// Getters (const)
	virtual bool vertex_is_source(const T &p_v) const = 0;
	virtual bool vertex_is_sink(const T &p_v) const = 0;
	virtual bool has_vertex(const T &) const = 0;
	virtual unsigned vertex_in_degree(const T &) const = 0;
	virtual unsigned vertex_out_degree(const T &) const = 0;
	virtual std::vector<T> vertex_neighborhood(const T&,
			bool p_closed = false) const = 0;
	virtual std::vector<T> vertices() const = 0;
	virtual unsigned nb_vertices() const = 0;
	virtual unsigned order() const = 0; // same as nb_vertices (mathematical term)

	virtual bool has_edge(const T &, const T &) const = 0;
	virtual std::vector<std::pair<T, T> > edges() const = 0;
	virtual unsigned nb_edges() const = 0;
	virtual unsigned size() const = 0; // same as nb_edges (mathematical term)

	// Setters (mutators)
	virtual void add_vertex(const T &) = 0;
	virtual void delete_vertex(const T &) = 0;

	virtual void add_edge(const T&, const T&) = 0;
	virtual void delete_edge(const T&, const T&) = 0;

protected:
	int m_config;
	unsigned m_nbVertices; /// the order (number of vertices) of the graph
};

}

#endif /* ABSTRACTGRAPH_H_ */
