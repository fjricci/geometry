### Description

This program takes a json file as input and generates a quote for the
manufacturing cost.

Supported on MacOSX with clang.

### Installing dependencies

To install nhlomann/json (https://github.com/nlohmann/json):

`brew tap nlohmann/json && brew install nlohmann_json`

The local file `json.hpp` comes from this library.

### Building

`mkdir build && cd build
 clang ../main.cpp ../Geometry.cpp ../Profile.cpp -o geometry -lc++ -std=c++11`

### Running

`geometry profile.json`
