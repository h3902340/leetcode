#include "Jutil.h"
using namespace std;

const int N = 4e4;
const int C = 26;
const int K = 15;
class Trie {
    struct Node {
        int idx[C];
        int cnt[C];
    };
    Node arr[N * K];
    int idx;

   public:
    void init() {
        for (int i = 0; i < C; i++) {
            arr[0].idx[i] = 0;
            arr[0].cnt[i] = 0;
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
                    arr[idx].cnt[j] = 0;
                }
                arr[id].idx[c] = idx++;
            }
            arr[id].cnt[c]++;
            id = arr[id].idx[c];
        }
    }
    void remove(string& s) {
        int n = s.size();
        int id = 0;
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            arr[id].cnt[c]--;
            id = arr[id].idx[c];
        }
    }
    bool has(string& s) {
        int n = s.size();
        int id = 0;
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            if (arr[id].cnt[c] == 0) {
                return false;
            }
            id = arr[id].idx[c];
        }
        return true;
    }
};
Trie t;

int main() {
    string a = "hello";
    string b = "world";
    string c = "hell";
    t.init();
    t.add(a);
    printf("has(%s):%d\n", c.c_str(), t.has(c));  // has("hell"):1
    printf("has(%s):%d\n", a.c_str(), t.has(a));  // has("hello"):1
    printf("has(%s):%d\n", b.c_str(), t.has(b));  // has("world"):0
    t.remove(a);
    printf("has(%s):%d\n", a.c_str(), t.has(a));  // has("hello"):0
    return 0;
}