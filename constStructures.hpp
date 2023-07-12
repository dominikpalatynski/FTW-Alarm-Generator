#include <iostream>

struct ConstAlarmText
{
    const std::string text_1  = "\" type=\"value\" ack-all-value=\"0\" use-ack-all=\"false\" ack-tag=\"\" exp=\"{::";
    const std::string text_2 = "}\" message-tag=\"\" message-handshake-exp=\"\" message-notification-tag=\"\" remote-ack-exp=\"\" remote-ack-handshake-tag=\"\" ";
    const std::string text_3 = "\" handshake-tag=\"\"/>";
};
struct ConstMessageText
{
    const std::string text_1 = "\" backcolor=\"#800000\" forecolor=\"#FFFFFF\" audio=\"false\" display=\"true\" print=\"false\" message-to-tag=\"false\" text=\"?\"/>";
};
