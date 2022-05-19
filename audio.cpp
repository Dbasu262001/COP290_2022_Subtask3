#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include "weights.h"
#include<bits/stdc++.h>
#include<fstream>
#include<mkl/mkl.h>
using namespace std;
typedef struct{
    int label;
    float prob;
}pred_t;

extern pred_t* libaudioAPI(const char* audiofeatures, pred_t* pred);

float INPUT_ARRAY[250];

float IP1_WT_[] = IP1_WT;
float IP2_WT_[]=IP2_WT;
float IP3_WT_[]=IP3_WT;
float IP4_WT_[]=IP4_WT;

float IP1_BIAS_[]=IP1_BIAS;
float IP2_BIAS_[]=IP2_BIAS;
float IP3_BIAS_[]=IP3_BIAS;

float IP4_BIAS_[] = IP4_BIAS;


float OUTFC[12];



// Relu function 
// Definition: f(x) = 0 if x<0 else f(x) = x
void Relu(float arr[], int Length){
    for(int i=0;i<Length;i++){
        if(arr[i]<0.0){
            arr[i]=0.0;
        }
    }
    return;
}


// Softmax Probability function
// Definition f(x_i)= exp(x_i)/Σ exp(x_j) __  0<=j<=n, 0<=i<=n


vector<float> softmax(vector<float> &vec, int len, float *arr){
    vector<float> result;


    if(vec.empty() || len==0){
        return result;
    }
    float sum = 0.0;
    for(int i=0;i<len;i++){
        float temp =vec.at(i);
        sum=sum+exp(temp);

    }
     
    for(int i=0;i<len;i++){ // this for loop calculates the softmax values and store in result vector
        float temp =vec.at(i);
        temp=exp(temp)/sum;
        result.push_back(temp);
    }
   // SToring the values of softmax in an input array
    for(int i=0;i<len;i++){
        arr[i]=0.0;
        arr[i]=result.at(i);
    }
    return result;

}



//Function to create a Fullyconneted layer

void FC(float *IP,int IP_ROW,int IP_COL,  float *IP_WT,int IP_WT_ROW,int IP_Wt_COL,   float *IP_BIAS,int IP_BIAS_ROW,int IP_BIAS_COL,  float *OUT_FC,int OUT_FC_ROW,int OUT_FC_COL ){
   const CBLAS_LAYOUT order = CblasRowMajor;
   const CBLAS_TRANSPOSE transIP = CblasNoTrans;
   const CBLAS_TRANSPOSE transW = CblasNoTrans;
   cblas_sgemm(order, transIP, transW, IP_ROW, IP_Wt_COL, IP_COL, 1.0, IP, IP_COL, IP_WT, IP_Wt_COL,0.0,OUT_FC, IP_Wt_COL);

   for(int i=0;i<OUT_FC_ROW*OUT_FC_COL;i++){
       OUT_FC[i] = OUT_FC[i]+IP_BIAS[i];
   }
   cout<<endl;
 
    return;
}


// function implementing DNN infereence and the final softmax probability
void DNN_Infernce_S1(float *IP,float *IPA1_WT, float *IPA2_WT, float *IPA3_WT, float *IPA4_WT, float *IPA1_BIAS, float *IPA2_BIAS, float *IPA3_BIAS,float *IPA4_BIAS, float *OUT_FC){
    float OUT1_FC[144];
    float OUT2_FC[144];
    float OUT3_FC[144];
    FC(IP,1,250,IPA1_WT,250,144,IPA1_BIAS,1,144,OUT1_FC,1,144);
    Relu(OUT1_FC,144);

    FC(OUT1_FC,1,144,IPA2_WT,144,144,IPA2_BIAS,1,144,OUT2_FC,1,144);
    Relu(OUT2_FC,144);

    FC(OUT2_FC,1,144,IPA3_WT,144,144,IPA3_BIAS,1,144,OUT3_FC,1,144);
    Relu(OUT3_FC,144);

    FC(OUT3_FC,1,144,IPA4_WT,144,12,IPA4_BIAS,1,12,OUT_FC,1,12);
    vector<float> V;
    for(int i=0;i<12;i++){
        V.push_back(OUT_FC[i]);
    }
    softmax(V,12,OUT_FC);

    return;

}


//

int getMaxIndex(float * arr, int length ){
    float x = arr[0];
    int index=0;
    for(int i=1;i<length;i++){
        if(arr[i]>x){
            index=i;
            x=arr[i];
        }
    }
    return index;
}



// Function to process the audio library
pred_t* libaudioAPI(const char* filename, pred_t* pred){
    string Output_String_Array[]={"silence","unknown","yes","no","up","down","left","right","on","off","stop","go"};   
    
int Index =0;
float Num;
ifstream  Input_File(filename);
if(!Input_File.is_open()){
    cerr<<"Could not open the  Input file"<<endl<<"Please enter the name of your input file "<<endl;
}
while(Input_File>>Num){
    INPUT_ARRAY[Index]=Num;
    Index++;
}
Input_File.close(); 

DNN_Infernce_S1(INPUT_ARRAY,IP1_WT_,IP2_WT_,IP3_WT_,IP4_WT_,IP1_BIAS_,IP2_BIAS_,IP3_BIAS_,IP4_BIAS_,OUTFC);

int Max_index_1=getMaxIndex(OUTFC,12);
float Max_val_1= OUTFC[Max_index_1];
OUTFC[Max_index_1]= -1.0;


int Max_index_2=getMaxIndex(OUTFC,12);
float Max_val_2= OUTFC[Max_index_2];
OUTFC[Max_index_2]= -1.0;

int Max_index_3=getMaxIndex(OUTFC,12);
float Max_val_3= OUTFC[Max_index_3];
OUTFC[Max_index_3]= -1.0;
(pred+0)->prob=Max_val_1;
    (pred+0)->label=Max_index_1;

    (pred+1)->prob=Max_val_2;
    (pred+1)->label=Max_index_2;

    (pred+2)->prob=Max_val_3;
    (pred+2)->label=Max_index_3;


return pred;

}