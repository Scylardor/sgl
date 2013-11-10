/**
 * \file AdjacencyMatrix.hpp
 * \brief Adjacency Matrix implementation.
 * \author Alexandre Baron
 * \version 0.1
 * \date 2013, October
 *
 * Implementation of a generic adjacency matrix for internal use in a graph
 */

#include <stdexcept>
#include <algorithm> // std::find

using namespace std;

namespace SGL {



////////////////////////////////////////////////////////////////////////////////////////////////////////
// External class methods
////////////////////////////////////////////////////////////////////////////////////////////////////////



template<typename T>
Adjacency_Matrix<T>::Adjacency_Matrix(configuration p_f) {
	this->m_config = p_f;
	this->m_nbVertices = 0;
	if (p_f & UNDIRECTED) {
		m_matrix = new UndirectedMatrix();
	} else {
		m_matrix = new DirectedMatrix();
	}
}


/**
 * \brief verifies that a vertex is in the matrix
 * \param[in] p_v the element we search the vertex of
 * \return whether the matrix contains this vertex or not
 */
template<typename T>
bool Adjacency_Matrix<T>::hasVertex(const T &p_v) const {
	bool isHere = true;

	try {
		_index(p_v);
	} catch (const logic_error &le) {
		isHere = false;
	}
	return isHere;
}

/**
 * \brief verifies that an edge is in the matrix
 * \param[in] p_v1 the source vertex of the edge
 * \param[in] p_v2 the destination vertex of the edge
 * \pre The 2 vertices of the edge are in the matrix
 * \exception logic_error if one of the two vertices isn't in the matrix
 * \return whether the matrix contains this edge or not
 */
template<typename T>
bool Adjacency_Matrix<T>::hasEdge(const T &p_v1, const T &p_v2) const {
	int index_s1, index_s2;

	try {
		index_s1 = _index(p_v1);
		index_s2 = _index(p_v2);
	} catch (const logic_error &le) {
		throw logic_error("hasEdge: one of the vertices isn't in the matrix");
	}
	return (m_matrix->hasEdge(index_s1, index_s2));
}

/**
 * \brief Returns the in-degree of a vertex in the matrix
 * i.e. the number of neighbor vertices of this vertex which have an edge that
 * goes to it.
 * \param[in] p_v the vertex we want to know the in-degree of
 * \pre The vertex has to be in the matrix
 * \exception logic_error if the vertex isn't in the matrix
 * \return the number of edges to other vertices the vertex is the destination of
 */
template<typename T>
unsigned Adjacency_Matrix<T>::vertexInDegree(const T & p_v) const {
	int index_s;
	unsigned indegree = 0;

	try {
		index_s = _index(p_v);
	} catch (const logic_error &le) {
		throw logic_error("vertexInDegree: the vertex isn't in the graph");
	}
	for (unsigned i = 0; i < m_elems.size(); i++) {
		if (m_matrix->hasEdge(i, index_s)) {
			indegree++;
		}
	}
	return indegree;
}

/**
 *  \brief Returns the out-degree of a vertex in the graph,
 *  i.e. the number of edges with other vertices it is the source of.
 * \param[in] p_v the vertex we want to know the out-degree of
 * \pre The vertex must be in the graph
 * \exception logic_error if the vertex isn't in the graph
 * \return the number of edges to other vertices the vertex is the source of
 */
template<typename T>
unsigned Adjacency_Matrix<T>::vertexOutDegree(const T & p_v) const {
	int index_s;
	unsigned outdegree = 0;

	try {
		index_s = _index(p_v);
	} catch (const logic_error &le) {
		throw logic_error("vertexOutDegree: the vertex isn't in the graph");
	}
	for (unsigned i = 0; i < m_elems.size(); i++) {
		if (m_matrix->hasEdge(index_s, i)) {
			outdegree++;
		}
	}
	return outdegree;
}

/**
 *  \brief Lists the adjacent vertices of a vertex in the graph.
 *  If closed boolean is set to true, the vertex itself will be included in the returned neighborhood,
 *  making it a closed neighborhood (as opposed to the open version, without it included).
 * \param[in] p_v the vertex we want the neighborhood of
 * \param[in] p_closed boolean to say whether we want the closed neighborhood of the vertex or not (false by default)
 * \pre Enough memory available
 * \pre The vertex has to be in the graph
 * \exception bad_alloc in case of insufficient memory
 * \exception logic_error if the vertex isn't in the graph
 * \return A vector containing the data of all neighbor vertices of the vertex
 */
template<typename T>
vector<T> Adjacency_Matrix<T>::vertexNeighborhood(const T &p_v, bool p_closed) const {
	unsigned index;

	try {
		index = _index(p_v);
	} catch (const logic_error &le) {
		throw logic_error("vertexNeighborhood: the vertex isn't in the graph");
	}
	vector<T> neighbors;

	for (unsigned i = 0; i < m_elems.size(); i++) {
		if (m_matrix->hasEdge(index, i)) {
			neighbors.push_back(m_elems[i]);
		}
	}
	if (p_closed && std::find(neighbors.begin(), neighbors.end(), p_v) == neighbors.end()) {
		neighbors.push_back(p_v);
	}
	return neighbors;
}

/**
 * \brief Adds a vertex to the graph
 * \param[in] p_elem the new element to put in the graph
 * \pre Enough memory available
 * \pre The vertex isn't already in the graph
 * \post The graph counts one more vertex
 * \exception bad_alloc in case of insufficient memory
 * \exception logic_error if the vertex already is in the graph
 */
template<typename T>
void Adjacency_Matrix<T>::addVertex(const T &p_elem) {
	m_elems.push_back(p_elem);
	m_matrix->addVertex();
}


/**
 * \brief deletes a vertex from the graph
 * \param[in] p_v The element we want to delete the vertex of
 * \pre The vertex is in the graph
 * \post The graph counts one less vertex
 * \exception logic_error if the vertex isn't in the graph
 */
template<typename T>
void Adjacency_Matrix<T>::deleteVertex(const T &p_v) {
	int index_s;

	try {
		index_s = _index(p_v);
	} catch (const logic_error &le) {
		throw logic_error("deleteVertex: the vertex isn't in the graph");
	}
	this->m_matrix->deleteVertex(index_s);

	m_elems.erase(m_elems.begin() + index_s);
}

/**
 * \brief Adds an edge in the graph
 * \param[in] p_v1 the source vertex of the edge
 * \param[in] p_v2 the destination vertex of the edge
 * \pre Enough memory available
 * \pre The 2 vertices of the edge are in the graph
 * \post The graph counts one more edge
 * \exception bad_alloc in case of insufficient memory
 * \exception logic_error if one of the two vertices isn't in the graph
 */
template<typename T>
void Adjacency_Matrix<T>::addEdge(const T &p_v1, const T &p_v2) {
	int index_s1, index_s2;
	try {
		index_s1 = _index(p_v1);
		index_s2 = _index(p_v2);
	} catch (const logic_error &le) {
		throw logic_error("addEdge: one of the vertices isn't in the graph");
	}
	m_matrix->addEdge(index_s1, index_s2);
}

/**
 * \brief Deletes an edge in the graph
 * \param[in] p_v1 the source vertex of the edge
 * \param[in] p_v2 the destination vertex of the edge
 * \pre The 2 vertices of the edge are in the graph
 * \post The graph counts one less edge
 * \exception logic_error if one of the two vertices isn't in the graph
 */
template<typename T>
void Adjacency_Matrix<T>::deleteEdge(const T &p_v1, const T &p_v2) {
	int index_s1, index_s2;
	try {
		index_s1 = _index(p_v1);
		index_s2 = _index(p_v2);
	} catch (const logic_error &le) {
		throw logic_error("deleteEdge: one of the vertices isn't in the graph");
	}
	if (!m_matrix->hasEdge(p_v1, p_v2)) {
		throw logic_error("deleteEdge: no edge between the two vertices");
	}
	m_matrix->deleteEdge(index_s1, index_s2);
}

/**
 * \brief Lists all the vertices in the graph
 * Returns in a vector all the vertices of the graph
 * \pre Enough memory available
 * \post A vector of all the vertices data is returned
 * \exception bad_alloc in case of insufficient memory
 * \return a vector containing all the vertices of the graph
 */
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
	vector<vector<int> > edge_indexes;

	m_matrix->edges(edge_indexes);
	for (unsigned src = 0; src < edge_indexes.size(); src++) {
		vector<pair<T, T> > vertex_edges;
		for (unsigned dest = 0; dest < edge_indexes[src].size(); dest++) {
			edges.push_back(make_pair(m_elems[src], m_elems[dest]));
		}
	}
	return edges;
}


/**
 * \brief Checks the strucural equality of two matrices.
 * \return true if the matrices are identical, else false
 */
template<typename T>
bool Adjacency_Matrix<T>::operator==(const Adjacency_Matrix &p_rhs) const {
	bool areEqual = true;

	if (nbEdges() != p_rhs.nbEdges() || nbVertices() != p_rhs.nbVertices()) {
		areEqual = false;
	}
	// splitting in two if's as we have to know if vectors are of same size to perform comparison
	if (areEqual && (m_elems != p_rhs.m_elems || m_matrix != p_rhs.m_matrix)) {
		areEqual = false;
	}
	return areEqual;
}

/**
 * \brief Output function.
 */
template<typename T>
const string Adjacency_Matrix<T>::_repr() const {
	stringstream stream;
//
//	stream << "Matrix vertices number: " << nbVertices() << endl;
//	stream << "Matrix edges number: " << nbEdges() << endl;
//	stream << "Matrix composition:" << endl;
//	if (nbVertices() == 0) {
//		stream << "null";
//	} else {
//		stream << "\t";
//	}
//	for (unsigned i = 0; i < m_elems.size(); i++) {
//		stream << m_elems[i] << "\t";
//	}
//	stream << endl;
//	for (unsigned i = 0; i < m_matrix.size(); i++) {
//		stream << m_elems[i] << "\t";
//		for (unsigned j = 0; j < m_matrix[i].size(); j++) {
//			stream << m_matrix[i][j] << "\t";
//		}
//		stream << endl;
//	}
	return stream.str();
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


////////////////////////////////////////////////////////////////////////////////////////////////////////
// Internal matrices methods: Directed matrix
////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
unsigned Adjacency_Matrix<T>::DirectedMatrix::nbEdges() const {
	unsigned nbEdges = 0;

	for (unsigned pos = 0; pos != m_matrix.size(); pos++) {
		for (unsigned i = 0; i < m_matrix[pos].size(); i++) {
			if (m_matrix[pos][i] == 1) {
				nbEdges++;
			}
		}
	}
	return nbEdges;
}

template <typename T>
bool Adjacency_Matrix<T>::DirectedMatrix::hasEdge(unsigned p_idx_v1, unsigned p_idx_v2) const {
	return (m_matrix[p_idx_v1][p_idx_v2] != 0);
}



template <typename T>
void Adjacency_Matrix<T>::DirectedMatrix::addVertex() {
	vector<int> newline(m_matrix.size(), 0);

	m_matrix.push_back(newline);
	for (unsigned i = 0; i < m_matrix.size(); i++) {
		m_matrix[i].push_back(0);
	}
}

template <typename T>
void Adjacency_Matrix<T>::DirectedMatrix::deleteVertex(unsigned p_index) {
	for (unsigned pos = 0; pos != m_matrix.size(); pos++) {
		m_matrix[pos].erase(m_matrix[pos].begin() + p_index);
	}
	m_matrix.erase(m_matrix.begin() + p_index);
}

template <typename T>
void Adjacency_Matrix<T>::DirectedMatrix::addEdge(unsigned p_idx_v1, unsigned p_idx_v2) {
	m_matrix[p_idx_v1][p_idx_v2] = 1;
}

template <typename T>
void Adjacency_Matrix<T>::DirectedMatrix::deleteEdge(unsigned p_idx_v1, unsigned p_idx_v2) {
	m_matrix[p_idx_v1][p_idx_v2] = 0;
}

template <typename T>
void Adjacency_Matrix<T>::DirectedMatrix::edges(vector<vector<int> > & p_edges_indexes) const {
	for (unsigned i = 0; i < m_matrix.size(); i++) {
		vector<int> vertex_edges_dests;

		for (unsigned j = 0; j < m_matrix[i].size(); j++) {
			if (m_matrix[i][j] != 0) {
				vertex_edges_dests.push_back(j);
			}
		}
		p_edges_indexes.push_back(vertex_edges_dests);
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
// Internal matrices methods: Undirected matrix
////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
unsigned Adjacency_Matrix<T>::UndirectedMatrix::nbEdges() const {
	unsigned nbEdges = 0;

	for (unsigned i = 0; i != m_matrix.size(); i++) {
		if (m_matrix[i] != 0) {
			nbEdges++;
		}
	}
	return nbEdges;
}

template <typename T>
bool Adjacency_Matrix<T>::UndirectedMatrix::hasEdge(unsigned p_idx_v1, unsigned p_idx_v2) const {
	return (m_matrix[_calcActualIndex(p_idx_v1, p_idx_v2)] != 0);
}

template <typename T>
void Adjacency_Matrix<T>::UndirectedMatrix::edges(vector<vector<int> > & p_edges_indexes) const {
	vector<int> vertex_edges_dests;

	for (unsigned idx = 0; idx < _nbVertices(); idx++) {
		vector<int> vertex_edges_dests;

		unsigned startIndex = (idx + 1) * idx / 2;
		for (unsigned pos = 0; pos < (idx+1); pos++) {
			if (m_matrix[startIndex + pos] != 0) {
				vertex_edges_dests.push_back(pos);
			}
		}
		p_edges_indexes.push_back(vertex_edges_dests);
	}
}

template <typename T>
void Adjacency_Matrix<T>::UndirectedMatrix::addVertex() {
	for (unsigned i = 0; i < m_matrix.size() + 1; i++) {
		m_matrix.push_back(0);
	}
}

template <typename T>
void Adjacency_Matrix<T>::UndirectedMatrix::deleteVertex(unsigned p_index) {
	// first, remove the edges of the vertices following this one
	for (unsigned pos = _nbVertices()-1; pos != p_index; pos--) {
		int edgeIndex = (pos + 1) * pos / 2 + p_index;

		m_matrix.erase(m_matrix.begin() + edgeIndex);
	}
	// grab the index of the "vertex-0" edge, the first of this vertex edges
	unsigned startIndex = (p_index + 1) * p_index / 2;
	// next, remove all the edges of the vertex itself
	m_matrix.erase(m_matrix.begin() + startIndex, m_matrix.begin() + startIndex + (p_index + 1));
}

template <typename T>
void Adjacency_Matrix<T>::UndirectedMatrix::addEdge(unsigned p_idx_v1, unsigned p_idx_v2) {
	m_matrix[_calcActualIndex(p_idx_v1, p_idx_v2)] = 1;
}

template <typename T>
void Adjacency_Matrix<T>::UndirectedMatrix::deleteEdge(unsigned p_idx_v1, unsigned p_idx_v2) {
	m_matrix[_calcActualIndex(p_idx_v1, p_idx_v2)] = 1;
}


template <typename T>
unsigned Adjacency_Matrix<T>::UndirectedMatrix::_nbVertices() const {
	unsigned nbVertices = 0;
	unsigned step = 2;
	unsigned cpt = 1;

	while (cpt <= m_matrix.size()) {
		nbVertices++;
		cpt += step;
		step++;
	}
	return nbVertices;
}

template <typename T>
unsigned Adjacency_Matrix<T>::UndirectedMatrix::_calcActualIndex(unsigned p_idx_v1, unsigned p_idx_v2) const {
	unsigned index;

	if (p_idx_v1 > p_idx_v2) {
		index = (p_idx_v1 + 1) * 2 / 2 + p_idx_v2;
	} else {
		index = (p_idx_v2 + 1) * 2 / 2 + p_idx_v1;
	}
	return index;
}

}
