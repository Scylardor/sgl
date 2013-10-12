/**
 * \file SGLGraph.hpp
 * \brief SGLGraph implementation.
 * \author Alexandre Baron
 * \version 0.1
 * \date 2013, October
 *
 * Implementation of a generic graph with an adjacency list
 */

#include <algorithm>

#include "SGLGraph.h"

using namespace std;

namespace SGL {

/**
 *  \brief Constructor
 *
 *  \pre Enough memory available
 *  \exception bad_alloc in case of insufficient memory
 */
template<typename T>
SGLGraph<T>::SGLGraph() {
}


/**
 *  \brief Copy constructor
 *
 *  \pre Enough memory available
 *  \exception bad_alloc in case of insufficient memory
 */
template<typename T>
SGLGraph<T>::SGLGraph(const SGLGraph &p_src) {
	_copyAdjacencyList(p_src);
}


/**
 *  \brief Constructor of a sub-graph of the original, using a filter vector
 * \pre Enough memory available
 * \pre All the vertices in the filter vector must be in the source graph
 * \post a deep copy of the graph is obtained, with only the vertices contained in the filter vector
 * \exception bad_alloc in case of insufficient memory
 * \exception logic_error if a vertex in filter vector isn't contained in the source graph
 */
template<typename T>
SGLGraph<T>::SGLGraph(const SGLGraph &p_src, const vector<T> &p_filter) {
	for (typename vector<T>::const_iterator vertex = p_filter.begin();
			vertex != p_filter.end(); ++vertex) {
		if (!p_src.hasVertex((*vertex))) {
			throw logic_error(
					"SGLGraph: a filter vector's vertex isn't in the source graph");
		}
		addVertex((*vertex));
	}
}


/**
 *  \brief Destructor
 */
template<typename T>
SGLGraph<T>::~SGLGraph() {
	for (unsigned int pos = 0; pos < m_nodes.size(); pos++) {
		delete m_nodes[pos];
	}
}


/**
 * \brief Assignment operator overloading
 *
 * \pre Enough memory available
 * \post A deep copy is returned
 * \exception bad_alloc in case of insufficient memory
 */
template<typename T>
const SGLGraph<T> & SGLGraph<T>::operator =(const SGLGraph<T> &p_src) {
	SGLGraph<T> temp(p_src);

	std::swap(m_nodes, temp.m_nodes);
	return *this;
}


/**
 *  \brief Adds a vertex to the graph
 *
 * \pre Enough memory available
 * \pre The vertex isn't already in the graph
 * \post The graph counts one more vertex
 * \exception bad_alloc in case of insufficient memory
 * \exception logic_error if the vertex already is in the graph
 */
template<typename T>
void SGLGraph<T>::addVertex(const T &p_s) {
	if (hasVertex(p_s)) {
		throw logic_error("addVertex: this vertex is already in the graph");
	}
	Node *newv = new Node(p_s);

	m_nodes.push_back(newv);
}


/**
 *  \brief Adds an edge in the graph
 *
 * \pre Enough memory available
 * \pre The 2 vertices of the edge are in the graph
 * \post The graph counts one more edge
 * \exception bad_alloc in case of insufficient memory
 * \exception logic_error if one of the two vertices isn't in the graph
 */
template<typename T>
void SGLGraph<T>::addEdge(const T &p_s1, const T &p_s2) {
	int index_s1, index_s2;
	try {
		index_s1 = _index(p_s1);
		index_s2 = _index(p_s2);
	} catch (const logic_error &le) {
		throw logic_error("addEdge: one of the vertices isn't in the graph");
	}
	m_nodes[index_s1]->m_neighbors.push_back(m_nodes[index_s2]);
}


/**
 *  \brief Deletes an edge in the graph
 *
 * \pre The 2 vertices of the edge are in the graph
 * \post The graph counts one less edge
 * \exception logic_error if one of the two vertices isn't in the graph
 */
template<typename T>
void SGLGraph<T>::deleteEdge(const T &p_s1, const T &p_s2) {
	int index_s1, index_s2;
	try {
		index_s1 = _index(p_s1);
		index_s2 = _index(p_s2);
	} catch (const logic_error &le) {
		throw logic_error("deleteEdge: one of the vertices isn't in the graph");
	}
	m_nodes[index_s1]->m_neighbors.remove(m_nodes[index_s2]->m_data);
}


/**
 *  \brief deletes a vertex from the graph
 *
 * \pre The vertex is in the graph
 * \post The graph counts one less vertex
 * \exception logic_error if the vertex isn't in the graph
 */
template<typename T>
void SGLGraph<T>::deleteVertex(const T &p_s) {
	int index_s;

	try {
		index_s = _index(p_s);
	} catch (const logic_error &le) {
		throw logic_error("deleteVertex: the vertex isn't in the graph");
	}
	for (unsigned int pos = 0; pos != m_nodes.size(); pos++) {
		m_nodes[pos]->m_neighbors.remove(m_nodes[index_s]->m_data);
	}
	delete m_nodes[index_s];
	m_nodes.erase(m_nodes.begin() + index_s);
}


/**
 *  \brief verifies that a vertex is in the graph
 *
 * \post The graph remains unchanged
 */
template<typename T>
bool SGLGraph<T>::hasVertex(const T &p_s) const {
	bool isHere = true;

	try {
		_index(p_s);
	} catch (const logic_error &le) {
		isHere = false;
	}
	return isHere;
}


/**
 * \brief verifies that an edge is in the graph
 * \pre The 2 vertices of the edge are in the graph
 * \post The graph remains unchanged
 * \exception logic_error if one of the two vertices isn't in the graph
 */
template<typename T>
bool SGLGraph<T>::hasEdge(const T &p_s1, const T &p_s2) const {
	bool isHere = true;
	int index_s1, index_s2;

	try {
		index_s1 = _index(p_s1);
		index_s2 = _index(p_s2);
	} catch (const logic_error &le) {
		throw logic_error("hasEdge: one of the vertices isn't in the graph");
	}
	if (std::find(m_nodes[index_s1]->m_neighbors.begin(),
			m_nodes[index_s1]->m_neighbors.end(), m_nodes[index_s2]->m_data)
			== m_nodes[index_s1]->m_neighbors.end()) {
		isHere = false;
	}
	return isHere;
}


/**
 *  \brief Returns the number of vertices in the graph
 *
 * \post The graph remains unchanged
 */
template<typename T>
unsigned int SGLGraph<T>::order() const {
	return m_nodes.size();
}


/**
 *  \brief Returns the number of edges in the graph
 *
 * \post The graph remains unchanged
 */
template<typename T>
unsigned int SGLGraph<T>::size() const {
	unsigned int order = 0;

	for (unsigned int pos = 0; pos < m_nodes.size(); pos++) {
		order += m_nodes[pos]->m_neighbors.size();
	}
	return order;
}


/**
 *  \brief Lists all the vertices in the graph
 *
 * Returns in a vector all the vertices of the graph
 * \pre Enough memory available
 * \post A vector of all the vertices data is returned
 * \exception bad_alloc in case of insufficient memory
 */
template<typename T>
std::vector<T> SGLGraph<T>::vertices() const {
	vector<T> elems;

	elems.reserve(m_nodes.size());
	for (unsigned int pos = 0; pos < m_nodes.size(); pos++) {
		elems.push_back(m_nodes[pos]->m_data);
	}
	return elems;
}


/**
 *  \brief Returns the in-degree of a vertex in the graph
 *  i.e. the number of neighbor vertices of this vertex which have an edge that
 *  goes to it.
 *
 * \pre The vertex has to be in the graph
 * \post The graph remains unchanged
 * \exception logic_error if the vertex isn't in the graph
 * \return the in-degree of a vertex in the graph
 */
template<typename T>
unsigned int SGLGraph<T>::vertexInDegree(const T &p_v) const {
	if (!hasVertex(p_v)) {
		throw logic_error("vertexInDegree: the vertex isn't in the graph");
	}
	unsigned int inDegree = 0;

	for (unsigned int pos = 0; pos < m_nodes.size(); pos++) {
		if (hasEdge(m_nodes[pos]->m_data, p_v)) {
			inDegree++;
		}
	}
	return inDegree;
}


/**
 *  \brief Returns the out-degree of a vertex in the graph,
 *  i.e. the number of edges with other vertices it is the source of.
 *
 * \pre The vertex must be in the graph
 * \post The graph remains unchanged
 * \exception logic_error if the vertex isn't in the graph
 */
template<typename T>
unsigned int SGLGraph<T>::vertexOutDegree(const T &p_s) const {
	if (!hasVertex(p_s)) {
		throw logic_error("vertexOutDegree: the vertex isn't in the graph");
	}
	return m_nodes[_index(p_s)]->m_neighbors.size();
}



/**
 *  \brief Lists the adjacent vertices of a vertex in the graph.
 *  If closed boolean is set to true, the vertex itself will be included in the returned neighborhood,
 *  making it a closed neighborhood (as opposed to the open version, without it included).
 *
 * \pre Enough memory available
 * \pre The vertex has to be in the graph
 * \post The graph remains unchanged
 * \exception bad_alloc in case of insufficient memory
 * \exception logic_error if the vertex isn't in the graph
 * \return A vector containing the data of all neighbor vertices of the vertex
 */
template<typename T>
std::vector<T> SGLGraph<T>::vertexNeighborhood(const T &p_s,
		bool p_closed) const {
	if (!hasVertex(p_s)) {
		throw logic_error("vertexNeighborhood: the vertex isn't in the graph");
	}
	vector<T> adjs;
	unsigned int index_v = _index(p_s);

	for (unsigned int pos = 0; pos < m_nodes.size(); pos++) {
		Node *cur = m_nodes[pos];

		if (pos == index_v) {
			// if we find the node of the given vertex, we add to the vector
			// all the vertices it points to, after having checked they're not already in it
			for (typename list<T>::const_iterator node = cur->m_neighbors.begin();
					node != cur->m_neighbors.end(); ++node) {
				if (std::find(adjs.begin(), adjs.end(), m_nodes[pos]->m_data)
						== adjs.end()) {
					adjs.push_back(m_nodes[pos]->m_data);
				}
			}
		} else {
			// for any other vertex, we check if the given vertex is one of the neighbors.
			// if it is, add this vertex to the vector after having checked it isn't already in it
			if (std::find(cur->m_neighbors.begin(), cur->m_neighbors.end(),
					m_nodes[index_v]->m_data) != cur->m_neighbors.end()) {
				if (std::find(adjs.begin(), adjs.end(), cur->m_data)
						== adjs.end()) {
					adjs.push_back(cur->m_data);
				}
			}
		}
	}
	return adjs;
}

/**
 *  \brief Displays a representation of the graph
 *  \pre The type contained by the graph must have declared an overloading of the << operator for ostreams
 *  	 in order to be printed out by the function
 * \post The graph remains unchanged
 */

template<typename T>
void SGLGraph<T>::display() const {
	cout << "Number of vertices: " << order() << endl;
	cout << "Number of edges: " << size() << endl;
	cout << "List of vertices and their edges:" << endl << endl;
	for (unsigned int pos = 0; pos < m_nodes.size(); pos++) {
		Node *cur = m_nodes[pos];

		cout << "Vertex: " << cur->m_data << endl;
		cout << "Source of " << cur->m_neighbors.size() << " edges:" << endl;
		for (typename list<T>::const_iterator v = cur->m_neighbors.begin();
				v != cur->m_neighbors->end(); ++v) {
			cout << (*v);
			cout << endl;
		}
		if (cur->m_neighbors.size() == 0) {
			cout << "No edges" << endl;
		}
		cout << endl;
	}
	if (m_nodes.size() == 0)
		cout << "Empty graph" << endl;
}

template<typename T>
void SGLGraph<T>::_copyAdjacencyList(const SGLGraph &p_src) {
	for (unsigned int pos = 0; pos < p_src.size(); pos++) {
		addVertex(p_src.m_nodes[pos]->m_data);
	}
	for (unsigned int pos = 0; pos < p_src.size(); pos++) {
		Node *cur = p_src.m_nodes[pos];

		for (typename list<T>::const_iterator v = cur->m_neighbors.begin();
				v != cur->m_neighbors->end(); ++v) {
			addEdge(p_src.m_nodes[pos]->m_data, (*v)->m_data);
		}
	}
}

template<typename T>
int SGLGraph<T>::_index(const T &p_v) const {
	int index = -1;

	for (unsigned int pos = 0; pos < m_nodes.size(); pos++) {
		if (m_nodes[pos]->m_data == p_v) {
			index = pos;
			break;
		}
	}
	if (index == -1) {
		throw logic_error("Vertex not in the graph");
	}
	return index;
}

} //Fin du namespace
