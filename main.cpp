#include <iostream>
#include <vector>
#include <string>
#include <utility>

class Tag {
public:
    std::string name;
    std::string type;

    Tag(const std::string& name, const std::string& type) : name(name), type(type) {}

    std::pair<std::string ,int> getTypeInfo() const{
        if(type == "sint"){
                return std::make_pair(name,8);
        }
        else if(type == "int"){
                return std::make_pair(name,16);

        }
        else if(type == "dint"){
                return std::make_pair(name,32);
        }
        else{
                throw std::runtime_error("Unsupported type: " + type); 
        }
    }

};

class Alarm {
        
private:
    const std::string constansValueV1 = "\" type=\"value\" ack-all-value=\"0\" use-ack-all=\"false\" ack-tag=\"\" exp=\"{::";
    const std::string constansValueV2 = "}\" message-tag=\"\" message-handshake-exp=\"\" message-notification-tag=\"\" remote-ack-exp=\"\" remote-ack-handshake-tag=\"\" ";
    const std::string constansValueV3 = "\" handshake-tag=\"\"/>";
public:
    std::string combinedLine;
    Alarm( const std::string& trigger,const std::string& tag, const std::string& label)
        : combinedLine(trigger+constansValueV1 + tag + constansValueV2 + label + constansValueV3) {}
};
class Message{
private:
        const std::string constMessageValueV1 = "\" backcolor=\"#800000\" forecolor=\"#FFFFFF\" audio=\"false\" display=\"true\" print=\"false\" message-to-tag=\"false\" text=\"?\"/>";
  public:
        std::string combinedLine;
            Message( const std::string& M1,const std::string& M2)
        : combinedLine(M1+M2+constMessageValueV1) {}

};
class Aplication{
private:
        int numOfAlarms;
        Tag tag;
public:
        std::vector<Alarm> generatedAlarms;
        std::vector<Message> generatedMessages;
        Aplication(const int &num, const Tag &tags): numOfAlarms(num),tag(tags) {}
        void prepareStrings(){
                std::string T1 = "<trigger id=\"T";
                std::string T2 = "label=\"";
                std::string tagName = tag.getTypeInfo().first;
                std::string  M1 = "<message id=\"M";
                std::string M2 = "\" trigger-value=\"1\" identifier=\"0\" trigger=\"#T";
                 int bitValue= tag.getTypeInfo().second;
                 int prev = 0;
                 int curr = 0;
                int bitCounter = 0;
                int byteCounter = 0;
              for(int i=0 ;i < numOfAlarms;i++){
                curr = i% bitValue;
                if(prev>curr){
                        bitCounter = 0;
                }
                if(curr == 0){
                        byteCounter++;
                }
                generatedAlarms.emplace_back(T1+std::to_string(i+1),tag.name + '['+std::to_string(byteCounter - 1) + "]."+ std::to_string(bitCounter),T2+std::to_string(i+1));
                generatedMessages.emplace_back(M1+std::to_string(i+1),M2+std::to_string(i+1));
                prev = i% bitValue;
                bitCounter++;     


              }  
        }
        void printFrameInConsole(){
                   for(auto el:generatedAlarms){
                        std::cout<<el.combinedLine<<std::endl;
                }
                     for(auto el:generatedMessages){
                        std::cout<<el.combinedLine<<std::endl;
                }
        }

}; 
int main() {
         std::vector<Alarm> alarmsDone;
        Tag tag("FirstTag","int");
        Aplication app(100,{"FirstTag","dint"});
        app.prepareStrings();
        app.printFrameInConsole();
    

    return 0;
}