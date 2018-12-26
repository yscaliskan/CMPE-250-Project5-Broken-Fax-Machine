//
// Created by Yaşar Selçuk Çalışkan on 23.12.2018.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <iterator>
#include <list>
#include <queue>

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

void rabinKarp(string pat, string txt, list<int>* adj)
{
    int q = 101;
    int M = pat.length();
    int N = txt.length();
    int i, j;
    long long int p = 0; // hash value for pattern
    long long int t = 0; // hash value for txt
    int h = 1;

    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M-1; i++)
        h = (h*256)%q;

    // Calculate the hash value of pattern and first
    // window of text
    for (i = 0; i < M; i++)
    {
        p = (256*p + pat[i])%q;
        t = (256*t + txt[i])%q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++)
    {

        // Check the hash values of current window of text
        // and pattern. If the hash values match then only
        // check for characters on by one
        if ( p == t )
        {
            /* Check for characters one by one */
            for (j = 0; j < M; j++)
            {
                if (txt[i+j] != pat[j])
                    break;
            }

            // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
            if (j == M)
                adj[i].emplace_back(i + pat.length());
        }

        // Calculate hash value for next window of text: Remove
        // leading digit, add trailing digit
        if ( i < N-M )
        {
            t = (256*(t - txt[i]*h) + txt[i+M])%q;

            // We might get negative value of t, converting it
            // to positive
            if (t < 0)
                t = (t + q);
        }
    }
}

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
    int messageLength = message.length();
    list<int>* adj = new list<int>[messageLength + 1];
    for (int i = 0; i < numWords; ++i){
        string word;
        infile >> word;
        rabinKarp(word, message, adj);
    }
    auto* options = new long long int[messageLength + 1];
    for (int i = 0; i <= messageLength; ++i){
        options[i] = (long long int) 0;
    }
    priority_queue<Edge, vector<Edge>, edgeCompare> pq;
    for (list<int>::iterator it = adj[0].begin(); it != adj[0].end(); ++it){
        pq.push(make_pair(0, (*it)));
    }
    while(!pq.empty()){
        Edge currentEdge = pq.top();
        pq.pop();
        if(currentEdge.second != messageLength && options[currentEdge.second] == 0){
            for (list<int>::iterator it = adj[currentEdge.second].begin(); it != adj[currentEdge.second].end(); ++it){
                pq.push(make_pair(currentEdge.second, (*it)));
            }
        }
        if(currentEdge.first == 0){
            options[currentEdge.second] = (long long int) 1;
        }
        else{
            options[currentEdge.second] = ((options[currentEdge.first] % ((long long int) pow(10, 9) + 7))
                    + (options[currentEdge.second] % ((long long int) pow(10, 9) + 7))) % ((long long int) pow(10, 9) + 7);
        }
    }
    ofstream myfile;
    myfile.open(argv[2]);
    myfile << options[message.length()] << endl;
    return 0;
}

