#include "router.h"

void Router::add(std::string const & route, std::string const & fileName)
{
    map[route] = fileName;
}

std::string Router::find(std::string const & route)
{
    std::unordered_map<std::string, std::string >::iterator it = map.find(route);
    if(it == map.end())
    {
        return "./static/404.html";
    }
    else
    {
        return it->second;
    }
}

void Router::print()
{
    std::unordered_map<std::string, std::string >::iterator it = map.begin();

    std::cout << "Route\t\tFile" << std::endl;

    while(it != map.end())
    {
        std::cout << it->first << "\t\t" << it->second << std::endl;
        it++;
    }
}
