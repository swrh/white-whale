# White Whale

This is a simple code that implements a fixed-size key-value container that
uses an LRU cache replacement policy. It provides mapping between any type of
key or value and and should be very fast, depending on the interface you use.

Author: Fernando Silveira (fsilveira@gmail.com)

### Why?

I coded this simple library just to accomplish a challenge of a job position I
applied in 2017. For some unknown reason the name of this company, which is
located in São Paulo, shall remain a mistery.

### Language

The language used in this library is C++. The title of the challenge was "C/C++
Software Developer coding challenge", so I chose C++.

### Requirements

This project requires CMake 3.1 and Boost 1.54.0 and has only been tested on a
Ubuntu 16.04 operating system.

### Features

* Keys and values are of any type;
* The basic operations are `add(key, value)` and `get(key)`;
* It is fast, because no data is stored anywhere but in the RAM memory (DOH! :O)

### Documentation

Unfortunately the only documentation available at the moment is this README
file and the comments inline. The simplest Doxygen configuration script should
be able to retrieve and display everything there is in nice HTML pages. Please
refer to any Doxygen tutorial to do this.

### Limitations

* This is just *kind of* a proof of concept of an LRU key-value cache. Please
  do not blame me if you find this useless.
* Only a single process (possibly multi-threaded) can access a particular
  database at a time.
* There is no client-server support builtin to the library.  An application
  that needs such support will have to wrap their own server around the
  library.
* No support for UNICODE strings -- I didn't even try;

## First steps

### Building and running

To build you do it like any other CMake project:

```
$ mkdir build
$ cd build
$ cmake ..
$ make -j4
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
following 4 operations: CREATE, ADD, GET and DESTRUCT. These 4 operations are
triggered by 4 method calls with the same name. Here they are:

```c++
#include <ww/container.hpp>

template <typename K, typename V> bool create(const std::string &name, uint64_t n);
bool add(const std::string &name, const std::string &key, const std::string &value);
bool get(const std::string &name, const std::string &key, std::string &value);
bool destruct(const std::string &name);
```

Before calling any of these objects you must instantiate an object of the
`container` class:

```c++
#include <ww/container.hpp>

using namespace ww;

container cont; // the container class is in the 'ww' namespace
```

Then you can procede to the other operations.

### CREATE/DESTRUCT

To create a new container you just need to specify its name, the key and the
value types and its size:

```c++
cont.create<int, float>("foobar", 3);
```

There you go: you've created a new container named "foobar" with the cache size of 3.

To destroy you just need to:

```c++
cont.destruct("foobar");
```

If something goes wrong (a false is returned anywhere), call:

```c++
cont.get_error();
```

... or ...

```c++
cont.get_error_string();
```

And this will tell you what is wrong with your setup.

### ADD/GET

To add and retrieve entries just call the `get()` and `add()`:

```c++
cont.add("foobar", "3", "12.34");
string result;
cont.get("foobar", "3", result);
```

### Adding support for new types

To add support for new types you should implement the
`string_utils::from_string()` and `string_utils::to_string()` methods in the
`src/string_utils.cpp` file and ensure your type can be used as `std::map` key.

Suggestion: [What requirements must std::map key classes meet to be valid keys?](https://stackoverflow.com/questions/6573225/what-requirements-must-stdmap-key-classes-meet-to-be-valid-keys)


### ATTENTION

Please note that if you use the type `string` you must always prepend and
append double quotes when passing to the `get()` and `add()` methods.

## Better performance

As you should have noticed the CREATE/ADD/GET/DESTRUCT methods receive and
return only string values. If you need to achieve a greater performance PLEASE
AVOID THE `container` CLASS AND USE THE `storage` CLASS DIRECTLY. This way
you'll avoid the string parsing/formatting/copying/etc and I'm sure you'll be
much more satisfied.

Below is a simple example:

```c++
#include <ww/storage.hpp>

using namespace ww;

storage<int, float> foobar(3);
foobar.add(42, 3.14); // adds 42
foobar.add(34, 1.1); // adds 34
foobar.add(9, 8.765); // discards 42 and adds 9
float result;
foobar.get(42, result); // will return false
foobar.get(34, result); // will return true and with result == "1.1"
```

For more information please visit the `test/storage.cpp` file.

## Testing

The tests are not so good, I know. I'm sorry, but I spent way too much time
designing, coding and documenting.

## LICENSE

BSD 2-clause all the way, baby.

# TODO

* document performance;
* document the limitations on the string matching;
* implement a better way to add support for new key/value types
