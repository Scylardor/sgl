SGL - Simple Graph Library
==========================

While studying the graph theory in class, I found the required implemention didn't go far enough.

So I decided to create my own small graph library. It's willing to be greatly inspired by the Boost Graph Library.

It should propose some famous algorithms:
* Breadth-first search and depth-first search
* Warshall
* Floyd/Warshall
* Dijkstra
* Bellman-Ford
* Kruskal, Prim
* Ford-Fulkerson
* A*...

A GraphViz graph generation utility permitting to create images of the produced graphs also would be great.

We're not there yet, but I hope it will be someday.

Components
----------

At the moment, the library itself only uses the standard library. No specific dependencies are needed.

For now, it merely manages a (really) simple oriented graph, using internally an adjacency list. This cannot be changed yet.

But I'd like to make it highly parametrizable, mainly:
* by letting the user choose the internal structure to use (adjacency list or adjacency matrix), depending on what he needs
* by letting vertices and edges hold a lot of possible properties and maybe facilitate their customization 

On the other hand, the documentation is made with [Doxygen](http://www.stack.nl/~dimitri/doxygen/) so you'll need it if you want to build it by yourself. I provide the doxyfile used to generate it.

And to build the unit tests, you'll need the [Google Test](http://code.google.com/p/googletest/) framework.

How to build it
---------------

You don't have to since SGL is a header-only library.

Just take SGL.h and SGL.hpp with your source files, and include SGL.h.

All the project is inside the SGL namespace.