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
 *  \exception bad_alloc in case of insufficient memory
 */
template<typename T>
Adjacency_List<T>::Adjacency_List(configuration p_flags)
{
}

/**
 *  \brief Copy constructor
 *
 *  \pre Enough memory available
 *  \param[in] p_src the graph to copy
 *  \exception bad_alloc in case of insufficient memory
 */
template<typename T>
Adjacency_List<T>::Adjacency_List(const Adjacency_List &p_src)
{
	_copyAdjacencyList(p_src);
}

/**
 * \brief Constructor of a sub-graph of the original, using a filter vector
 * i.e. only the vertices contained in the vector will be copied
 * \param[in] p_src the graph to copy
 * \param[in] p_filter the vector containing the vertices to copy
 * \pre Enough memory available
 * \pre All the vertices in the filter vector must be in the source graph
 * \post a deep copy of the graph is obtained, with only the vertices contained in the filter vector
 * \exception bad_alloc in case of insufficient memory
 * \exception logic_error if a vertex in filter vector isn't contained in the source graph
 */
template<typename T>
Adjacency_List<T>::Adjacency_List(const Adjacency_List &p_src, const std::vector<T> &p_filter) { // the explicit std:: is for Doxygen to recognize the function
	for (typename vector<T>::const_iterator vertex = p_filter.begin();
			vertex != p_filter.end(); ++vertex) {
		if (!p_src.hasVertex((*vertex))) {
			throw logic_error("Adjacency_List: a filter vector's vertex isn't in the source graph");
		}
		addVertex((*vertex));
	}
}

/**
 *  \brief Destructor
 */
template<typename T>
Adjacency_List<T>::~Adjacency_List() {
	for (unsigned int pos = 0; pos < m_nodes.size(); pos++) {
		delete m_nodes[pos];
	}
}

/**
 * \brief Assignment operator overloading: deep copy of a graph
 * \param[in] p_src the graph to copy
 * \pre Enough memory available
 * \post A deep copy is returned
 * \exception bad_alloc in case of insufficient memory
 * \return the current graph returns itself
 */
template<typename T>
const Adjacency_List<T> & Adjacency_List<T>::operator =(const Adjacency_List<T> &p_src) {
	Adjacency_List<T> temp(p_src);

	std::swap(m_nodes, temp.m_nodes);
	return *this;
}

/**
 * \brief Adds a vertex to the graph
 * \param[in] p_v the new element to put in the graph
 * \pre Enough memory available
 * \pre The vertex isn't already in the graph
 * \post The graph counts one more vertex
 * \exception bad_alloc in case of insufficient memory
 * \exception logic_error if the vertex already is in the graph
 */
template<typename T>
void Adjacency_List<T>::addVertex(const T &p_v) {
	if (hasVertex(p_v)) {
		throw logic_error("addVertex: this vertex is already in the graph");
	}
	Node *newv = new Node(p_v);

	m_nodes.push_back(newv);
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
void Adjacency_List<T>::addEdge(const T &p_v1, const T &p_v2) {
	int index_s1, index_s2;
	try {
		index_s1 = _index(p_v1);
		index_s2 = _index(p_v2);
	} catch (const logic_error &le) {
		throw logic_error("addEdge: one of the vertices isn't in the graph");
	}
	m_nodes[index_s1]->m_neighbors.push_back(m_nodes[index_s2]->m_data);
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
void Adjacency_List<T>::deleteEdge(const T &p_v1, const T &p_v2) {
	int index_s1, index_s2;
	try {
		index_s1 = _index(p_v1);
		index_s2 = _index(p_v2);
	} catch (const logic_error &le) {
		throw logic_error("deleteEdge: one of the vertices isn't in the graph");
	}
	if (!hasEdge(p_v1, p_v2)) {
		throw logic_error("deleteEdge: no edge between the two vertices");
	}
	m_nodes[index_s1]->m_neighbors.remove(m_nodes[index_s2]->m_data);
}

/**
 * \brief deletes a vertex from the graph
 * \param[in] p_v The element we want to delete the vertex of
 * \pre The vertex is in the graph
 * \post The graph counts one less vertex
 * \exception logic_error if the vertex isn't in the graph
 */
template<typename T>
void Adjacency_List<T>::deleteVertex(const T &p_v) {
	int index_s;

	try {
		index_s = _index(p_v);
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
 * \brief verifies that a vertex is in the graph
 * \param[in] p_v the element we search the vertex of
 * \post The graph remains unchanged
 * \return whether the graph contains this vertex or not
 */
template<typename T>
bool Adjacency_List<T>::hasVertex(const T &p_v) const {
	bool isHere = true;

	try {
		_index(p_v);
	} catch (const logic_error &le) {
		isHere = false;
	}
	return isHere;
}

/**
 * \brief verifies that an edge is in the graph
 * \param[in] p_v1 the source vertex of the edge
 * \param[in] p_v2 the destination vertex of the edge
 * \pre The 2 vertices of the edge are in the graph
 * \post The graph remains unchanged
 * \exception logic_error if one of the two vertices isn't in the graph
 * \return whether the graph contains this edge or not
 */
template<typename T>
bool Adjacency_List<T>::hasEdge(const T &p_v1, const T &p_v2) const {
	bool isHere = true;
	int index_s1, index_s2;

	try {
		index_s1 = _index(p_v1);
		index_s2 = _index(p_v2);
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
 * \brief Lists all the vertices in the graph
 * Returns in a vector all the vertices of the graph
 * \pre Enough memory available
 * \post A vector of all the vertices data is returned
 * \exception bad_alloc in case of insufficient memory
 * \return a vector containing all the vertices of the graph
 */
template<typename T>
std::vector<T> Adjacency_List<T>::vertices() const {
	vector<T> elems;

	elems.reserve(m_nodes.size());
	for (unsigned int pos = 0; pos < m_nodes.size(); pos++) {
		elems.push_back(m_nodes[pos]->m_data);
	}
	return elems;
}

/**
 * \brief Returns the in-degree of a vertex in the graph
 * i.e. the number of neighbor vertices of this vertex which have an edge that
 * goes to it.
 * \param[in] p_v the vertex we want to know the in-degree of
 * \pre The vertex has to be in the graph
 * \exception logic_error if the vertex isn't in the graph
 * \return the number of edges to other vertices the vertex is the destination of
 */
template<typename T>
unsigned int Adjacency_List<T>::vertexInDegree(const T &p_v) const {
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
 * \param[in] p_v the vertex we want to know the out-degree of
 * \pre The vertex must be in the graph
 * \exception logic_error if the vertex isn't in the graph
 * \return the number of edges to other vertices the vertex is the source of
 */
template<typename T>
unsigned int Adjacency_List<T>::vertexOutDegree(const T &p_v) const {
	if (!hasVertex(p_v)) {
		throw logic_error("vertexOutDegree: the vertex isn't in the graph");
	}
	return m_nodes[_index(p_v)]->m_neighbors.size();
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
std::vector<T> Adjacency_List<T>::vertexNeighborhood(const T &p_v, bool p_closed) const {
	if (!hasVertex(p_v)) {
		throw logic_error("vertexNeighborhood: the vertex isn't in the graph");
	}
	vector<T> adjs;
	unsigned int index_v = _index(p_v);

	for (unsigned int pos = 0; pos < m_nodes.size(); pos++) {
		Node *cur = m_nodes[pos];

		if (pos == index_v) {
			// if we find the node of the given vertex, we add to the vector
			// all the vertices it points to, after having checked they're not already in it
			for (typename list<T>::const_iterator vert =
					cur->m_neighbors.begin(); vert != cur->m_neighbors.end();
					++vert) {
				if (std::find(adjs.begin(), adjs.end(), (*vert))
						== adjs.end()) {
					adjs.push_back((*vert));
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
	if (p_closed) {
		adjs.push_back(p_v);
	}
	return adjs;
}

/**
 * \brief Displays a representation of the graph
 * \pre The type contained by the graph must have declared an overloading of the << operator for ostreams
 *  	 in order to be printed out by the function
 * \post The graph remains unchanged
 */
template<typename T>
const std::string Adjacency_List<T>::_repr() const {
	stringstream stream;

	stream << "Number of vertices: " << nbVertices() << endl;
	stream << "Number of edges: " << nbEdges() << endl;
	stream << "List of vertices and their edges:" << endl << endl;
	for (unsigned int pos = 0; pos < m_nodes.size(); pos++) {
		Node *cur = m_nodes[pos];

		stream << "Vertex: " << cur->m_data << endl;
		stream << "Source of " << cur->m_neighbors.size() << " edges to vertices:"
				<< endl;
		for (typename list<T>::const_iterator v = cur->m_neighbors.begin();
				v != cur->m_neighbors.end(); ++v) {
			stream << cur->m_data << " -> " << (*v);
			stream << endl;
		}
		if (cur->m_neighbors.size() == 0) {
			stream << "No edges" << endl;
		}
		stream << endl;
	}
	if (m_nodes.size() == 0) {
		stream << "Empty list" << endl;
	}
	return stream.str();
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
vector<pair<T, T> > Adjacency_List<T>::edges() const {
	vector<pair<T, T> > edges;
	for (unsigned int i = 0; i < m_nodes.size(); i++) {
		Node *cur = m_nodes[i];

		for (typename list<T>::const_iterator v = cur->m_neighbors.begin();
				v != cur->m_neighbors.end(); ++v) {
			edges.push_back(make_pair(cur->m_data, (*v)));
		}
	}
	return edges;
}


/**
 * \brief Checks the structural equality of two graphs: same vertices, same edges
 * \param[in] p_g2 the second graph
 * \return whether the two graphs are structurally equal or not
 */
template<typename T>
bool Adjacency_List<T>::equals(const Adjacency_List &p_g2) const {
	bool areEqual = true;

	if ((nbVertices() != p_g2.nbVertices()) || (nbEdges() != p_g2.nbEdges())) {
		areEqual = false;
	}
	if (areEqual) {
		std::vector<T> elems = vertices();

		for (unsigned int i = 0; i < elems.size(); i++) {
			if (!p_g2.hasVertex(elems[i])) {
				areEqual = false;
				break;
			}
		}
		std::vector<std::pair <T, T> > theEdges = edges();

		for (unsigned int i = 0; i < theEdges.size(); i++) {
			if (!p_g2.hasEdge(theEdges[i].first, theEdges[i].second)) {
				areEqual = false;
				break;
			}
		}
	}
	return areEqual;
}

/**
 * \brief Private function used by a copy constructor to copy the adjacency list of another graph
 * \pre Enough memory available
 * \param[in] p_src the source graph
 * \post The contents of the source graph (vertices and edges) are fully copied
 * \exception bad_alloc in case of insufficient memory
 */
template<typename T>
void Adjacency_List<T>::_copyAdjacencyList(const Adjacency_List &p_src) {
	for (unsigned pos = 0; pos < p_src.nbVertices(); pos++) {
		addVertex(p_src.m_nodes[pos]->m_data);
	}
	for (unsigned pos = 0; pos < p_src.nbVertices(); pos++) {
		Node *cur = p_src.m_nodes[pos];

		for (typename list<T>::const_iterator v = cur->m_neighbors.begin();
				v != cur->m_neighbors.end(); ++v) {
			addEdge(p_src.m_nodes[pos]->m_data, (*v));
		}
	}
}

/**
 * \brief Private function used to retrieve the index in the intern adjacency list of an element
 * \pre The vertex is in the graph
 * \param[in] p_v the vertex to search
 * \exception logic_error the vertex isn't in the graph
 * \return the index in the adjacency list of the given vertex's node
 */
template<typename T>
int Adjacency_List<T>::_index(const T &p_v) const {
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

} // namespace SGL
