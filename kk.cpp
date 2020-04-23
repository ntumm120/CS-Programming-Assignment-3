#include <iostream>
#include <vector>
#include "maximumheap.cpp"
#include <string.h>
#include <fstream>
#include <random>


int KaramkarKarp(vector<int> sequence){

    MaxHeap H = *(new MaxHeap());

    for(int i = 0; i < sequence.size(); i++){
        H.insert(sequence[i]);
    }

    while(H.getSize() != 1){
        int firstmax = H.delete_max();
        int secondmax = H.delete_max();
        int difference = firstmax - secondmax;
        H.insert(difference);
    }

    int residue = H.get_max();
    return residue;
}

void readFile(char* infile, vector<int> & sequence){

    ifstream inFile(infile);
    string line;
    for (int i = 0; i < 100; i++) {
        getline(inFile, line);
        sequence[i] = stoi(line);
    }
    inFile.close();
}

void randSequence(vector<int> & sequence){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribution(1, pow(10, 12));
    for (int i = 0; i < 100; i++){
        int random = distribution(gen);
        sequence.push_back(random);
    }
    return;
}

int main(int argc, char* argv[]) {

    int flag = atoi(argv[1]);
    if (flag == 0){
        vector<int> sequence(100);
        randSequence(sequence);
        for (int i = 0; i < sequence.size(); i++){
            cout << sequence[i] << "\n";
        }

    }

    if (flag == 1){
        char* infile = argv[2];
        vector<int> sequence(100);
        readFile(infile, sequence);
    }



    return 0;
}
