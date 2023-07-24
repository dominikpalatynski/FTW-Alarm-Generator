#include "logic.hpp"
int main()
{

    Aplication app(200, {"[Tags_PLC]Program:Station10_Module100.ST10_100_Variables.Control.xAlarmReset", "dint"});
    app.menu();
    // Alarm alarm("id=\"T1\" type=\"value\" ack-all-value=\"0\" use-ack-all=\"false\" ack-tag=\"\" exp=\"{::[Tags_PLC]Program:Station10_Module100.ST10_100_Variables.Control.xAlarmReset[0].0}\" message-");
    // std::cout << alarm.getAlarVariables().second.tagName;
    return 0;
}