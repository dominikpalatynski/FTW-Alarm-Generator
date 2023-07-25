#include "Alarm.hpp"
Alarm::Alarm(const std::string &trigger, const std::string &tag, const std::string &label, int idNumber)
    : combinedLine(trigger + constString.text_1 + tag + constString.text_2 + label + constString.text_3),
      alarmVariables(idNumber, AlarmValues(tag)) {}
Alarm::Alarm(const std::string &combine)
    : alarmVariables(readLastIndex(combine, "id=\"T"), AlarmValues(findPhrase(combine, "exp=\"{::", "}"))),
      combinedLine(combine)
{


}

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
        return -1;
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
    void Alarm::setAlarmVariables (const std::string &value){
        alarmVariables.second.tagName = value;
    }
    void Alarm::replace (const std::string &newValue){
        size_t startPos =  combinedLine.find( alarmVariables.second.tagName);
        combinedLine.replace(startPos,newValue.length(),newValue);
    }