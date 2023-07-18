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




class Tag {
public:
    std::string name;
    std::string type;

    Tag(const std::string& name, const std::string& type);

    std::pair<std::string ,int> getTypeInfo() const;


};

class Alarm {
        
private:

    ConstAlarmText constString;
public:
    std::string combinedLine;
    Alarm( const std::string& trigger,const std::string& tag, const std::string& label);
    Alarm(const std::string& combined);
};
class Message{
private:
        ConstMessageText constString;
  public:
        std::string combinedLine;
            Message( const std::string& M1,const std::string& M2);
            Message(const std::string & combine);
};
class Aplication{
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
        void readA_MFromFile(const std::string &fileName,const std::string &startMarker,const std::string &endMarker,char choice);
        int readLastIndex(const std::string & combLine);
        void menu();
 

}; 
