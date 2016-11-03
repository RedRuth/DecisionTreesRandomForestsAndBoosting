#include<iostream>
#include<fstream>
using namespace std;
int seperate(int a,int boundary){
    
    if(a==-1)
        return -1;
    else if(a<boundary)
        return 0;
    else
        return 1;
}

int main(){
    int instanesTrain=32561;
    int instancesTest=16281;
    fstream inFileTrain,inFileTest;
    ofstream outFileTrain,outFileTest;
    inFileTrain.open("../../../Data/trainData.txt");
    
    outFileTrain.open("../../../Data/trainDataDisc.txt");
    
    inFileTest.open("../../../Data/testData.txt");
    
    outFileTest.open("../../../Data/testDataDisc.txt");
    
    int features=14;
    int temp;
    int sep[13]={28,0,209912,0,12,0,0,0,0,0,7298,1825,42};
    for(int i=0;i<instanesTrain;i++){
        
        for(int j=0;j<features;j++){
            inFileTrain >>temp;
            
            if(j==0 || j==2 ||j==4 || j==10 || j==11 || j==12)
                temp=seperate(temp,sep[j]);

            outFileTrain <<temp<<endl;
        }
        cout<<"Next\n";
    }
    
    for(int i=0;i<instancesTest;i++){
        
        for(int j=0;j<features;j++){
            inFileTest >>temp;
            
            if(j==0 || j==2 ||j==4 ||j==10 ||j==11 ||j==12)
                temp=seperate(temp,sep[j]);
            
            outFileTest << temp<<endl;
            }
    }


    
    
    
    return 0;
}
