SGL - Simple Graph Library
==========================

Introduction
------------

SGL is a graph library greatly inspired by the BGL (Boost Graph Library).

Emerging from a school project, it doesn't really pretend to be as complete nor fast than Boost's, but it focuses on being at least simple to use.

The module also aims to provide some standard graph theory algorithms, like:
- breadth-first search and depth-first search
- Warshall's transitive closure algorithm
- some shortest-path finding algorithms like Floyd-Warshall, Dijkstra, Bellman-Ford
- connectivity finding algorithms
- minimum spanning tree algorithms like Kruskal-Prim's, etc.
- and more !

A graphic generator using for example GraphViz tools may also be implemented.


Components
----------

At the moment, two data structures are available for use with the SGL
- Adjacency_List : a graph internally implemented by an adjacency list
- Adjacency_Matrix : a graph internally implemented by an adjacency matrix

This in order to let users choose what they find the more appropriate for their use case.

For example, an adjacency matrix is better indicated for a graph with a known big number of edges.

On the other hand, for graphs of variable, but relatively small size, an adjacency list is commonly a good choice.


More types of implementation will maybe come in time.

Actually, since they all inherit from an abstract base class AbstractGraph, it should be possible for any user to create his own custom graph class inheriting the base class, given it implements the required methods. 


How to build it
---------------

You don't have to, since SGL is a header-only library.

To use it, just take the "sgl" directory in your project directory, make your linker aware that "sgl" is now an include directory, and include SGL.h in your source files. You're now ready to go !

Remember, everything in the project is inside the SGL namespace.


Documentation
-------------

The project's documentation is generated with Doxygen. The most up-to-date version can be found on the [project's GitHub page](www.scylardor.github.io/sgl).