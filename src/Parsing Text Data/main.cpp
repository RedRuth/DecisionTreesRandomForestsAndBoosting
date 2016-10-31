#include "prePoc.hpp"

int main(){
    int instances=16281;
    DataCleaner training("../../Data/adult.test.txt",instances);
    ofstream output;
    output.open("../../Data/testData.txt");
    
    for(int i=0;i<instances;i++){
        for(int j=0;j<14;j++)
            output<<training.featureMatrix[i][j]<<endl;
    }
    output.close();
    ofstream output2;
    output2.open("../../Data/testOutput.txt");
    for(int i=0;i<instances;i++)
        output2<<training.outputVector[i]<<endl;
    
    return 0;
}
