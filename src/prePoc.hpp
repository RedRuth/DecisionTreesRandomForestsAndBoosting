#ifndef PREPROC_H
#define PREPROC_H

#define INSTANCES 32561
#define GREATER_THAN_50 1
#define LESS_THAN_50 0

#include<string>
#include<iostream>
#include<fstream>

#include "FeatureEnumerations.h"
using namespace std;

class DataCleaner{
    
public:
    int   featureMatrix[32561][14];
    bool  outputVector[32561];
    
    DataCleaner(char filePath[]);
    
};

#endif