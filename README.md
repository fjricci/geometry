### Description

This program takes a json file as input and generates a quote for the
manufacturing cost.

Supported on MacOSX with clang.

### Installing dependencies

To install nhlomann/json (https://github.com/nlohmann/json):

`brew tap nlohmann/json && brew install nlohmann_json`

The local file `json.hpp` comes from this library.

### Building

```
mkdir build && cd build
clang ../main.cpp ../Geometry.cpp ../Profile.cpp -o geometry -lc++ -std=c++11
```

### Running

`geometry profile.json`

### Formatting

This code adheres to the LLVM coding style, and patches should be formatted
using `clang-format`.

### Future improvements

A more efficient validation method for the profile would be great,
and more thorough error checking on the input json files would be necessary
for real-world applications.
