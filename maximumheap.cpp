#include <iostream>
#include <vector>

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

//used this for testing

/*int main() {
    MaxHeap pq;
    
    pq.insert(3);
    pq.insert(2);
    pq.insert(15);
    pq.insert(2100000000000);
    pq.insert(7000000000);


    cout << "Size is " << pq.getSize() << endl;

    cout << pq.get_max() << "\n";
    cout << pq.delete_max() << "\n";
    cout << pq.get_max() << "\n";

    cout << "Size is " << pq.getSize() << endl;


    return 0;
}*/
