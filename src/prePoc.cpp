#include "prePoc.hpp"

DataCleaner::DataCleaner(char filePath[]){
    ifstream inputFile;
    inputFile.open(filePath);
    string trainingExample;
    while(!inputFile.eof()){
        getline(inputFile,trainingExample);
        cout<<trainingExample<<endl;
    }
}
