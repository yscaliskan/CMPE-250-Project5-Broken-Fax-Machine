//
// Created by Yaşar Selçuk Çalışkan on 23.12.2018.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <iterator>
#include <list>
#include <queue>
#include "MessageDecoder.h"

using namespace std;

int main(int argc, char* argv[]){
    ios_base::sync_with_stdio(false);
    if(argc != 3){
        cout << "Run the code with the following command: ./project3 [input_file] [output_file]" << endl;
        return 1;
    }
    string message;
    int numWords;
    ifstream infile(argv[1]);
    infile >> message;
    infile >> numWords;
    MessageDecoder messageDecoder(message);
    for (int i = 0; i < numWords; ++i){
        string word;
        infile >> word;
        messageDecoder.addWord(word);
    }
    ofstream myfile;
    myfile.open(argv[2]);
    long long int result = messageDecoder.decode();
    myfile << result << endl;
    return 0;
}

