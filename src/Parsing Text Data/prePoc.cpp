#include "prePoc.hpp"
#define AGE 0
#define WORKCLASS 1
#define FNLWGT 2
#define EDUCATION 3
#define EDUCATION_NUM 4
#define MARITAL_STATUS 5
#define OCCUPATION 6
#define RELATIONSHIP 7
#define RACE 8
#define SEX 9
#define CAPITAL_GAIN 10
#define CAPITAL_LOSS 11
#define HOURS_PER_WEEK 12
#define NATIVE_COUNTRY 13

DataCleaner::DataCleaner(char filePath[],int examples){
    this->instances=examples;
    FILE *inputFile=fopen(filePath,"r");
    
    char trainingExample[200];
    char *tok;
    int counter=0;
    
    while(fgets(trainingExample,200,inputFile)){
        if(counter==instances)
            break;
        int len=strlen(trainingExample);
        
        
        if(trainingExample[len-6]=='>')
            outputVector[counter]=1;
         else
             outputVector[counter]=0;

       
        tok=strtok(trainingExample,",");
        featureMatrix[counter][AGE]=atoi(tok);
        
        tok=strtok(NULL,",");
        featureMatrix[counter][WORKCLASS]=giveWorkClass(tok);
        
        tok=strtok(NULL,",");
        featureMatrix[counter][FNLWGT]=atoi(tok);

        
        tok=strtok(NULL,",");
        featureMatrix[counter][EDUCATION]=giveEducation(tok);
        
        tok=strtok(NULL,",");
        featureMatrix[counter][EDUCATION_NUM]=atoi(tok);
        
        tok=strtok(NULL,",");
        featureMatrix[counter][MARITAL_STATUS]=giveMaritalStatus(tok);

        
        tok=strtok(NULL,",");
        featureMatrix[counter][OCCUPATION]=giveOccupation(tok);
        
        
        tok=strtok(NULL,",");
        featureMatrix[counter][RELATIONSHIP]=giveRelationship(tok);

        
        tok=strtok(NULL,",");
        featureMatrix[counter][RACE]=giveRace(tok);

        
        tok=strtok(NULL,",");
        featureMatrix[counter][SEX]=giveSex(tok);

        
        tok=strtok(NULL,",");
        featureMatrix[counter][CAPITAL_GAIN]=atoi(tok);

        
        tok=strtok(NULL,",");
        featureMatrix[counter][CAPITAL_LOSS]=atoi(tok);

        
        tok=strtok(NULL,",");
        featureMatrix[counter][HOURS_PER_WEEK]=atoi(tok);
        
        tok=strtok(NULL,",");
        featureMatrix[counter][NATIVE_COUNTRY]=giveNativeCountry(tok);
        
        
        
       
        
        counter++;
    }
}



int DataCleaner::giveWorkClass(char token[]){
    
    if(strcmp(token," Private")==0)
        return workClass(PRIVATE);
    else if(strcmp(token," Self-emp-not-inc")==0)
        return workClass(SELF_EMPLOYED_NOT_INCLUDED);
    else if(strcmp(token," Self-emp-inc")==0)
        return workClass(SELF_EMPLOYED_INC);
    else if(strcmp(token," Federal-gov")==0)
        return workClass(FEDERAL_GOV);
    else if(strcmp(token," Local-gov")==0)
        return workClass(LOCAL_GOV);
    else if(strcmp(token," State-gov")==0)
        return workClass(STATE_GOV);
    else if(strcmp(token," Without-pay")==0)
        return workClass(WITHOUT_PAY);
    else if(strcmp(token," Never-worked")==0)
        return workClass(NEVER_WORKED);
    else
        return workClass(UNKNOWNWC);
    
}

int DataCleaner::giveEducation(char token[]){
    if(strcmp(token," Bachelors")==0)
       return education( BACHELORS);
    else if(strcmp(token," Some-college")==0)
       return education( SOME_COLLEGE);
    else if(strcmp(token," 11th")==0)
        return education( ELEVENTH);
    else if(strcmp(token," HS-grad")==0)
        return education(HS_GRAD);
    else if(strcmp(token," Prof-school")==0)
        return education(PROF_SCHOOL);
    else if(strcmp(token," Assoc-acdm")==0)
        return education(ASSOC_ACDM);
    else if(strcmp(token," Assoc-voc")==0)
        return education(ASSOC_VOC);
    else if(strcmp(token," 9th")==0)
        return education(NINTH);
    else if(strcmp(token," 7th-8th")==0)
        return education(SEVENTH_EIGHTH);
    else if(strcmp(token," 12th")==0)
        return education(TWELFTH);
    else if(strcmp(token," Masters")==0)
        return education(MASTERS);
    else if(strcmp(token," 1st-4th")==0)
        return education(FIRST_FOURTH);
    else if(strcmp(token," 10th")==0)
        return education(TENTH);
    else if(strcmp(token," Doctorate")==0)
        return education(DOCTORATE);
    else if(strcmp(token," 5th-6th")==0)
        return education(FIFTH_SIXTH);
    else if(strcmp(token," Preschool")==0)
        return education(PRESCHOOL);
    else
        return education(UNKNOWNEDU);

        
}

int DataCleaner::giveMaritalStatus(char token[]){
    
    if(strcmp(token," Married-civ-spouse")==0)
        return maritalStatus(MARRIED_CIV_SPOUSE);
    else if(strcmp(token," Divorced")==0)
        return maritalStatus(DIVORCED);
    else if(strcmp(token," Never-married")==0)
        return maritalStatus(NEVER_MARRIED);
    else if(strcmp(token," Seperated")==0)
        return maritalStatus(SEPARATED);
    else if(strcmp(token," Widowed")==0)
        return maritalStatus(WIDOWED);
    else if(strcmp(token," Married-spouse-absent")==0)
        return maritalStatus(MARRIED_SPOUSE_ABSENT);
    else if(strcmp(token," Married-AF-spouse")==0)
        return maritalStatus(MARRIED_AF_SPOUSE);
    else
        return maritalStatus(UNKNOWNMS);
}

int DataCleaner::giveOccupation(char token[]){
    if(strcmp(token," Tech-support")==0)
        return occupation(TECH_SUPPORT);
    else if(strcmp(token," Craft-repair")==0)
        return occupation(CRAFT_REPAIR);
    else if(strcmp(token," Other-service")==0)
        return occupation(OTHER_SERVICE);
    else if(strcmp(token," Sales")==0)
        return occupation(SALES);
    else if(strcmp(token," Exec-managerial")==0)
        return occupation(EXEC_MANAGERIAL);
    else if(strcmp(token," Prof-specialty")==0)
        return occupation(PROF_SPECIALTY);
    else if(strcmp(token," Handlers-cleaners")==0)
        return occupation(HANDLER_CLEANERS);
    else if(strcmp(token," Machine-op-inspct")==0)
        return occupation(MACHINE_OP_INSPCT);
    else if(strcmp(token," Adm-clerical")==0)
        return occupation(ADM_CLERICAL);
    else if(strcmp(token," Farming-fishing")==0)
            return occupation(FARMING_FISHING);
    else if(strcmp(token," Transport-moving")==0)
            return occupation(TRANSPORT_MOVING);
    else if(strcmp(token," Priv-house-serv")==0)
            return occupation(PRIVATE_HOUSE_SERVICE);
    else if(strcmp(token," Protective-serv")==0)
            return occupation(PROTECTIVE_SERVICES);
    else if(strcmp(token," Armed-Forces")==0)
            return occupation(ARMED_FORCES);
    else
            return occupation(UNKNOWNO);
    
}

int DataCleaner::giveRelationship(char token[]){
    if(strcmp(token," Wife")==0)
        return relationship(WIFE);
        
    else if(strcmp(token," Own-child")==0)
        return relationship(OWN_CHILD);
        
    else if(strcmp(token," Husband")==0)
        return relationship(OWN_CHILD);
        
    else if(strcmp(token," Other-relative")==0)
        return relationship(OWN_CHILD);

    else if(strcmp(token," Not-in-family")==0)
        return relationship(OWN_CHILD);
    
    else if(strcmp(token," Unmarried")==0)
        return relationship(OWN_CHILD);
        
    else
            return relationship(UNKNOWNREL);
}

int DataCleaner::giveRace(char token[]){
    if(strcmp(token," White")==0)
        return race(WHITE);
    else if(strcmp(token," Asian-Pac-Islander")==0)
        return race(ASIAN_PAC_ISLANDER);
    else if(strcmp(token," Amer-Indian-Eskimo")==0)
        return race(AMER_INDIAN_ESKIMO);
    else if(strcmp(token," Other")==0)
        return race(OTHER);
    else if(strcmp(token," Black")==0)
        return race(BLACK);
    else
        return race(UNKNOWNRACE);
}

int DataCleaner::giveSex(char token[]){
    if(strcmp(token," Female")==0)
        return sex(FEMALE);
    else if(strcmp(token," Male")==0)
        return sex(MALE);
    else
        return sex(UNKNOWNSEX);
}

int DataCleaner::giveNativeCountry(char token[]){

    char labels[] =" United-States, Cambodia, England, Puerto-Rico, Canada, Germany, Outlying-US(Guam-USVI-etc), India, Japan, Greece, South, China, Cuba, Iran, Honduras, Philippines, Italy, Poland, Jamaica, Vietnam, Mexico, Portugal, Ireland, France, Dominican-Republic, Laos, Ecuador, Taiwan, Haiti, Columbia, Hungary, Guatemala, Nicaragua, Scotland, Thailand, Yugoslavia, El-Salvador, Trinadad&Tobago, Peru, Hong, Holand-Netherlands";
    char *label;
    
    int counter=0;
    label=strtok(labels,",");
    while(label){
        
        if(strcmp(token,label)==0){
            return counter;
        }
        
        label=strtok(NULL,",");
        counter++;
    }
    return -1;
    
}
