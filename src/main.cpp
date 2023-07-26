#include "Application.hpp"
#include "Alarm.hpp"
#include "Message.hpp"
int main()
{

    Aplication app(200, {"[Tags_PLC]Program:Station10_Module100.ST10_100_Variables.Control.xAlarmReset", "dint"});
    // app.menu();
    // Message message("<message id=\"M2\" trigger-value=\"1\" identifier=\"0\" trigger=\"#T2\" backcolor=\"#800000\" forecolor=\"#FFFFFF\" audio=\"false\" display=\"true\" print=\"false\" message-to-tag=\"false\" text=\"?\"/>");
    // std::cout<<message.getAlarVariables().first<<" "<<message.getAlarVariables().second.messageText<<"\n ";
    // std::cout<<message.combinedLine<<"\n ";

    // message.replace("test");
    // std::cout<<message.getAlarVariables().first<<" "<<message.getAlarVariables().second.messageText<<"\n ";
    // std::cout<<message.combinedLine<<"\n ";
    app.readFromCsv("alarms.csv");





    return 0;
}