#include <iostream>

struct ConstAlarmText
{
    const std::string text_1 = "\" type=\"value\" ack-all-value=\"0\" use-ack-all=\"false\" ack-tag=\"\" exp=\"{::";
    const std::string text_2 = "}\" message-tag=\"\" message-handshake-exp=\"\" message-notification-tag=\"\" remote-ack-exp=\"\" remote-ack-handshake-tag=\"\" ";
    const std::string text_3 = "\" handshake-tag=\"\"/>";
};
struct ConstMessageText
{
    const std::string text_1 = "\" backcolor=\"#800000\" forecolor=\"#FFFFFF\" audio=\"false\" display=\"true\" print=\"false\" message-to-tag=\"false\" text=\"?\"/>";
};
struct FormatText
{
    std::string firstS = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    std::string secondS = "<alarms version=\"1.0\" product=\"{E44CB020-C21D-11D3-8A3F-0010A4EF3494}\" id=\"Alarms\">\n";
    std::string thirdS = " <alarm history-size=\"128\" capacity-high-warning=\"90\" capacity-high-high-warning=\"99\"";
    std::string fourthS = "display-name=\"\" hold-time=\"250\" max-update-rate=\"1,00\" embedded-server-update-rate=\"1,00\" silence-tag=\"\" remote-silence-exp=\"\" remote-ack-all-exp=\"\"";
    std::string fifthS = "status-reset-tag=\"\" remote-status-reset-exp=\"\" close-display-tag=\"\" remote-close-display-exp=\"\" use-alarm-identifier=\"false\" capacity-high-warning-tag=\"\" capacity-high-high-warning-tag=\"\" capacity-overrun-tag=\"\" remote-clear-history-exp=\"?\">\n";
    std::string sixthS = "</triggers>";
    std::string seventhS = "<messages>";
    std::string eightS = "</messages>";
    std::string ninethS = "</alarm>";
    std::string tenthS = "</alarms>";
    std::string eleventhS = "<triggers>";

    std::vector<std::string> beginOfFrame;

    FormatText() : beginOfFrame({firstS, secondS, thirdS, fourthS, fifthS}){};
};
struct MessageValues
{
    std::string messageText;
    MessageValues(const std::string& messageTxt):messageText(messageTxt){};

};
struct AlarmValues
{
    std::string tagName;
    AlarmValues(const std::string& tagName):tagName(tagName){};
};