#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 1e5;
const int C = 3;
const int U = N << 1;
const int SCALE = 40;
const int T = N * SCALE;
const int BIT = 18;
const int MASK = (1 << BIT) - 1;
int cnt[C];
class SparseSet {
    int sparse[U + 1];

public:
    int dense[N + 1];
    int val[N + 1];
    int num;
    void init() { num = 0; }
    bool has(int x) {
        int idx = sparse[x];
        return (idx < num && dense[idx] == x);
    }
    void insert(int x, int v) {
        int idx = sparse[x];
        if (idx >= num || dense[idx] != x) {
            sparse[x] = num;
            dense[num] = x;
            val[num] = v;
            num++;
        }
    }
    int getVal(int x) { return val[sparse[x]]; }
};
SparseSet se;
class HashMap {
    ll table[T];
    int val[T];
    int t;

public:
    void init(int n) {
        t = n * SCALE;
        for (int i = 0; i < t; i++) {
            table[i] = -2;
        }
    }
    void insert(ll k, int v) {
        int key = k % t;
        while (table[key] != -2 && table[key] != k) {
            key++;
            if (key == t) {
                key = 0;
            }
        }
        table[key] = k;
        val[key] = v;
    }
    int getVal(ll k) {
        int key = k % t;
        while (table[key] != k) {
            if (table[key] == -2) {
                return -2;
            }
            key++;
            if (key == t) {
                key = 0;
            }
        }
        return val[key];
    }
};
HashMap mp;

class Solution {
public:
    int longestBalanced(string s) {
        int n = s.size();
        int res = 1;
        int a = 1;
        char c = s[0];
        for (int i = 1; i < n; i++) {
            if (s[i] == c) {
                a++;
            } else {
                a = 1;
                c = s[i];
            }
            if (res < a) {
                res = a;
            }
        }
        for (int k = 0; k < C; k++) {
            int d = 0;
            int a = (k + 1) % C;
            se.init();
            se.insert(N, -1);
            for (int i = 0; i < n; i++) {
                int c = s[i] - 'a';
                if (c == k) {
                    d = 0;
                    se.init();
                    se.insert(N, i);
                    continue;
                }
                if (c == a) {
                    d++;
                } else {
                    d--;
                }
                int key = N + d;
                if (se.has(key)) {
                    int l = i - se.getVal(key);
                    if (res < l) {
                        res = l;
                    }
                } else {
                    se.insert(key, i);
                }
            }
        }
        mp.init(n);
        mp.insert(0, -1);
        for (int i = 0; i < C; i++) {
            cnt[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            cnt[c]++;
            ll v = 0;
            for (int j = 1; j < C; j++) {
                v = (v << BIT) | ((cnt[j] - cnt[(j + 1) % C]) & MASK);
            }
            int idx = mp.getVal(v);
            if (idx == -2) {
                mp.insert(v, i);
            } else {
                int l = i - idx;
                if (res < l) {
                    res = l;
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3714";
    auto begin = jtimer();
    Solution sol;
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    string line_in;
    string line_out;
    while (getline(file_in, line_in)) {
        auto s = jread_string(line_in);
        auto res = sol.longestBalanced(s);
        getline(file_out, line_out);
        auto ans = jread_int(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint(res, "res");
        jprint(ans, "ans");
        printf("\n");
    }
    if (allPass) {
        printf("%sALL CORRECT [%d/%d]\n%s", KGRN, passCount, caseCount, KNRM);
    } else {
        printf("%sWRONG ANSWER [%d/%d]\n%s", KRED, passCount, caseCount, KNRM);
    }
    auto end = jtimer();
    jprint_time(begin, end);
    return 0;
}