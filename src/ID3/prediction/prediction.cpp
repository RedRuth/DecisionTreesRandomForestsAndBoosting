#include<iostream>
#include<fstream>
#include<string.h>
#include<queue>
#include<stdlib.h>
using namespace std;
struct node{
    int NumOfChildren;
    int dec_feature;
    struct node *children[42];
    int label;
    
};

const int featureValues[14]= { 2, 9, 2, 17 ,2, 8, 15, 7, 6, 3, 2, 2, 2, 42 };


node *createNode(int feat,int lab){
    node *temp=(node*)malloc(sizeof(node));
    temp->NumOfChildren=featureValues[feat];
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
    char *dec_feat,*label;
    line=(char*)malloc(15000*sizeof(char));
    
    queue<node *> que;
    node *root;

    
    fgets(line,15000,tree);
    nodeValues=strtok(line,"\t");
    
    char feature,label;
    feature=nodeValues[0];
    label=nodeValues[strlen(nodeValues)-1];
    root=createNode(atoi(feature),atoi(label));

    que.push(root);
    
    while(fgets(line,15000,tree)){
        nodeValues=strtok(line,"\t");
        while(nodeValues!=NULL)
            nodeValues=strtok(NULL,"\t");
        
        
    }
    
}