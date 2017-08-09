# White Whale [![Travis Build status](https://travis-ci.org/swrh/white-whale.svg?branch=master)](https://travis-ci.org/swrh/white-whale)

This is a simple code that implements a fixed-size key-value container that
uses an LRU cache replacement policy. It provides mapping between any type of
key or value and and should be very fast, but it doesn't serialize the data.
Yes, it doesn't.

Author: Fernando Silveira (fsilveira@gmail.com)

### Why?

I coded this simple library just to accomplish a challenge of a job position I
applied in 2017. For some unknown reason the name of this company, which is
located in São Paulo, shall remain a mistery, just like the feedback I'm still
waiting for.

### Language

The language used in this library is C++. The title of the challenge was "C/C++
Software Developer coding challenge", so I chose C++.

### Requirements

This project requires CMake 3.1 and Boost 1.54.0 and has only been tested on a
Ubuntu 16.04 operating system.

### Documentation

Unfortunately the only documentation available at the moment is this README
file and the comments inline. The simplest Doxygen configuration script should
be able to retrieve and display everything there is in nice HTML pages. Please
refer to any Doxygen tutorial to do this.

### Features

* Keys and values are of any type;
* The basic operations are `add(key, value)` and `get(key)`;
* It is supposed to be fast, because no complex data storage or parsing is
  done.

### Limitations

* This is just *kind of* a proof of concept of an LRU key-value cache. Please
  do not blame me if you find this useless, [I'm just the messenger][1];
* Only a single process can access a particular database at a time;
* There is no client-server support builtin to the library.  An application
  that needs such support will have to wrap their own server around the
  library;
* No support for UNICODE strings.

## First steps

### Building and running

To build you do it like any other CMake project:

```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

After that, you can run the tests just by calling `./ww-test`:

```
$ ./ww-test
Running 4 test cases...

*** No errors detected
```

If you wish to call the API from a new program you might implement a `main.cpp`
in the root directory of this project and add the following lines to the
`CMakeLists.txt` file:

```
# ww definitions
add_executable (ww
	${COMMON_SOURCES}
	./main.cpp
	)

target_link_libraries (ww
	${Boost_LIBRARIES}
	)

target_include_directories(ww PUBLIC
	./include
	${Boost_INCLUDE_DIRS}
	)

target_compile_options(ww PUBLIC
	${Boost_CFLAGS_OTHER}
	)
```

... or you could edit the tests directly in the `test/*.cpp` files.

### API

The main part of the library is the `container` class. There we can achieve the
following 4 operations: CREATE, ADD, GET and DESTRUCT. These four operations
are triggered by the constructor, the destructor and two other method calls
with the same name. Here they are:

```c++
#include <ww/container.hpp>

template <typename K, typename V> class
container
{
public:
    container(size_type max_size);
    ~container();
    bool add(const K &k, const V &v);
    V *get(const K &k);
};
```

### CREATE/DESTRUCT

To create a new container you just need to instantiate it:

```c++
container<int, float> foobar(3);
```

There you go: you've created a new container with the cache size of 3.

To destroy you just destroy it (let it go out of scope).

### ADD/GET

To add and retrieve entries just call the `get()` and `add()`:

```c++
foobar.add(3, 12.34);
float *result = foobar.get(3);
assert(result != nullptr);
assert(*result == 12.34);
```

## Testing

The tests are not good yet, I'm sorry.

## LICENSE

BSD 2-clause all the way, baby.

[1]: https://en.wikipedia.org/wiki/Shooting_the_messenger
