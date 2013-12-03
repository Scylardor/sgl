//! \file AdjacencyList.hpp
//! \brief Implementation of a generic graph adjacency list
//! \author baron_a
//! \version 0.1
//! \date Oct 19, 2013

#include <stdexcept>

using namespace std;

namespace SGL {

/**
 *  \brief Constructor
 *  \pre Enough memory available
 *  \param[in] p_flags the configuration flags of the graph
 *  \exception bad_alloc in case of insufficient memory
 */
template<typename T>
Adjacency_List<T>::Adjacency_List(configuration p_flags) {
	this->m_config = p_flags;
}

template<typename T>
Adjacency_List<T>::Adjacency_List(const Adjacency_List<T> &p_src) {
	// TODO : refactor this function
	// copies the nodes and the edges at the same time
	for (unsigned v = 0; v < p_src.m_nodes.size(); v++) {
		Node copy(p_src.m_nodes[v]);

		m_nodes.push_back(copy);
	}
	this->m_nbVertices = p_src.m_nbVertices;
}

template<typename T>
bool Adjacency_List<T>::hasVertex(const T & p_elem) const {
	bool present = true;

	try {
		_index(p_elem);
	} catch (const logic_error &) {
		present = false;
	}
	return present;
}

template<typename T>
bool Adjacency_List<T>::vertexIsSource(const T &p_elem) const {
	if (hasConfiguration(UNDIRECTED)) {
		throw logic_error("vertexIsSource: the graph is undirected");
	}
	return (vertexInDegree(p_elem) == 0);
}

template<typename T>
bool Adjacency_List<T>::vertexIsSink(const T &p_elem) const {
	if (hasConfiguration(UNDIRECTED)) {
		throw logic_error("vertexIsSink: the graph is undirected");
	}
	return (vertexOutDegree(p_elem) == 0);
}

template<typename T>
unsigned Adjacency_List<T>::vertexInDegree(const T &p_v) const {
	unsigned inDeg = 0;
	unsigned v_idx = _index(p_v); // throws logic error if the elem's not in the graph

	for (unsigned v = 0; v < m_nodes.size(); v++) {
		for (unsigned edge_idx = 0; edge_idx != m_nodes[v].m_edges.size(); edge_idx++) {
			if (m_nodes[v].m_edges[edge_idx].m_dest == v_idx) {
				inDeg++;
				// if the graph is undirected: a loop counts twice
				if (v == v_idx && hasConfiguration(UNDIRECTED)) {
					inDeg++;
				}
			}
		}
	}
	return inDeg;
}

template<typename T>
unsigned Adjacency_List<T>::vertexOutDegree(const T &p_v) const {
	unsigned v_idx = _index(p_v); // throws logic error if the elem's not in the graph
	unsigned outDeg = m_nodes[v_idx].m_edges.size();
	// if the graph is undirected: a loop counts twice
	if (hasConfiguration(UNDIRECTED) && hasEdge(p_v, p_v)) {
		outDeg++;
	}
	return outDeg;
}

template<typename T>
std::vector<T> Adjacency_List<T>::vertexNeighborhood(const T &p_v, bool p_closed) const {
	unsigned v_idx = _index(p_v); // throws logic error if the elem's not in the graph
	vector<T> neighbors;

	for (unsigned edge_idx = 0; edge_idx != m_nodes[v_idx].m_edges.size(); edge_idx++) {
		unsigned nghbr_idx = m_nodes[v_idx].m_edges[edge_idx].m_dest; // get the neighbor index stored in the edge

		neighbors.push_back(m_nodes[nghbr_idx].m_data);
	}
	if (p_closed) {
		neighbors.push_back(m_nodes[v_idx].m_data);
	}
	return neighbors;
}

template<typename T>
std::vector<T> Adjacency_List<T>::vertices() const {
	vector<T> vertices;

	for (unsigned idx = 0; idx != m_nodes.size(); idx++) {
		vertices.push_back(m_nodes[idx].m_data);
	}
	return vertices;
}

template<typename T>
bool Adjacency_List<T>::hasEdge(const T &p_src, const T &p_dest) const {
	unsigned src_idx = _index(p_src); // throws logic error if the elem's not in the graph
	unsigned dest_idx = _index(p_dest); // throws logic error if the elem's not in the graph
	bool present = true;

	try {
		_edgeIndex(src_idx, dest_idx);
	} catch (const logic_error &) {
		present = false;
	}
	return present;
}

template<typename T>
std::vector<std::pair<T, T> > Adjacency_List<T>::edges() const {
	vector<pair<T, T> > edges;

	for (unsigned idx = 0; idx != m_nodes.size(); idx++) {
		for (unsigned edge_idx = 0; edge_idx < m_nodes[idx].m_edges.size(); edge_idx++) {
			unsigned dest_idx = m_nodes[idx].m_edges[edge_idx].m_dest;
			pair<T, T> newedge = make_pair(m_nodes[idx].m_data, m_nodes[dest_idx].m_data);

			edges.push_back(newedge);
		}
	}
	return edges;
}

template<typename T>
void Adjacency_List<T>::addVertex(const T &p_elem) {
	if (hasVertex(p_elem)) {
		throw logic_error("This element is already in the graph");
	}
	Node newnode(p_elem);

	m_nodes.push_back(newnode);
	this->m_nbVertices++;
}

template<typename T>
void Adjacency_List<T>::deleteVertex(const T &p_v) {
	unsigned v_idx = _index(p_v); // throws logic error if the elem's not in the graph

	m_nodes.erase(m_nodes.begin() + v_idx); // erase the node itself
	// next, erase the edges coming to this vertex in other nodes
	// and update the referred node indexes for each remaining vertex
	for (unsigned i = 0; i < m_nodes.size(); i++) {
		// search for the vertex index
		bool present = false;
		unsigned erase_idx;

		for (unsigned edge_idx = 0; edge_idx < m_nodes[i].m_edges.size(); edge_idx++) {
			if (m_nodes[i].m_edges[edge_idx].m_dest == v_idx) {
				present = true;
				erase_idx = edge_idx;
			}
			else if (m_nodes[i].m_edges[edge_idx].m_dest > v_idx) { // update the vertices indexes
				m_nodes[i].m_edges[edge_idx].m_dest--; // because all the next indexes have been shifted by one
			}
			if (present) {
				m_nodes[i].m_edges.erase(m_nodes[i].m_edges.begin() + erase_idx); // delete the edge going to the deleted vertex
			}
		}
	}
	this->m_nbVertices--;
}

template<typename T>
void Adjacency_List<T>::addEdge(const T &p_src, const T & p_dest) {
	unsigned src_idx = _index(p_src);   // throws logic error if the elem's not in the graph
	unsigned dest_idx = _index(p_dest); // throws logic error if the elem's not in the graph

	if (hasEdge(p_src, p_dest)) {
		throw logic_error("This edge already exists");
	}
	Edge newedge(dest_idx);

	m_nodes[src_idx].m_edges.push_back(newedge);
	// if the graph is undirected : also add an edge in the other way,
	// except when we do a loop (an edge from a vertex to the same vertex).
	if (src_idx != dest_idx && hasConfiguration(UNDIRECTED)) {
		if (hasEdge(p_dest, p_src)) {
			throw logic_error("This edge already exists"); // since edges add in pairs in an undirected graph, actually shouldn't happen
		}
		Edge newedge(src_idx);

		m_nodes[dest_idx].m_edges.push_back(newedge);
	}
}

template<typename T>
void Adjacency_List<T>::deleteEdge(const T &p_src, const T & p_dest) {
	unsigned src_idx = _index(p_src); // throws logic error if the elem's not in the graph
	unsigned dest_idx = _index(p_dest); // throws logic error if the elem's not in the graph
	unsigned edge_idx = _edgeIndex(src_idx, dest_idx); // throws logic error if no such edge

	m_nodes[src_idx].m_edges.erase(m_nodes[src_idx].m_edges.begin() + edge_idx);
	if (hasConfiguration(UNDIRECTED)) {
		unsigned edge_idx = _edgeIndex(dest_idx, src_idx); // throws logic error if no such edge

		m_nodes[dest_idx].m_edges.erase(m_nodes[dest_idx].m_edges.begin() + edge_idx);
	}
}

template<typename T>
unsigned Adjacency_List<T>::_index(const T &p_v) const {
	for (unsigned i = 0; i < m_nodes.size(); i++) {
		if (m_nodes[i].m_data == p_v) {
			return i;
		}
	}
	throw logic_error("This element is not in the graph");
}

template<typename T>
unsigned Adjacency_List<T>::_edgeIndex(unsigned p_idx_src, unsigned p_idx_dest) const {
	for (unsigned edge_idx = 0; edge_idx < m_nodes[p_idx_src].m_edges.size(); edge_idx++) {
		if (m_nodes[p_idx_src].m_edges[edge_idx].m_dest == p_idx_dest) {
			return edge_idx;
		}
	}
	throw logic_error("No such edge in the graph");
}

} // namespace SGL
