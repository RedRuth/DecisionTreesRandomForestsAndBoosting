#include "id3.cpp"
#include<fstream>
#include<queue>


int main(int argc,char *argv[]){
    char *pathDataTrain= "../../Data/trainDataDisc.txt";
    char *pathLabelTrain="../../Data/trainOutput.txt";

    
    int NumberOfInstances=32561;
    int NumberOfFeatures=14;
    DecisionTree dt= DecisionTree(pathDataTrain,pathLabelTrain,NumberOfInstances,NumberOfFeatures);
    node *root= dt.root;
    //cout<<root->dec_feature<<endl;
    
    int save=0;
    
    queue<node *> que;
    queue<int> saveChecker;
    que.push(root);
    saveChecker.push(0);
    
    while(que.size() !=0){
        
        node *temp=que.front();
        que.pop();
        int saveC=saveChecker.front();
        saveChecker.pop();
        if(saveC!=save){
            cout<<endl;
            save=saveC;
        }
        cout<<temp->dec_feature<<":"<<temp->labelPredict<<"\t";
        
        if(temp->dec_feature!=-2){
            for(int i=0;i<featureValues[temp->dec_feature];i++){
                que.push(temp->children[i]);
                saveChecker.push(save+1);
            }
        }
        
        
    }
    
    return 0;
}