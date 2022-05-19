Steps for installing MKL library:

sudo apt-get update
sudo apt-get install intel-mkl-full

Steps to set path of shared library and  run:

$export LD_LIBRARY_PATH=./:$LD_LIBRARY_PATH
$./test.sh

output file is "outfile.txt"
Verify using outputfile.txt in mfcc_features  or softmax.csv **********

Link for the Project Description:   https://www.cse.iitd.ac.in/~rijurekha/cop290_2022.html



**********************
Functions used in the audio.cpp file:

Relu:
    for any float input x, f(x) = 0 if x<0 else f(x) = x.

Softmax:
    Calculates the probabilities distribution of the event over ‘n’ different events, distributions are stored in a array.
    f(x_i)= exp(x_i)/Σ exp(x_j) __  0<=j<=n, 0<=i<=n

FC: 
    Implements the fully connected layer for a input matrix A , a given weight matrix W and a bias Matrix B as A*W + B.

DNN_Inference:
    Implements the the Deep Neural Network(Inference)   as FC1 [250x144] -> RELU -> FC2 [144x144] -> RELU -> FC3 [144X144] -> RELU -> FC4 [144x12] -> softmax  i.e the final 
    output is the softmax probabilities distribution.

getMaxIndex:
    Outputs the index value of an array with maximum value from  the array with softmax probabilitiy distributions.

libAudioAPI:
    Takes the input file(EXTRACTED FEATURE OF AUDIO FILE IN from .txt file ) and outputs the pointer of  pred_t
    
    
    
// Assignment done by Dharmeswar Basumatary(2020CS50423) and Richa Yadav(2020CS50438)







 
