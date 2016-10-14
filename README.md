### Description

This program takes a json file as input and generates a quote for the
manufacturing cost.

Supported on MacOSX with clang.

### Installing dependencies

To install nhlomann/json (https://github.com/nlohmann/json):

`brew tap nlohmann/json && brew install nlohmann_json`

### Building

`mkdir build && cd build
 clang ../main.cpp ../Geometry.cpp -o geometry -lc++ -std=c++11`

### Running

`geometry profile.json`
