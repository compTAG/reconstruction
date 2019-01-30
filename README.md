# Reconstruction

## Dependencies

- [Boost](https://www.boost.org/) (tested with 1.58)
- [CMake](https://cmake.org) (tested with 3.11.0)
- [Dionysus](https://github.com/mrzv/dionysus) (tested with 2.0.6)
- [Google Test](https://github.com/google/googletest) (tested with 1.8.0)
- [PLF Nanotimer](https://github.com/mattreecebentley/plf_nanotimer) (tested with commit 8c42255)

## Building and Setup

Dependences are installed using CMake!  For more on getting started with cmake
see the [cmake tutorial](https://cmake.org/cmake-tutorial/). To get started just
build as you would any standard cmake project (but the dependences will be
handled for you).

    mkdir build
    cd build
    cmake ..
    make

Before making edits use:

	git checkout -b [new_branch_name]

to create a new branch to work on.


## Benchmarking with python

To make benchmark running easier, we use a kind of jankey encoding of the graph.
To run a graph

    v0 = (1,4)
    v1 = (12,45)
    v2 = (23,13)

And edges

    e0 = (v0,v2)
    e1 = (v1,v2)

We specify the coordinates of the vertices as an array `[1, 4, 12, 45, 23, 13]`.
Next we use an implicit number of the vertices so that the first and second
coordinates are the x- and y-coordinates of vertex 0, the third and fourth are
the x- and y-coordinates of vertex 1, etc.  For example, the 0th vertex has
coordinates (1, 4) and the 1st vertex has coordinates (12, 45).

We specify the edges with pairs using the implicit vertex numbering.  For
example, since edge e0, uses vertices v0 and v1, and edge e1 uses vertices v1
and v2, we specify the edges as `[0, 2, 1, 2]`.

### Using the bindings

To setup the python bindings, install with pip.  From the project root (the one
with `setup.py` run, from the shell

    $ pip install .

If you didn't get any errors, things may have worked!  After all is setup you
can tests and benchmarks.  For example, to run a graph from the previous section
run Startup python and run

    >>> import reconstruction
    >>> runner = reconstruction.Runner([1,4,12,45,23,13], [0,2,1,2])
    >>> runner.verify()

If the result from verify was `True`, that means that the reconstruction was
successful.  Now, you can benchmark with `k` iterations.

    >>> k = 1000
    >>> runner.benchmanrk(k)
    54917045.0

The result will be the number of nano seconds spent performing the `k`
iterations minus the time for computing persistence diagrams.
