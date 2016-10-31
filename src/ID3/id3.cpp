#ifndef ID3_H
#define ID3_H

#include<string>
#include<iostream>
#include<fstream>
#include"../FeatureEnumerations.h"
#include<math.h>


using namespace std;

typedef struct{
    int age;
    enum workClass wc;
    int fnlwgt;
    enum education edu;
    int eudcationNum;
    enum maritalStatus marSta;
    enum occupation occ;
    enum relationship rel;
    enum race rce;
    enum sex s;
    int capitalGain;
    int capitalLoss;
    int hoursPerWeek;
    enum nativeCountry natCou;
    int label;
}trainingExamples;

trainingExamples *Data[32561];

void createExample(trainingExamples *te,int features[],int outputLabel);
float createSet(char *pathData,char *pathLabel,int NumberOfInstances,int NumberOfFeatures);

void createExample(trainingExamples *te,int features[],int outputLabel){
    te->age=features[0];
    te->wc=workClass(features[1]);
    te->fnlwgt=features[2];
    te->edu=education(features[3]);
    te->eudcationNum=features[4];
    te->marSta=maritalStatus(features[5]);
    te->occ=occupation(features[6]);
    te->rel=relationship(features[7]);
    te->rce=race(features[8]);
    te->s=sex(features[9]);
    te->capitalGain=features[10];
    te->capitalLoss=features[11];
    te->hoursPerWeek=features[12];
    te->natCou=nativeCountry(features[13]);
    te->label=outputLabel;
}

float createSet(char *pathData,char *pathLabel,int NumberOfInstances,int NumberOfFeatures){
    fstream dataFile;
    fstream labelFile;
    
    dataFile.open(pathData);
    labelFile.open(pathLabel);
    
    
    int features[NumberOfFeatures];
    int label;
    float lessCount=0,greaterCount=0;
    float total=NumberOfInstances;
    
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
    }
    float entropy;
    cout<<lessCount<<" "<<greaterCount<<endl;
    lessCount=(lessCount/total);
    greaterCount=(greaterCount/total);
    entropy=-1*((lessCount*log(lessCount))+(greaterCount*log(greaterCount)));
    return entropy;
}

#endif