SGL - Simple Graph Library
==========================

Introduction
------------

SGL is a graph library greatly inspired by the BGL (Boost Graph Library).

This is a project driven by my need to have a generic graph tool in C++, without using Boost's. May it be useful to other people as well !

Documentation
-------------

The project's documentation is generated with Doxygen. The most up-to-date version can be found on the [project's GitHub page](http://scylardor.github.io/sgl/).

License
-------

The project is under the MIT License.

It lets you do pretty anything you want with the code, as long as you provide attribution back to me and don’t hold me liable.

Components
----------

The SGL implements a collection of graph implementations and generic algorithms to work with.

The configuration of each graph can easily be modified by a set of flags : directed, weighted graphs...

At the moment two data structures are available for use with the SGL:
- Adjacency_List : a graph internally implemented by an adjacency list
- Adjacency_Matrix : a graph internally implemented by an adjacency matrix

This in order to let users choose what they find the more appropriate for their use case.

More features may come in time.

Which class should I use ?
-------------------------

For example, an adjacency matrix is better indicated for a graph with a known big number of edges.

On the other hand, for graphs of variable, but relatively small size, an adjacency list is commonly a good choice.


How to use it
---------------

SGL is a **header-only library**, so you don't need to compile anything beforehand.

To use it, just clone the repository in your project, make your compiler aware that the SGL directory is now an include directory, and include SGL.h in your source files. You're now ready to go !

**Also**, if you're interested in just using one class of the library and have to keep a low compilation time, since every class of the library is a separate module, you can just import the header of this class (e.g. : AdjacencyMatrix.h) 
Remember, everything in the project is inside the SGL namespace.