#include <iostream>
#include <vector>
#include "maximumheap.cpp"
#include <string.h>
#include <fstream>
#include <random>



vector<long long> readFile(char* infile){
    vector<long long> sequence(100);
    ifstream inFile(infile);
    string line;
    for (int i = 0; i < 100; i++) {
        getline(inFile, line);
        sequence[i] = stol(line);
    }
    inFile.close();
    return sequence;
}

vector<long long> randInputSequence(){
    vector<long long> sequence(100);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long> distribution(1, pow(10, 12));
    for (int i = 0; i < 100; i++){
        long long random = distribution(gen);
        sequence[i] = random;
    }
    return sequence;
}

vector<long long> randSolutionSequence(){
    vector<long long> sequence(100);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribution(0, 1);
    for (int i = 0; i < 100; i++){
        int random = distribution(gen);
        if (random == 0){
            sequence[i] = 1;
        }
        else{
            sequence[i] = -1;
        }
    }
    return sequence;
}

long long residue(vector<long long> solution, vector<long long> sequence){
    long long residue = 0;
    for (int i = 0; i < 100; i++){
        residue += (solution[i] * sequence[i]);
    }

    residue = abs(residue);
    return residue;
}

vector<long long> generateNeighbor(vector<long long> sequence){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribution(0, 99);

    vector<long long> neighbor(100);
    for(int i = 0; i < 100; i++){
        neighbor[i] = sequence[i];
    }

    int i = distribution(gen);
    int j = i;
    while(j == i){
        j = distribution(gen);
    }

    int rand = distribution(gen);
    if((rand % 2) == 0){
        neighbor[i] -= (2 * neighbor[i]);
    }
    else{
        neighbor[i] -= (2 * neighbor[i]);
        neighbor[j] -= (2 * neighbor[j]);
    }
    return neighbor;
}


long long KaramkarKarp(vector<long long> sequence){

    MaxHeap H = *(new MaxHeap());

    for(int i = 0; i < sequence.size(); i++){
        H.insert(sequence[i]);
    }

    while(H.getSize() != 1){
        long long firstmax = H.delete_max();
        long long secondmax = H.delete_max();
        long long difference = firstmax - secondmax;
        H.insert(difference);
    }

    long long residue = H.get_max();
    return residue;
}

vector<long long> repeatedRandom(vector<long long> sequenceInput){
    vector<long long> tempSequence = randSolutionSequence();
    vector<long long> randSequence(100);
    long long res;
    long long tempres;
    long long finalres = 0;
    for(int i = 0; i < 25000; i++){
        randSequence = randSolutionSequence();
        res = residue(randSequence, sequenceInput);
        tempres = residue(tempSequence, sequenceInput);
        if (res < tempres) {
            finalres = res;
            tempSequence = randSequence;
        }
    }
    cout << finalres << "\n";
    return tempSequence;
}

vector<long long> hillClimbing(vector<long long> sequenceInput){
    vector<long long> tempSequence = randSolutionSequence();
    vector<long long> neighborSequence(100);
    long long res;
    long long tempres;
    long long finalres = 0;
    for(int i = 0; i < 25000; i++){
        neighborSequence = generateNeighbor(tempSequence);
        res = residue(neighborSequence, sequenceInput);
        tempres = residue(tempSequence, sequenceInput);
        if (res < tempres) {
            finalres = res;
            tempSequence = neighborSequence;
        }
    }
    cout << finalres << "\n";
    return tempSequence;
}

int main(int argc, char* argv[]) {

    int flag = atoi(argv[1]);
    if (flag == 0){
        vector<long long> input(100);
        input = randInputSequence();

        vector<long long> answer = repeatedRandom(input);
        for (int i = 0; i < 100; i++){
            cout << answer[i] << "\n";
        }

        long long kk = KaramkarKarp(input);
        cout << kk << "\n";
    }


    if (flag == 1){
        char* infile = argv[2];
        vector<long long> sequence(100);
        readFile(infile);
    }


    return 0;
}