#include "Message.hpp"
Message::Message(const std::string &M1, const std::string &M2, int idNumber)
    : combinedLine(M1 + M2 + constString.text_1), messageVariables(idNumber, MessageValues(constString.text_1)) {}
Message::Message(const std::string &combine) :  messageVariables({readLastIndex(combine, "id=\"M"), MessageValues(findPhrase(combine, "text=\"", "\"/"))}),
        combinedLine(combine){};
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
    std::pair<int, MessageValues> Message::getAlarVariables(){
        return messageVariables;
    }
        void Message::setMessageVariables(const std::string &value){
                messageVariables.second.messageText = value;
        }
    void Message::replace(const std::string &newValue){
        size_t startPos =  combinedLine.find( messageVariables.second.messageText);
         size_t endPos = startPos + messageVariables.second.messageText.length();
        combinedLine.replace(startPos, endPos - startPos, newValue);
        setMessageVariables(newValue);
    }

