#ifndef PREPROC_H
#define PREPROC_H

#define INSTANCES 32561
#define GREATER_THAN_50 1
#define LESS_THAN_50 0

#include<string>
#include<iostream>
#include<fstream>

#include "../FeatureEnumerations.h"
using namespace std;

class DataCleaner{
private:
    int instances;
    int valueToSet;
    int findLabel(char labels[],char token[]);
    int giveWorkClass(char token[]);
    int giveEducation(char token[]);
    int giveMaritalStatus(char token[]);
    int giveOccupation(char token[]);
    int giveRelationship(char token[]);
    int giveRace(char token[]);
    int giveSex(char token[]);
    int giveNativeCountry(char token[]);
public:
    int   featureMatrix[32561][14];
    bool  outputVector[32561];
    
    DataCleaner(char filePath[],int examples);
    
};

#endif