#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <map>
#include <functional>
#include <sstream>
#include <memory>
#include "constStructures.hpp"

class Tag
{
public:
    std::string name;
    std::string type;

    Tag(const std::string &name, const std::string &type) : name(name), type(type) {}

    std::pair<std::string, int> getTypeInfo() const
{
        if (type == "sint")
        {
                return std::make_pair(name, 8);
        }
        else if (type == "int")
        {
                return std::make_pair(name, 16);
        }
        else if (type == "dint")
        {
                return std::make_pair(name, 32);
        }
        else
        {
                throw std::runtime_error("Unsupported type: " + type);
        }
}
};
