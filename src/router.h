// this module provides us with classes and methods to make
// a routing table containing routes and the files to be served
// for that corresponding route
#include <iostream>
#include <unordered_map>

class Router
{
private:
    std::unordered_map<std::string, std::string> map;
public:
    // function to add a new route into the routing table
    // 1st argument: route like "/about"
    // 2nd argument: file name to be served
    void add(std::string const & route, std::string const & fileName );

    // function to fetch the filename mapped to the given route
    // returns the file name as a CPP std::string
    std::string find(std::string const & route);

    // function to print the routing table
    void print();
};
