#include <iostream>
#include <vector>
#include "maximumheap.cpp"


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

int main() {
    vector<int> sequence;
    sequence.push_back(14);
    sequence.push_back(6);
    sequence.push_back(7);
    sequence.push_back(9);
    int answer = KaramkarKarp(sequence);
    cout << answer << "\n";
    return 0;
}
