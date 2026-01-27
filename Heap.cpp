#include "Jutil.h"
using namespace std;

#define ll long long
struct Data {
    ll v;
    int i;
    bool operator<(const Data& a) const { return v == a.v ? i < a.i : v < a.v; }
    bool operator>(const Data& a) const { return v == a.v ? i > a.i : v > a.v; }
    Data& operator=(const Data& a) {
        v = a.v;
        i = a.i;
        return *this;
    }
};
const int N = 1e7;
const int top = 1;
Data heap[N << 1];
int idx;
void push(Data a) {
    int i = idx++;
    while (i > top) {
        int p = i >> 1;
        if (heap[p] < a) {
            break;
        }
        heap[i] = heap[p];
        i = p;
    }
    heap[i] = a;
}
void heapify(int i) {
    Data a = heap[i];
    int l = i << 1;
    int r = l + 1;
    while (l < idx) {
        if (r < idx && heap[r] < heap[l]) {
            l = r;
        }
        if (a < heap[l]) {
            break;
        }
        heap[i] = heap[l];
        i = l;
        l = i << 1;
        r = l + 1;
    }
    heap[i] = a;
}
void pop() {
    heap[top] = heap[--idx];
    heapify(top);
}
void init() { idx = 0; }

int main() {
    vector<Data> arr(N);
    for (int i = 0; i < N; i++) {
        arr[i] = {(ll)rand() << 32 | rand(), rand()};
    }
    auto start = jtimer();
    for (int i = 0; i < N; i++) {
        push(arr[i]);
    }
    auto end = jtimer();
    printf("[%d pushes]\n", N);
    printf("my heap: ");
    jprint_time(start, end);
    priority_queue<Data, vector<Data>, greater<Data>> pq;
    auto start2 = jtimer();
    for (int i = 0; i < N; i++) {
        pq.push({arr[i].v, arr[i].i});
    }
    auto end2 = jtimer();
    printf("priority_queue: ");
    jprint_time(start2, end2);
    printf("[%d pops]\n", N);
    auto start3 = jtimer();
    for (int i = 0; i < N; i++) {
        pop();
    }
    auto end3 = jtimer();
    printf("my heap: ");
    jprint_time(start3, end3);
    auto start4 = jtimer();
    for (int i = 0; i < N; i++) {
        pq.pop();
    }
    auto end4 = jtimer();
    printf("priority_queue: ");
    jprint_time(start4, end4);
    return 0;
}