/**
 * \file AdjacencyMatrix.hpp
 * \brief Adjacency Matrix implementation.
 * \author Alexandre Baron
 * \version 0.1
 * \date 2013, October
 *
 * Implementation of a generic adjacency matrix for internal use in a graph
 */

#include "AdjacencyMatrix.h"

using namespace std;

namespace SGL {

template <typename T>
Adjacency_Matrix<T>::Adjacency_Matrix(unsigned int p_size) {
	if (p_size != 0) {
		m_elems.reserve(p_size);
		m_matrix.reserve(p_size);
	}
}

template <typename T>
Adjacency_Matrix<T>::~Adjacency_Matrix() {}


/**
 * \brief verifies that a vertex is in the graph
 * \param[in] p_s the element we search the vertex of
 * \post The graph remains unchanged
 * \return whether the graph contains this vertex or not
 */
template<typename T>
bool Adjacency_Matrix<T>::hasVertex(const T &p_s) const {
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
 * \param[in] p_s1 the source vertex of the edge
 * \param[in] p_s2 the destination vertex of the edge
 * \pre The 2 vertices of the edge are in the graph
 * \post The graph remains unchanged
 * \exception logic_error if one of the two vertices isn't in the graph
 * \return whether the graph contains this edge or not
 */
template<typename T>
bool Adjacency_Matrix<T>::hasEdge(const T &p_s1, const T &p_s2) const {
	bool isHere = true;
	int index_s1, index_s2;

	try {
		index_s1 = _index(p_s1);
		index_s2 = _index(p_s2);
	} catch (const logic_error &le) {
		throw logic_error("hasEdge: one of the vertices isn't in the graph");
	}
	isHere = (m_matrix[index_s1][index_s2] == 1);
	return isHere;
}


template <typename T>
void Adjacency_Matrix<T>::addVertex(const T &p_elem) {
	vector<int> newline(m_matrix.size(), 0);

	if (hasVertex(p_elem)) {
		throw logic_error("addVertex: Vertex already in the graph");
	}
	m_elems.push_back(p_elem);
	m_matrix.push_back(newline);
	for (unsigned i = 0; i < m_matrix.size(); i++) {
		m_matrix[i].push_back(0);
	}
}


/**
 * \brief deletes a vertex from the graph
 * \param[in] p_s The element we want to delete the vertex of
 * \pre The vertex is in the graph
 * \post The graph counts one less vertex
 * \exception logic_error if the vertex isn't in the graph
 */
template<typename T>
void Adjacency_Matrix<T>::deleteVertex(const T &p_s) {
	int index_s;

	try {
		index_s = _index(p_s);
	} catch (const logic_error &le) {
		throw logic_error("deleteVertex: the vertex isn't in the graph");
	}
	for (unsigned pos = 0; pos != m_elems.size(); pos++) {
		m_matrix[pos].erase(m_matrix[pos].begin() + index_s);
	}
	m_matrix.erase(m_matrix.begin() + index_s);
	m_elems.erase(m_elems.begin() + index_s);
}


/**
 * \brief Adds an edge in the graph
 * \param[in] p_s1 the source vertex of the edge
 * \param[in] p_s2 the destination vertex of the edge
 * \pre Enough memory available
 * \pre The 2 vertices of the edge are in the graph
 * \post The graph counts one more edge
 * \exception bad_alloc in case of insufficient memory
 * \exception logic_error if one of the two vertices isn't in the graph
 */
template<typename T>
void Adjacency_Matrix<T>::addEdge(const T &p_s1, const T &p_s2) {
	int index_s1, index_s2;
	try {
		index_s1 = _index(p_s1);
		index_s2 = _index(p_s2);
	} catch (const logic_error &le) {
		throw logic_error("addEdge: one of the vertices isn't in the graph");
	}
	m_matrix[index_s1][index_s2] = 1;
}


/**
 * \brief Deletes an edge in the graph
 * \param[in] p_s1 the source vertex of the edge
 * \param[in] p_s2 the destination vertex of the edge
 * \pre The 2 vertices of the edge are in the graph
 * \post The graph counts one less edge
 * \exception logic_error if one of the two vertices isn't in the graph
 */
template<typename T>
void Adjacency_Matrix<T>::deleteEdge(const T &p_s1, const T &p_s2) {
	int index_s1, index_s2;
	try {
		index_s1 = _index(p_s1);
		index_s2 = _index(p_s2);
	} catch (const logic_error &le) {
		throw logic_error("deleteEdge: one of the vertices isn't in the graph");
	}
	if (!hasEdge(p_s1, p_s2)) {
		throw logic_error("deleteEdge: no edge between the two vertices");
	}
	m_matrix[index_s1][index_s2] = 0;
}

template<typename T>
vector<T> Adjacency_Matrix<T>::vertices() const {
	vector<T> verts(m_elems);

	return verts;
}

/**
 * \brief Lists all the edges in the graph.
 * Returns all the edges under the form of a vector of pair of elements (source, destination)
 * \pre Enough memory available
 * \post A vector of all the edges is returned
 * \exception bad_alloc in case of insufficient memory
 * \return A vector of pairs of elements organized as (source, destination)
 */
template<typename T>
vector<pair<T, T> > Adjacency_Matrix<T>::edges() const {
	vector<pair<T, T> > edges;

	for (unsigned i = 0; i < m_matrix.size(); i++) {
		vector<int> line = m_matrix[i];

		for (unsigned j = 0; j != line.size(); j++) {
			if (line[j] == 1) {
				edges.push_back(make_pair(m_elems[i], m_elems[j]));
			}
		}
	}
	return edges;
}

/**
 * \brief Private function used to retrieve the index in the intern adjacency list of an element
 * \pre The vertex is in the graph
 * \param[in] p_v the vertex to search
 * \exception logic_error the vertex isn't in the graph
 * \return the index in the adjacency list of the given vertex's node
 */
template<typename T>
int Adjacency_Matrix<T>::_index(const T &p_v) const {
	int index = -1;

	for (unsigned pos = 0; pos < m_elems.size(); pos++) {
		if (m_elems[pos] == p_v) {
			index = pos;
			break;
		}
	}
	if (index == -1) {
		throw logic_error("Vertex not in the graph");
	}
	return index;
}

}
