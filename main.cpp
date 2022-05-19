#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include "weights.h"
#include<bits/stdc++.h>
#include<fstream>
#include<mkl/mkl.h>
#include "libaudioAPI.h"
using namespace std;

int main(int charc,char** argv){
  if(argv[1]==NULL){
    cout<<" Use the command line as :"<<endl<<"./yourcode.out ca4d5368_nohash_5.txt(i.e name of your input file in txt format) \n or ./yourcode.out ca4d5368_nohash_5.txt(i.e name of your input file in txt format) outputfile.txt(i.ename of your output file)"<<endl; 
  }
  string Output_String_Array[]={"silence","unknown","yes","no","up","down","left","right","on","off","stop","go"};   
  pred_t* pred;
  pred = new pred_t[3];
  libaudioAPI(argv[1],pred);
  int x,y,z;
  x=(pred+0)->label;
   y=(pred+1)->label;
   z=(pred+2)->label;
string St;
if(argv[2]==NULL){
    St= "output.txt";
    cout<<"Your expected output is stored in output.txt in the same directory of main.cpp file"<<endl;
}else{
  St = argv[2];
}

ofstream OUTFILE;
OUTFILE.open(St,ios_base::app);
OUTFILE<<argv[1]<<"  "<<Output_String_Array[x]<<" "<<Output_String_Array[y]<<" "<<Output_String_Array[z]<<" "<<(pred+0)->prob<<" "<<(pred+1)->prob<<" "<<(pred+2)->prob<<endl;
OUTFILE.close();
cout<<argv[1]<<"  "<<Output_String_Array[x]<<" "<<Output_String_Array[y]<<" "<<Output_String_Array[z]<<" "<<(pred+0)->prob<<" "<<(pred+1)->prob<<" "<<(pred+2)->prob<<endl;
return 0;
}