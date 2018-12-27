//
// Created by Yaşar Selçuk Çalışkan on 27.12.2018.
//

#ifndef PROJECT5_MESSAGEDECODER_H
#define PROJECT5_MESSAGEDECODER_H

#include <string>
#include <list>
#include <queue>
#include <cmath>

using namespace std;

typedef pair<int, int> Edge;

struct edgeCompare {

    bool operator() (const Edge& a, const Edge& b){
        if(a.first == b.first){
            return a.second > b.second;
        }
        return a.first > b.first;
    }
};

class MessageDecoder {
    string message;
    int messageLength;
    long long int* options;
    list<int>* adj;
    void rabinKarp(string pat, string txt, list<int>* adj);
public:
    MessageDecoder(string message);
    void addWord(string word);
    long long int decode();
};


#endif //PROJECT5_MESSAGEDECODER_H
