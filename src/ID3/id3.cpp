#ifndef ID3_H
#define ID3_H

#include<string>
#include<iostream>
#include<fstream>
#include"../FeatureEnumerations.h"
#include<math.h>
#include<list>
#include<vector>
using namespace std;

typedef struct{
    int features[14];
    int label;
}trainingExamples;


struct nodet{
    list<int> *indices;
    list<int> *used;
    float entropy;
    struct nodet *children[42];
    int dec_feature; //Feature Index on whic decision is to be made
    int setSize;
    int labelPredict;
};


typedef struct{
    float class0; //!instances with label=2;
    float class1; //! instance with label=1
    float total; //! Total instances in Set
}set;

list<int> attribs;
class Feature{
    
    
public:
    set *classes;
    float total;
    int NumberOfAttributes;
    
    Feature(int AttributeNumber){
        
        classes=(set*)malloc(AttributeNumber*sizeof(set));
        
        this->NumberOfAttributes= AttributeNumber;
        
        for(int i=0;i<NumberOfAttributes;i++){
            classes[i].class0=0;
            classes[i].class1=0;
            classes[i].total=0;
        }
        total=0;
        
    }
};


typedef struct nodet node;
 const int featureValues[14]= { 2, 9, 2, 17 ,2, 8, 15, 7, 6, 3, 2, 2, 2, 42 };

class DecisionTree{
    
    int featureMask[14];
    
    trainingExamples *Data[32561];
    
    void createExample(int index,int features[],int outputLabel){
        
        for(int i=0;i<14;i++)
            Data[index]->features[i]=features[i];
       
        Data[index]->label=outputLabel;
    }

    float GiveEntropy(set S1){
        
        // cout<<S1.class0<<" "<<S1.class1<<" "<<S1.total<<endl;
        float p0=(S1.class0/S1.total);
        float p1=(S1.class1/S1.total);
        
        float ent= -1* (p0*log(p0) + p1*log(p1));
        if(isnan(ent))
            ent=0;
        return ent;
    }

    node *createNode(list<int> dataIndices,float entropy,int setSize,int labelPredict,list<int> usedP){
       
        node *temp=(node*)malloc(sizeof(node));

        temp->entropy=entropy;
        temp->indices= new list<int>(dataIndices.begin(),dataIndices.end());
        temp->used=new list<int>(usedP.begin(),usedP.end());
        
        temp->dec_feature=-2; //Unassigned -2
        temp->setSize=setSize;
        int dec_value=-2;
        for(int i=0;i<42;i++)
            temp->children[i]=NULL;
        temp->labelPredict=labelPredict;

        return temp;
    }
    

    float InformationGain(int j,list<int> *instances,int examples,float entropy){

        Feature f(featureValues[j]);
        float terms[f.NumberOfAttributes];
        int totals[f.NumberOfAttributes];
        for(int i=0;i< f.NumberOfAttributes ;i++)
            totals[i]=0;
        
        int mc, mcV=0;
        for(int instance:*instances){
            int value=Data[instance]->features[j];
            if(value!=-1)
                totals[value]++;
        }
        for(int i=0;i<f.NumberOfAttributes;i++){
            if(totals[i]>mcV){
                mcV=totals[i];
                mc=i;
            }
        }
        
        
        for(int instance : *instances){
            int value=Data[instance]->features[j];
            int label=Data[instance]->label;
            if(value != -1){
                f.total++;
                f.classes[value].total++;
                if(label==0)
                    f.classes[value].class0++;
                else
                    f.classes[value].class1++;
            }
            else{
                f.total++;
                f.classes[mc].total++;
                if(label==0)
                    f.classes[mc].class0++;
                else
                    f.classes[mc].class1++;
                
            }
        }
        float IG=entropy;
        
        for(int i=0;i<f.NumberOfAttributes;i++){
            terms[i]=(f.classes[i].total/f.total)*GiveEntropy(f.classes[i]);
            if(isnan(terms[i]))
                terms[i]=0;
            IG-=terms[i];
        }

        
        return IG;
    }

    int maxIG(float entropy,list<int> *instances,int examples,list<int> *used){
        
        int feat=-1;
        float maxIG= -1;
        float IGs;
        int *featureMask;
        
        featureMask=(int *)malloc(14*sizeof(int));
        
        for(int instance: *used){
            featureMask[instance]= -1;
            cout<<endl;
        }
        
        for(int j=0;j<14 ;j++){
            if(featureMask[j]!=-1){
            IGs=InformationGain(j,instances,examples,entropy);
               // cout<<"IGS is: "<<IGs<< endl;
            
            if(IGs > maxIG){
                maxIG=IGs;
                feat=j;
            }
            }
        }
        
        //cout<<maxIG<<" "<<feat<<endl;
        if(maxIG==0)
            return -1;
        return feat;
    }

    
    void CreateTree(node *NODE){
        list<int> *instances=NODE->indices;
        list<int> featUsed= *(NODE->used);

        int zeros=0,ones=0;
        
        for(int instance:* instances){
            int label=Data[instance]->label;
            if(label==0)
                zeros++;
            else
                ones++;
        }
        
        int mostCommonLabel;
        
        if(zeros>ones)
            mostCommonLabel=0;
        else
            mostCommonLabel=1;
        
        NODE->labelPredict=mostCommonLabel;

        
        if(featUsed.size() ==14){
           // cout<<"Predicted "<<mostCommonLabel<<" for path due to lack of attributess: ";
            //for(int instance : featUsed)
              //  cout<<instance<<"--->";
            //cout<<endl;
            NODE->dec_feature=-2;
            return;
            
        }
        
        int seperateFeat=maxIG(NODE->entropy,NODE->indices,NODE->setSize,NODE->used);
        
        if(seperateFeat==-1){
            //cout<<"Predicted "<<mostCommonLabel<<" for path due to lack of further IG: ";
            //for(int instance : featUsed)
              //  cout<<instance<<"--->";
            //cout<<endl;
            NODE->dec_feature=-2;
            return;
        }
        
        NODE->dec_feature=seperateFeat;
        
        
        featUsed.push_back(seperateFeat);
        
        const int NumberOfAttribs=featureValues[seperateFeat];
        
        
        
        set base[NumberOfAttribs];
        
        for(int i=0;i<NumberOfAttribs;i++){
            base[i].total=0;
            base[i].class0=0;
            base[i].class1=0;
        }
        
        float entropy[NumberOfAttribs];
        int counter[NumberOfAttribs];
        
        vector<list<int> > indices(NumberOfAttribs,list<int>(0));
        
        list<int> lis;
        
        for(int i=0;i<NumberOfAttribs;i++){
            counter[i]=0;
        }
        
        list<int> missing;
        
        for(int instance: *instances){
            
            int Value=Data[instance]->features[seperateFeat];
            int label=Data[instance]->label;
            if(Value!=-1){
                base[Value].total++;
                indices[Value].push_back(instance);
                
                if(label==0)
                    base[Value].class0++;
                else
                    base[Value].class1++;
            }
            else
                missing.push_back(instance);
        }
        int mostCommon=-1;
        int most=0;
        for(int i=0;i<NumberOfAttribs;i++){
            if(base[i].total > most){
                mostCommon=i;
                most=base[i].total;
            }
        }
        for(int missingIndex : missing){
            
            int label=Data[missingIndex]->label;
            
            base[mostCommon].total++;
            if(label==0)
                base[mostCommon].class0++;
            else
                base[mostCommon].class1++;
            indices[mostCommon].push_back(missingIndex);
        }
       // cout<<"FOR THE "<<seperateFeat<<"\n";
        
        for(int i=0;i<NumberOfAttribs;i++){
            entropy[i]=GiveEntropy(base[i]);
            
            if(isnan(entropy[i]))
                entropy[i]=0;
            
            NODE->children[i]=createNode(indices[i],entropy[i],base[i].total,-1,featUsed);
            
            //cout<<"Value: "<<i<<" Entropy: "<<entropy[i]<<" Total: "<<base[i].total<<" Label 0: "<<base[i].class0<<" Label 1: "<<base[i].class1<<endl;
            
        }

        for(int i=0;i<NumberOfAttribs;i++){
            
            if(base[i].total!=0){
                if(base[i].class0==0){
                 //   cout<<"Predicted 1 for path : ";
                   // for(int instance : featUsed)
                     //   cout<<instance<<"--->";
                    //cout<<endl;
                    NODE->children[i]->labelPredict=1;
                    NODE->children[i]->dec_feature=-2;


                    
                }else if(base[i].class1==0){
               //     cout<<"Predicted 0 for path : ";
                 //   for(int instance : featUsed)
                   //     cout<<instance<<"--->";
                    //cout<<endl;
                    NODE->children[i]->dec_feature=-2;
                    NODE->children[i]->labelPredict=0;

                    
                }else{
                
                    CreateTree(NODE->children[i]);
                }
                
                
            }
            else{
             //   cout<<"Predicted "<<mostCommonLabel<<" for path due to lack of examples: ";
               // for(int instance : featUsed)
                 //   cout<<instance<<"--->";
                //cout<<endl;
                NODE->children[i]->dec_feature=-2;
                NODE->children[i]->labelPredict=mostCommonLabel;
            }
        }
        
        
        
        
    }
    
public:
    node *root=NULL;

    
    DecisionTree(char *pathData,char *pathLabel,int NumberOfInstances,int NumberOfFeatures){
       
        fstream dataFile;
        fstream labelFile;
        
        dataFile.open(pathData);
        labelFile.open(pathLabel);
        
        for(int i=0;i<14;i++)
            featureMask[i]=0;
        
        int features[NumberOfFeatures];
        int label;
        
        set base;
        base.total=NumberOfInstances;
        
        list<int>indices;
        
        
        for(int i=0;i<NumberOfInstances;i++){
            
            Data[i]=(trainingExamples*)malloc(sizeof(trainingExamples));
            
            for(int j=0;j<NumberOfFeatures;j++){
                dataFile >> features[j];
                //cout<<features[j]<<endl;
            }
            labelFile >> label;
            
            if(label==0)
                base.class0++;
            else
                base.class1++;
            
            createExample(i,features,label);
            indices.push_back(i);
        }
        
        dataFile.close();
        labelFile.close();
        
        float Entropy=GiveEntropy(base);
    
        list<int> used;
        root=createNode(indices,Entropy,32561,-1,used);

        CreateTree(root);
        
    }
    
    
    
    
};

#endif