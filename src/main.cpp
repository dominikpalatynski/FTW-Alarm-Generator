#include "logic.hpp"
int main() {

        Tag tag("FirstTag","int");
        Aplication app(200,{"[Tags_PLC]Program:Station10_Module100.ST10_100_Variables.Control.xAlarmReset","dint"});
        app.menu();

    return 0;
}