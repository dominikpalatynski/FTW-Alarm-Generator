#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include "logic.hpp"
Tag::Tag(const std::string &name, const std::string &type) : name(name), type(type) {}

std::pair<std::string, int> Tag::getTypeInfo() const
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

Alarm::Alarm(const std::string &trigger, const std::string &tag, const std::string &label, int idNumber)
    : combinedLine(trigger + constString.text_1 + tag + constString.text_2 + label + constString.text_3),
      alarmVariables(idNumber, AlarmValues(tag)) {}

Alarm::Alarm(const std::string &combine) : combinedLine(combine),
                                           alarmVariables(readLastIndex(combinedLine, "id=\"T"), AlarmValues(findPhrase(combine, "exp=\"{::", "}"))){};
int Alarm::readLastIndex(const std::string &combLine, const std::string &startValue)
{
        std::size_t startVal = combLine.find(startValue);
        std::size_t numberStart;
        std::size_t numberEnd;

        if (startVal != std::string::npos)
        {
                std::size_t endPos = combLine.find("\"", startVal);

                if (endPos != std::string::npos)
                {
                        numberStart = combLine.find_first_of("0123456789", startVal + 5);
                        numberEnd = combLine.find_first_not_of("0123456789", numberStart);
                        std::string indexNumber = combLine.substr(numberStart, numberEnd - numberStart);

                        return std::stoi(indexNumber);
                }
        }
}
std::string Alarm::findPhrase(const std::string &combine, const std::string &open, const std::string &end)
{
        std::size_t startVal = combine.find(open);
        if (startVal != std::string::npos)
        {
                std::size_t endPos = combine.find(end, startVal);
                return combine.substr(startVal + open.size(), endPos - startVal - open.size());
        }
}
std::pair<int, AlarmValues> Alarm::getAlarVariables()
{
        return alarmVariables;
}
Message::Message(const std::string &M1, const std::string &M2, int idNumber)
    : combinedLine(M1 + M2 + constString.text_1), messageVariables(idNumber, MessageValues(constString.text_1)) {}
Message::Message(const std::string &combine) : combinedLine(combine),
                                               messageVariables({readLastIndex(combinedLine, "id=\"T"), MessageValues(findPhrase(combine, "text=\"", "\"/"))}){};
int Message::readLastIndex(const std::string &combLine, const std::string &startValue)
{
        std::size_t startVal = combLine.find(startValue);
        std::size_t numberStart;
        std::size_t numberEnd;

        if (startVal != std::string::npos)
        {
                std::size_t endPos = combLine.find("\"", startVal);

                if (endPos != std::string::npos)
                {
                        numberStart = combLine.find_first_of("0123456789", startVal + 5);
                        numberEnd = combLine.find_first_not_of("0123456789", numberStart);
                        std::string indexNumber = combLine.substr(numberStart, numberEnd - numberStart);

                        return std::stoi(indexNumber);
                }
        }
}
std::string Message::findPhrase(const std::string &combine, const std::string &open, const std::string &end)
{
        std::size_t startVal = combine.find(open);
        if (startVal != std::string::npos)
        {
                std::size_t endPos = combine.find(end, startVal);
                return combine.substr(startVal + open.size(), endPos - startVal - open.size());
        }
}

Aplication::Aplication(const int &num, const Tag &tags) : numOfAlarms(num), tag(tags) {}
void Aplication::prepareStrings()
{

        std::string T1 = "<trigger id=\"T";
        std::string T2 = "label=\"";
        std::string tagName = tag.getTypeInfo().first;
        std::string M1 = "<message id=\"M";
        std::string M2 = "\" trigger-value=\"1\" identifier=\"0\" trigger=\"#T";
        int bitValue = tag.getTypeInfo().second;
        int prev = 0;
        int curr = 0;
        int bitCounter = 0;
        int byteCounter = 0;
        for (int i = 0; i < numOfAlarms; i++)
        {
                curr = i % bitValue;
                if (prev > curr)
                {
                        bitCounter = 0;
                }
                if (curr == 0)
                {
                        byteCounter++;
                }
                generatedAlarms.emplace_back(T1 + std::to_string(i + 1), tag.name + '[' + std::to_string(byteCounter - 1) + "]." + std::to_string(bitCounter), T2 + std::to_string(i + 1), i);
                generatedMessages.emplace_back(M1 + std::to_string(i + 1), M2 + std::to_string(i + 1), i);
                prev = i % bitValue;
                bitCounter++;
        }
}
void Aplication::prepareBlankFrame()
{
        FormatText frameStr;

        for (const auto &el : frameStr.beginOfFrame)
        {
                blankStream << el << " ";
        }
        blankStream << "\n"
                    << frameStr.eleventhS << "\n";

        std::string alarmsString = std::accumulate(generatedAlarms.begin(), generatedAlarms.end(), std::string(),
                                                   [](const std::string &accumulated, const Alarm &alarm)
                                                   {
                                                           return accumulated + alarm.combinedLine + "\n";
                                                   });

        blankStream << alarmsString << "\n"
                    << frameStr.sixthS << "\n"
                    << frameStr.seventhS << "\n";

        alarmsString = std::accumulate(generatedMessages.begin(), generatedMessages.end(), std::string(),
                                       [](const std::string &accumulated, const Message &message)
                                       {
                                               return accumulated + message.combinedLine + "\n";
                                       });

        blankStream << alarmsString << "\n";
        blankStream << frameStr.eightS << "\n"
                    << frameStr.ninethS << "\n"
                    << frameStr.tenthS;
}

void Aplication::printFrameInConsole()
{
        prepareStrings();
        prepareBlankFrame();
        std::cout << blankStream.str();
}
void Aplication::printBlankFrametoXmlFile()
{
        prepareStrings();
        prepareBlankFrame();
        std::string filename;
        std::cout << "Give file name \n";
        std::cin >> filename;
        filename += ".xml";
        std::ofstream file(filename, std::ios::out);
        if (file.is_open())
        {
                file << blankStream.str();
                file.close();
                std::cout << "Pomyślnie utworzono i zapisano do pliku " << filename << std::endl;
        }
        else
        {
                std::cerr << "Nie można utworzyć pliku " << filename << " do zapisu" << std::endl;
        }
}
void Aplication::readA_MFromFile(const std::string &fileName, const std::string &startMarker, const std::string &endMarker, char choice)
{
        std::string line;
        bool insideTrigger = false;
        std::ifstream file(fileName);
        if (!file.is_open())
        {
                std::cerr << "Cannot oppen this file" << std::endl;
        }

        while (std::getline(file, line))
        {
                if (!insideTrigger && line.find(startMarker) != std::string::npos)
                {
                        insideTrigger = true;
                        continue;
                }
                if (line.find(endMarker) != std::string::npos)
                {
                        insideTrigger = false;
                        break;
                }
                if (insideTrigger)
                {
                        if (choice == 'a')
                        {
                                generatedAlarms.emplace_back(line);
                        }
                        else if (choice == 'm')
                        {
                                generatedMessages.emplace_back(line);
                        }
                }
        }
}
void Aplication::updateFile()
{
        std::string fileName;
        int lastIndexNumber;

        std::cout << "Give file name to update \n";
        std::cin >> fileName;

        readA_MFromFile(fileName, "<triggers>", "</triggers>", 'a');
        readA_MFromFile(fileName, "<messages>", "</messages>", 'm');
        for (auto el : generatedAlarms)
        {
                std::cout << el.getAlarVariables().first << " " << el.getAlarVariables().second.tagName << "\n";
        }
        // std::shared_ptr<Alarm> lastAlarm = std::make_shared<Alarm>(*(++generatedAlarms.rbegin()));

        // if (!generatedAlarms.empty())
        // {
        //         lastIndexNumber = readLastIndex(lastAlarm->combinedLine);
        // }
        // else
        // {
        //         std::cout << "No alarms found.\n";
        // }
}
int Aplication::readLastIndex(const std::string &combLine, const std::string &startValue)
{
        std::size_t startVal = combLine.find(startValue);
        std::size_t numberStart;
        std::size_t numberEnd;

        if (startVal != std::string::npos)
        {
                std::size_t endPos = combLine.find("\"", startVal);

                if (endPos != std::string::npos)
                {
                        numberStart = combLine.find_first_of("0123456789", startVal + 5);
                        numberEnd = combLine.find_first_not_of("0123456789", numberStart);
                        std::string indexNumber = combLine.substr(numberStart, numberEnd - numberStart);

                        return std::stoi(indexNumber);
                }
        }
}

void Aplication::menu()
{
        std::map<int, std::function<void()>> menuOption = {
            {1, [&]()
             { printFrameInConsole(); }},
            {2, [&]()
             { printBlankFrametoXmlFile(); }},
            {3, [&]()
             { updateFile(); }}

        };
        int choice;
        std::cout << "Choose option \n"
                  << "1: Print alarm frame in console and copy by your own to xml file \n"
                  << "2: Select file name then alarm frame will be printed to xml file \n"
                  << "3: Read alarms from file \n"

                  << "0: Leave\n";
        do
        {

                std::cin >> choice;
                auto it = menuOption.find(choice);
                if (it != menuOption.end())
                {
                        it->second();
                        std::cout << "Program Complete";
                        break;
                }
                else if (choice != 0)
                {
                        std::cout << "Incorrect choice";
                }

        } while (choice != 0);
}
