#include <iostream>
#include <vector>

using namespace std;


class MaxHeap {
    private:
        vector<int> heap;
        int p(int i);
        int r(int i);
        int l(int i);

    public:
        void shiftDown(int i);
        void shiftUp(int i);
        void insert(int key);
        int get_max();
        int delete_max();
        int getSize();
};

int MaxHeap::p(int i) {
    return (i - 1) / 2;
}

int MaxHeap::r(int i) {
    return (2 * i + 2);
}

int MaxHeap::l(int i) {
    return (2 * i + 1);
}

int MaxHeap::getSize() {
    return heap.size();
}

void MaxHeap::insert(int val) {
    heap.push_back(val);
    int index = heap.size() - 1;
    shiftUp(index);
}

int MaxHeap::get_max() {
    return heap[0];
}

int MaxHeap::delete_max() {
    int max = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    shiftDown(0);
    return max;

}

void MaxHeap::shiftDown(int i) {
    int left = l(i);
    int right = r(i);

    int largest = i;

    if (left < heap.size() && heap[left] > heap[i])
        largest = left;

    if (right < heap.size() && heap[right] > heap[largest])
        largest = right;

    if (largest != i) {
        swap(heap[i], heap[largest]);
        shiftDown(largest);
    }
}

void MaxHeap::shiftUp(int i) {

    if (i && heap[p(i)] < heap[i]) {
        swap(heap[i], heap[p(i)]);
        shiftUp(p(i));
    }
}

//used this for testing

/*int main() {
    MaxHeap pq;
    
    pq.insert(3);
    pq.insert(2);
    pq.insert(15);
    pq.insert(21);
    pq.insert(7);


    cout << "Size is " << pq.getSize() << endl;

    cout << pq.get_max() << "\n";
    cout << pq.delete_max() << "\n";
    cout << pq.get_max() << "\n";

    cout << "Size is " << pq.getSize() << endl;


    return 0;
}*/
