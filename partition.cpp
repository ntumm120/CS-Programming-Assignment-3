#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <random>
#include <cmath>

using namespace std;

class MaxHeap {
    private:
        vector<long long> heap;
        long long p(long long i);
        long long r(long long i);
        long long l(long long i);

    public:
        void shiftDown(long long i);
        void shiftUp(long long i);
        void insert(long long key);
        long long get_max();
        long long delete_max();
        long long getSize();
};

long long MaxHeap::p(long long i) {
    return (i - 1) / 2;
}

long long MaxHeap::r(long long i) {
    return (2 * i + 2);
}

long long MaxHeap::l(long long i) {
    return (2 * i + 1);
}

long long MaxHeap::getSize() {
    return heap.size();
}

void MaxHeap::insert(long long val) {
    heap.push_back(val);
    long long index = heap.size() - 1;
    shiftUp(index);
}

long long MaxHeap::get_max() {
    return heap[0];
}

long long MaxHeap::delete_max() {
    long long max = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    shiftDown(0);
    return max;

}

void MaxHeap::shiftDown(long long i) {
    long long left = l(i);
    long long right = r(i);

    long long largest = i;

    if (left < heap.size() && heap[left] > heap[i])
        largest = left;

    if (right < heap.size() && heap[right] > heap[largest])
        largest = right;

    if (largest != i) {
        swap(heap[i], heap[largest]);
        shiftDown(largest);
    }
}

void MaxHeap::shiftUp(long long i) {

    if (i && heap[p(i)] < heap[i]) {
        swap(heap[i], heap[p(i)]);
        shiftUp(p(i));
    }
}


// ALGOS RELATED CODE BELOW


default_random_engine gen;
uniform_real_distribution<double> distribution(0.0,1.0);

double generateRandomReal() {
    return distribution(gen);
}

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
        else {
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

vector<int> randPartition() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribution(0, 99);

    vector<int> partition(100);
    for (int i = 0; i < 100; i++) {
        partition[i] = distribution(gen);
    }
    return partition;
}

vector<int> generatePartitionNeighbor(vector<int> partition) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribution(0, 99);

    vector<int> neighbor(100);
    for(int i = 0; i < 100; i++){
        neighbor[i] = partition[i];
    }

    int i = distribution(gen);
    int j = distribution(gen);
    while (partition[i] == j) {
        j = distribution(gen);
    }
    neighbor[i] = j;
    return neighbor;
}

vector<long long> partitionToSequence(vector <long long> sequence, vector<int> partition) {
    vector <long long> newSequence(100);
    for (int i = 0; i < 100; i++) {
        newSequence[i] = 0;
    }
    for (int i = 0; i < 100; i++) {
        newSequence[partition[i]] += sequence[i];
    }
    return newSequence;
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

double coolingSchedule(int iteration) {
    return pow(10,10) * pow(0.8, iteration/300);
}

long long repeatedRandom(vector<long long> sequenceInput) {
    vector<long long> tempSequence = randSolutionSequence();
    long long res;
    long long finalres = residue(tempSequence, sequenceInput);
    for(int i = 0; i < 25000; i++){
        vector<long long> randSequence = randSolutionSequence();
        res = residue(randSequence, sequenceInput);
        if (res < finalres) {
            finalres = res;
            tempSequence = randSequence;
        }
    }
    return finalres;
}

long long ppRepeatedRandom(vector<long long> sequenceInput) {
    vector<int> tempPartition = randPartition();
    long long res;
    long long finalres = KaramkarKarp(partitionToSequence(sequenceInput, tempPartition));
    for(int i = 0; i < 25000; i++){
        vector<int> randomPartition = randPartition();
        res = KaramkarKarp(partitionToSequence(sequenceInput, randPartition()));
        if (res < finalres) {
            finalres = res;
            tempPartition = randomPartition;
        }
    }
    return finalres;
}

long long hillClimbing(vector<long long> sequenceInput){
    vector<long long> tempSequence = randSolutionSequence();
    long long res;
    long long finalres = residue(tempSequence, sequenceInput);
    for(int i = 0; i < 25000; i++){
        vector<long long> neighborSequence = generateNeighbor(tempSequence);
        res = residue(neighborSequence, sequenceInput);
        if (res < finalres) {
            finalres = res;
            tempSequence = neighborSequence;
        }
    }
    return finalres;
}

long long ppHillClimbing(vector<long long> sequenceInput) {
    vector<int> tempPartition = randPartition();
    long long res;
    long long finalres = KaramkarKarp(partitionToSequence(sequenceInput, tempPartition));
    for(int i = 0; i < 25000; i++){
        vector<int> neighborPartition = generatePartitionNeighbor(tempPartition);
        res = KaramkarKarp(partitionToSequence(sequenceInput, neighborPartition));
        if (res < finalres) {
            finalres = res;
            tempPartition = neighborPartition;
        }
    }
    return finalres;
}

long long simulatedAnnealing(vector<long long> sequenceInput) {
    vector<long long> tempSequence = randSolutionSequence();
    long long res;
    long long tempres = residue(tempSequence, sequenceInput);
    long long finalres = tempres;
    for(int i = 0; i < 25000; i++){
        vector<long long> neighborSequence = generateNeighbor(tempSequence);
        res = residue(neighborSequence, sequenceInput);
        if (res < tempres) {
            tempSequence = neighborSequence;
            tempres = res;
        } else if (generateRandomReal() < exp((-res - tempres)/coolingSchedule(i))) {
            tempSequence = neighborSequence;
            tempres = res;
        }
        if (tempres < finalres) {
            finalres = tempres;
        }
    }
    return finalres;
}

long long ppSimulatedAnnealing(vector<long long> sequenceInput) {
    vector<int> tempPartition = randPartition();
    long long res;
    long long tempres = KaramkarKarp(partitionToSequence(sequenceInput,tempPartition));
    long long finalres = tempres;
    for(int i = 0; i < 25000; i++){
        vector<int> neighborPartition = generatePartitionNeighbor(tempPartition);
        res = KaramkarKarp(partitionToSequence(sequenceInput, neighborPartition));
        if (res < tempres) {
            tempPartition = neighborPartition;
            tempres = res;
        } else if (generateRandomReal() < exp((-res - tempres)/coolingSchedule(i))) {
            tempPartition = neighborPartition;
            tempres = res;
        }
        if (tempres < finalres) {
            finalres = tempres;
        }
    }
    return finalres;
}

int main(int argc, char* argv[]) {

    int flag = atoi(argv[1]);
    int alg = atoi(argv[2]);
    char* infile = argv[3];
    vector<long long> input(100);

    if (flag == 0) {
        input = readFile(infile);
    } else {
        input = randInputSequence();
    }

    if (alg == 0) {
        cout << KaramkarKarp(input);
    } else if (alg == 1) {
        cout << repeatedRandom(input);
    } else if (alg == 2) {
        cout << hillClimbing(input);
    } else if (alg == 3) {
        cout << simulatedAnnealing(input);
    } else if (alg == 11) {
        cout << ppRepeatedRandom(input);
    } else if (alg == 12) {
        cout << ppHillClimbing(input);
    } else if (alg == 13) {
        cout << ppSimulatedAnnealing(input);
    }

    return 0;
}
