#include "Application.hpp"

Aplication::Aplication(const int &num, const Tag &tags) : numOfAlarms(num), tag(tags) {}
void Aplication::prepareStrings()
{

        std::string T1 = "<trigger id=\"T";
        std::string T2 = "label=\"";
        std::string tagName = tag.getTypeInfo().first;
        std::string M1 = "<message id=\"M";
        std::string M2 = "\" trigger-value=\"1\" identifier=\"0\" trigger=\"#T";
        int bitValue = tag.getTypeInfo().second;
        int prev = 0;
        int curr = 0;
        int bitCounter = 0;
        int byteCounter = 0;
        for (int i = 0; i < numOfAlarms; i++)
        {
                curr = i % bitValue;
                if (prev > curr)
                {
                        bitCounter = 0;
                }
                if (curr == 0)
                {
                        byteCounter++;
                }
                generatedAlarms.emplace_back(T1 + std::to_string(i + 1), tag.name , T2 + std::to_string(i + 1), i);
                generatedMessages.emplace_back(M1 + std::to_string(i + 1), M2 + std::to_string(i + 1), i);
                prev = i % bitValue;
                bitCounter++;
        }
}
void Aplication::prepareStrings(int numOfAlamrs, int firstTriggerNumber){
        std::string T1 = "<trigger id=\"T";
        std::string T2 = "label=\"";
        
        std::string M1 = "<message id=\"M";
        std::string M2 = "\" trigger-value=\"1\" identifier=\"0\" trigger=\"#T";

                int vecIndex = 0;
                int i = firstTriggerNumber;
                for(auto el:dataToUpdate){
                generatedAlarms.emplace_back(T1 + std::to_string(i + 1), el.first , T2 + std::to_string(i + 1), i);
                generatedMessages.emplace_back(M1 + std::to_string(i + 1), M2 + std::to_string(i + 1), i);
                generatedMessages[vecIndex].replace(std::get<0>(el.second));


                i++;
                vecIndex++;
                }
        std::cout<<"Addition to vector done"<<"\n";
               
              
               
        
}
void Aplication::prepareBlankFrame()
{
        FormatText frameStr;

        for (const auto &el : frameStr.beginOfFrame)
        {
                blankStream << el << " ";
        }
        blankStream << "\n"
                    << frameStr.eleventhS << "\n";

        std::string alarmsString = std::accumulate(generatedAlarms.begin(), generatedAlarms.end(), std::string(),
                                                   [](const std::string &accumulated, const Alarm &alarm)
                                                   {
                                                           return accumulated + alarm.combinedLine + "\n";
                                                   });

        blankStream << alarmsString << "\n"
                    << frameStr.sixthS << "\n"
                    << frameStr.seventhS << "\n";

        alarmsString = std::accumulate(generatedMessages.begin(), generatedMessages.end(), std::string(),
                                       [](const std::string &accumulated, const Message &message)
                                       {
                                               return accumulated + message.combinedLine + "\n";
                                       });

        blankStream << alarmsString << "\n";
        blankStream << frameStr.eightS << "\n"
                    << frameStr.ninethS << "\n"
                    << frameStr.tenthS;
}

void Aplication::printFrameInConsole()
{
        prepareStrings();
        prepareBlankFrame();
        std::cout << blankStream.str();
}
void Aplication::printBlankFrametoXmlFile()
{
        prepareStrings();
        prepareBlankFrame();
        std::string filename;
        std::cout << "Give file name \n";
        std::cin >> filename;
        filename += ".xml";
        std::ofstream file(filename, std::ios::out);
        if (file.is_open())
        {
                file << blankStream.str();
                file.close();
                std::cout << "Pomyślnie utworzono i zapisano do pliku " << filename << std::endl;
        }
        else
        {
                std::cerr << "Nie można utworzyć pliku " << filename << " do zapisu" << std::endl;
        }
}
void Aplication::readA_MFromFile(const std::string &fileName, const std::string &startMarker, const std::string &endMarker, char choice)
{
        std::string line;
        bool insideTrigger = false;
        bool foundEndMarker = false;
        std::ifstream file(fileName);
        if (!file.is_open())
        {
                std::cerr << "Cannot oppen this file" << std::endl;
        }
        int i = 0;
        while (std::getline(file, line))
        {            if (line.empty())
            {
                continue; // skipping empty line
            }
                
                if (!insideTrigger && line.find(startMarker) != std::string::npos)
                {
                        insideTrigger = true;
                       
                        continue;
                }
                if (line.find(endMarker) != std::string::npos)
                {
                        insideTrigger = false;
                        foundEndMarker = true;
                        std::cout<<"AddingDone"<<"\n";
                        break;
                }
              
                if (insideTrigger)
                {
                        if (choice == 'a')
                        {      
                                generatedAlarms.emplace_back(line);
                        }
                        else if (choice == 'm')
                        {
                                generatedMessages.emplace_back(line);
                               

                        }
                }
             
             
        }
      
}
void Aplication::updateFile()
{
        std::string fileName;
        int lastIndexNumber;

        std::cout << "Give file name to update \n";
        std::cin >> fileName;

        readA_MFromFile(fileName, "<triggers>", "</triggers>", 'a');
        readA_MFromFile(fileName, "<messages>", "</messages>", 'm');
        for (auto el : generatedMessages)
        {
                std::cout << el.combinedLine<<" \n";
        }
        std::shared_ptr<Alarm> lastAlarm = std::make_shared<Alarm>(*(++generatedAlarms.rbegin()));

        if (!generatedAlarms.empty())
        {
                lastIndexNumber = readLastIndex(lastAlarm->combinedLine,"id=\"T");
        }
        else
        {
                std::cout << "No alarms found.\n";
        }
}
int Aplication::readLastIndex(const std::string &combLine, const std::string &startValue)
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
    void Aplication::readFromCsv(const std::string &fileName){
        std::ifstream file(fileName);
        if(!file.is_open()){
                std::cerr<<"Cannot open this file"<<"\n";
        }

        std::string line;
        std::string tagName;
        std::string textMessage;
        while(std::getline(file,line)){
                std::size_t pos = line.find(';');
                tagName = line.substr(0,pos);
                textMessage = line.substr(pos+1);
                dataToUpdate[tagName] = std::make_tuple(textMessage,0);
        }
        file.close();
        for(auto it: dataToUpdate){
               std::cout<< it.first<< " "<<std::get<1>(it.second)<<"\n";
        }
    }

  
    void Aplication::generateFromExcel(){
        std::string fileInput;
        std::cout << "Give CSV file name \n";
        std::cin >> fileInput;
        readFromCsv( fileInput);
        prepareStrings(dataToUpdate.size(),0);
        prepareBlankFrame();

        std::string filename;
        std::cout << "Give file name \n";
        std::cin >> filename;
        filename += ".xml";
        std::ofstream file(filename, std::ios::out);
        if (file.is_open())
        {
                file << blankStream.str();
                file.close();
                std::cout << "Pomyślnie utworzono i zapisano do pliku " << filename << std::endl;
        }
        else
        {
                std::cerr << "Nie można utworzyć pliku " << filename << " do zapisu" << std::endl;
        }
    }


void Aplication::menu()
{
        std::map<int, std::function<void()>> menuOption = {
            {1, [&]()
             { printFrameInConsole(); }},
            {2, [&]()
             { printBlankFrametoXmlFile(); }},
            {3, [&]()
             { generateFromExcel(); }}

        };
        int choice;
        std::cout << "Choose option \n"
                  << "1: Print alarm frame in console and copy by your own to xml file \n"
                  << "2: Select file name then alarm frame will be printed to xml file \n"
                  << "3: Read alarms from file \n"

                  << "0: Leave\n";
        do
        {

                std::cin >> choice;
                auto it = menuOption.find(choice);
                if (it != menuOption.end())
                {
                        it->second();
                        std::cout << "Program Complete";
                        break;
                }
                else if (choice != 0)
                {
                        std::cout << "Incorrect choice";
                }

        } while (choice != 0);
}
