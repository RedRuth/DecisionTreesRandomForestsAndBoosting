#ifndef ID3_H
#define ID3_H

#include<string>
#include<iostream>
#include<fstream>
#include"../FeatureEnumerations.h"
#include<math.h>


using namespace std;

typedef struct{
    int features[14];
    int label;
}trainingExamples;


struct nodet{
    int *indices;
    float entropy;
    struct nodet *children[42];
    int dec_index; //Feature Index on whic decision is to be made
    int setSize;
    int labelPredict;
};

typedef struct nodet node;

class DecisionTree{
    
    
    
    trainingExamples *Data[32561];
    
    void createExample(trainingExamples *te,int features[],int outputLabel){
        
        for(int i=0;i<14;i++)
            te->features[i]=features[i];
        te->label=outputLabel;
    }

    node *createNode(int *dataIndices,float entropy,int setSize,int labelPredict){
        node *temp=(node*)malloc(sizeof(node));
        
        temp->entropy=entropy;
        temp->indices=dataIndices;
        temp->dec_index=-2; //Unassigned -2
        temp->setSize=setSize;
        int dec_value=-2;
        for(int i=0;i<42;i++)
            temp->children[i]=NULL;
        temp->labelPredict=labelPredict;
        return temp;
    }
public:
    node *root=NULL;

    
    DecisionTree(char *pathData,char *pathLabel,int NumberOfInstances,int NumberOfFeatures){
       
        fstream dataFile;
        fstream labelFile;
        
        dataFile.open(pathData);
        labelFile.open(pathLabel);
        
        
        int features[NumberOfFeatures];
        int label;
        float lessCount=0,greaterCount=0;
        float total=NumberOfInstances;
        int *indices=(int*)malloc(32561*sizeof(int));
        
        
        for(int i=0;i<NumberOfInstances;i++){
            Data[i]=(trainingExamples*)malloc(sizeof(trainingExamples));
            for(int j=0;j<NumberOfFeatures;j++)
                dataFile >> features[j];
            labelFile >> label;
            if(label==0)
                lessCount++;
            else
                greaterCount++;
            createExample(Data[i],features,label);
            indices[i]=i;
        }
        dataFile.close();
        labelFile.close();
        lessCount=(lessCount/total);
        greaterCount=(greaterCount/total);
        
        float entropy;
        entropy=-1*((lessCount*log(lessCount))+(greaterCount*log(greaterCount)));
        
        root=createNode(indices,entropy,32561,-1);
        
    }
};

#endif