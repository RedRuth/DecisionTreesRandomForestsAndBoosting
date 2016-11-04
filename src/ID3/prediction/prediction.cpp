#include<iostream>
#include<fstream>
#include<string.h>
#include<queue>
#include<stdlib.h>

#define TEST_SIZE 16281
#define NUMBER_OF_FEATURES 14

using namespace std;
struct nodet{
    int NumOfChildren;
    int dec_feature;
    struct nodet *children[42];
    int label;
    
};
typedef struct nodet node;


typedef struct{
    int features[14];
    int label;
}Data;

Data *instances[TEST_SIZE];
node *root;


const int featureValues[14]= { 2, 9, 2, 17 ,2, 8, 15, 7, 6, 3, 2, 2, 2, 42 };

int predict(int i);

void createExample(int index,int features[],int Label){
    
    for(int i=0;i<14;i++)
        instances[index]->features[i]=features[i];
    
    instances[index]->label=Label;
}

node *createNode(int feat,int lab){
    node *temp=(node*)malloc(sizeof(node));
    
    if(feat!=-1)
        temp->NumOfChildren=featureValues[feat];
    else
        temp->NumOfChildren=0;
    
    temp->dec_feature=feat;
    
    temp->label=lab;
    
    for(int i=0;i<42;i++)
        temp->children[i]=NULL;
    
    return temp;
    
}


int main(int argc,char *argv[]){
    FILE *tree=fopen("../ID3OutputTree.txt","r");
    char *line;
    char *nodeValues;
    char *dec_feat;
    line=(char*)malloc(15000*sizeof(char));
    
    queue<node *> que;

    
    fgets(line,15000,tree);
    nodeValues=strtok(line,"\t");
    
    int feature,label;
    
    feature=int(nodeValues[0])-'0';
    label=int(nodeValues[strlen(nodeValues)-1])-'0';

    root=createNode(feature,label);
    

    que.push(root);
    int i=0;
    node *current;
    int a,b;

    while(fgets(line,15000,tree)){
        nodeValues=strtok(line,"\t");
        
        while(nodeValues[0]!='\n' && nodeValues[0]!=' ' && que.size()!=0){
            current=que.front();
            que.pop();

            
            for(int i=0;i<current->NumOfChildren;i++){
                
                sscanf(nodeValues,"%d:%d",&feature,&label);
                
                if(nodeValues[0]=='-'){
                    current->children[i]=createNode(-1,label);
                }
                else{
                    current->children[i]=createNode(feature,label);
                    que.push(current->children[i]);
                }
                
                nodeValues=strtok(NULL,"\t");
            }
        }
    }
    
    
    fstream testFile,testLabels;
    testFile.open("../../../Data/testDataDisc.txt");
    testLabels.open("../../../Data/testOutput.txt");
    int features[NUMBER_OF_FEATURES];
    
    //Create Data Matrix from Text File
    for(int i=0;i<TEST_SIZE;i++){
        instances[i]=(Data*)malloc(sizeof(Data));
        
        for(int j=0;j<NUMBER_OF_FEATURES;j++){
            testFile>> features[j];
        }
        testLabels>>label;
        createExample(i,features,label);
        
    }
testFile.close();
    int p,actual;
    float correct=0,wrong=0,total=0;
    
    for(int i=0;i<TEST_SIZE;i++){
        p=predict(i);
        testLabels>>actual;
        cout<<p<<endl;
        
        total++;
        if(p==actual)
            correct++;
        else
            wrong++;
    }
    float accuracy=correct/total;
    cout<<"Correctly Classified: "<<correct<<"\nIncorrectly Classified: "<<wrong<<"\nAccuracy: "<<accuracy<<"\nMisclassification error: "<<1-accuracy<<endl;
}


int predict(int i){
    node *current=root;
    int feat=root->dec_feature;
    
    while(feat>=0){
        
        if(instances[i]->features[feat] ==-1)
            break;
        else{
            current= current->children[instances[i]->features[feat]];
            feat=current->dec_feature;
        }
    }
    return current->label;
}
