#include "id3.cpp"
#include<fstream>

int main(int argc,char *argv[]){
    char *pathDataTrain= "../../Data/trainData.txt";
    char *pathLabelTrain="../../Data/trainOutput.txt";
    int NumberOfInstances=32561;
    int NumberOfFeatures=14;
    float Entropy0;
    Entropy0=createSet(pathDataTrain,pathLabelTrain,NumberOfInstances,NumberOfFeatures);
    cout<<Entropy0<<endl;
    
    return 0;
}