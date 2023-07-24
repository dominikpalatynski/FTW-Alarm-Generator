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

    Tag(const std::string &name, const std::string &type);

    std::pair<std::string, int> getTypeInfo() const;
};

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
};
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
};
class Aplication
{
private:
    int numOfAlarms;
    Tag tag;
    std::string blankFrame;
    std::stringstream blankStream;

public:
    std::vector<Alarm> generatedAlarms;
    std::vector<Message> generatedMessages;
    Aplication(const int &num, const Tag &tags);
    void prepareStrings();
    void printFrameInConsole();
    void prepareBlankFrame();
    void printBlankFrametoXmlFile();
    void updateFile();
    void readA_MFromFile(const std::string &fileName, const std::string &startMarker, const std::string &endMarker, char choice);
    int readLastIndex(const std::string &combLine, const std::string &startValue);
    std::string findPhrase(const std::string &combine, const std::string &open, const std::string &end);
    void menu();
};
