#pragma once
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
class Message
{
private:
    ConstMessageText constString;
    std::pair<int, MessageValues> messageVariables;

public:
    std::string combinedLine;
    Message(const std::string &M1, const std::string &M2, int idNumber);
    Message(const std::string &combine);
    int readLastIndex(const std::string &combLine, const std::string &startValue);
    std::string findPhrase(const std::string &combine, const std::string &open, const std::string &end);
    std::pair<int, MessageValues> getAlarVariables();
    void setMessageVariables(const std::string &value);
    void replace(const std::string &newValue);

};