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
#include <map>
#include <tuple>
#include "constStructures.hpp"
#include "Message.hpp"
#include "Alarm.hpp"
#include "Tag.cpp"
class Aplication
{
private:
    int numOfAlarms;
    Tag tag;
    std::string blankFrame;
    std::stringstream blankStream;
    std::map<std::string,std::tuple<std::string,bool>> dataToUpdate;

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
    void readFromCsv(const std::string &fileName);
    void generateFromExcel();
    void prepareStrings(int numOfAlamrs, int firstTriggerNumber);
    void menu();
};
