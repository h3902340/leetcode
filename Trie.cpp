#include "Jutil.h"
using namespace std;

const int N = 1e5;
const int C = 26;
struct Trie {
    int idx[C];
};
Trie arr[N];
int idx;
void init() {
    for (int i = 0; i < C; i++) {
        arr[0].idx[i] = 0;
    }
    idx = 1;
}
void add(string& s) {
    int n = s.size();
    int id = 0;
    for (int i = 0; i < n; i++) {
        int c = s[i] - 'a';
        if (arr[id].idx[c] == 0) {
            for (int j = 0; j < C; j++) {
                arr[idx].idx[j] = 0;
            }
            arr[id].idx[c] = idx++;
        }
        id = arr[id].idx[c];
    }
}
bool has(string& s) {
    int n = s.size();
    int id = 0;
    for (int i = 0; i < n; i++) {
        int c = s[i] - 'a';
        if (arr[id].idx[c] == 0) {
            return false;
        }
        id = arr[id].idx[c];
    }
    return true;
}

int main() {
    string a = "hello";
    string b = "world";
    string c = "hell";
    init();
    add(a);
    printf("has(%s):%d\n", c.c_str(), has(c));  // has("hell"):1
    printf("has(%s):%d\n", a.c_str(), has(a));  // has("hello"):1
    printf("has(%s):%d\n", b.c_str(), has(b));  // has("world"):0
    return 0;
}