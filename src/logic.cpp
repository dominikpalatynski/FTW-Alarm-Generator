#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include "logic.hpp"
   Tag::Tag(const std::string& name, const std::string& type) : name(name), type(type) {}

    std::pair<std::string ,int> Tag::getTypeInfo() const{
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



        
    Alarm::Alarm( const std::string& trigger,const std::string& tag, const std::string& label)
        : combinedLine(trigger + constString.text_1 + tag + constString.text_2 + label + constString.text_3) {}

    Alarm::Alarm(const std::string &combine):combinedLine(combine){};

       
            Message::Message( const std::string& M1,const std::string& M2)
        : combinedLine(M1+M2+constString.text_1) {}
          Message::Message(const std::string & combine):combinedLine(combine){};





      Aplication::Aplication(const int &num, const Tag &tags): numOfAlarms(num),tag(tags) {}
        void Aplication::prepareStrings(){
                

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
        void Aplication::prepareBlankFrame() {
        FormatText frameStr;
        
        for (const auto& el : frameStr.beginOfFrame) {
                blankStream <<el<<" ";

        }
        blankStream<<"\n"<<frameStr.eleventhS<<"\n";

        std::string alarmsString = std::accumulate(generatedAlarms.begin(), generatedAlarms.end(), std::string(),
                [](const std::string& accumulated, const Alarm& alarm) {
                return accumulated + alarm.combinedLine + "\n" ;
                }
        );

        blankStream << alarmsString << "\n" << frameStr.sixthS << "\n" << frameStr.seventhS << "\n";

      

          alarmsString = std::accumulate(generatedMessages.begin(), generatedMessages.end(), std::string(),
                [](const std::string& accumulated, const Message& message) {
                return accumulated + message.combinedLine+ "\n";
                });
     
                blankStream<< alarmsString << "\n";
                blankStream <<frameStr.eightS << "\n" << frameStr.ninethS << "\n" << frameStr.tenthS;
        }

        void Aplication::printFrameInConsole(){
                prepareStrings();
               prepareBlankFrame();
                std::cout<<blankStream.str();
            
        }
        void Aplication::printBlankFrametoXmlFile() {
                prepareStrings();
                prepareBlankFrame();                     
                std::string filename;
                std::cout<<"Give file name \n";
                std::cin>>filename;
                filename+=".xml";
                std::ofstream file(filename, std::ios::out);
                if (file.is_open()) {
                        file << blankStream.str();
                        file.close();
                        std::cout << "Pomyślnie utworzono i zapisano do pliku " << filename << std::endl;
                } else {
                        std::cerr << "Nie można utworzyć pliku " << filename << " do zapisu" << std::endl;
                }
        }
        void Aplication::readA_MFromFile(const std::string &fileName,const std::string &startMarker,const std::string &endMarker,char choice) {
                std::string line;
                bool insideTrigger = false;
                std::ifstream file(fileName);
                if(!file.is_open()){
                        std::cerr << "Cannot oppen this file" << std::endl; 
                }

                while(std::getline(file,line)){
                        if(!insideTrigger && line.find(startMarker) != std::string::npos){
                                insideTrigger = true;
                        }
                        if(insideTrigger){
                                if(choice == 'a'){
                                generatedAlarms.emplace_back(line);
                                }
                                else if(choice == 'm'){
                                generatedMessages.emplace_back(line);  
                                }
                                if(line.find(endMarker) != std::string::npos){
                                        insideTrigger = false;
                                        break;
                                }
                        }
                }
                for(auto el:generatedAlarms){
                        std::cout<<el.combinedLine<<"\n";
                }
        

        }
        void Aplication::updateFile(){
                std::string fileName;
                std::cout<<"Give file name to update \n";
                std::cin>>fileName;
                readA_MFromFile(fileName,"<messages>","</messages>",'m');
                auto it = generatedMessages.begin();
                for(auto &el:generatedAlarms){
                        std::cout<<el.combinedLine<<"\n";
                        std::cout<<it->combinedLine<<" \n ";
                        it++;
                }
        }

        void Aplication::menu(){
                std::map<int,std::function<void()>> menuOption = {
                        {1,[&](){printFrameInConsole();}},
                        {2,[&](){printBlankFrametoXmlFile();}},
                        {3,[&](){ readA_MFromFile("file.xml","<messages>","</messages>",'m');}}

                };
                int choice;
                                        std::cout<<"Choose option \n"
                                        <<"1: Print alarm frame in console and copy by your own to xml file \n"
                                        <<"2: Select file name then alarm frame will be printed to xml file \n"
                                        <<"3: Read alarms from file \n"

                                        <<"0: Leave\n";
                do{
                    
                        std::cin>>choice;
                        auto it = menuOption.find(choice);
                        if(it != menuOption.end()){
                                it->second();
                                std::cout<<"Program Complete";
                                break;
                        }
                        else if(choice !=0 ){
                                std::cout<<"Incorrect choice";
                        }
                        

                }
                while (choice != 0);
             
                
        }


