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
class Alarm
{

private:
    ConstAlarmText constString;
    std::pair<int, AlarmValues> alarmVariables;

public:
    std::string combinedLine;
    Alarm(const std::string &trigger, const std::string &tag, const std::string &label, int idNumber);
    Alarm(const std::string &combined);
    int readLastIndex(const std::string &combLine, const std::string &startValue);
    std::string findPhrase(const std::string &combine, const std::string &open, const std::string &end);
    std::pair<int, AlarmValues> getAlarVariables();
    void setAlarmVariables(const std::string &value);
    void replace(const std::string &newValue);
};