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


       
            Message::Message( const std::string& M1,const std::string& M2)
        : combinedLine(M1+M2+constString.text_1) {}




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
                blankFrame += " "  + el;
        }
        blankFrame += "\n" + frameStr.eleventhS + "\n";

        std::string alarmsString = std::accumulate(generatedAlarms.begin(), generatedAlarms.end(), std::string(),
                [](const std::string& accumulated, const Alarm& alarm) {
                return accumulated + alarm.combinedLine + "\n" ;
                }
        );

        blankFrame += alarmsString + "\n" + frameStr.sixthS + "\n" + frameStr.seventhS + "\n";
      

          alarmsString = std::accumulate(generatedMessages.begin(), generatedMessages.end(), std::string(),
                [](const std::string& accumulated, const Message& message) {
                return accumulated + message.combinedLine+ "\n";
                });
        blankFrame += alarmsString + "\n";
        blankFrame += frameStr.eightS + "\n" + frameStr.ninethS + "\n" + frameStr.tenthS;
        }

        void Aplication::printFrameInConsole(){
                prepareStrings();
               prepareBlankFrame();
                std::cout<<blankFrame;
            
        }
        void Aplication::printBlankFrametoXmlFile() {
                prepareStrings();
                prepareBlankFrame();
                std::string filename;
                std::cout<<"Give file name";
                std::cin>>filename;
                std::ofstream file(filename, std::ios::out);
                if (file.is_open()) {
                        file << blankFrame;
                        file.close();
                        std::cout << "Pomyślnie utworzono i zapisano do pliku " << filename << std::endl;
                } else {
                        std::cerr << "Nie można utworzyć pliku " << filename << " do zapisu" << std::endl;
                }
        }
        void Aplication::menu(){
                std::map<int,std::function<void()>> menuOption = {
                        {1,[&](){printFrameInConsole();}},
                        {2,[&](){printBlankFrametoXmlFile();}}
                };
                int choice;
                                        std::cout<<"Choose option \n"
                                        <<"1: Print alarm frame in console and copy by your own to xml file \n"
                                        <<"2: Select file name then alarm frame will be printed to xml file \n"
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


