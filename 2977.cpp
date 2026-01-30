#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 1000;
const int M = 100;
const int M2 = M << 1;
ll dis[M2][M2];
ll U = 1e12;
void initFloydWarshall(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            dis[i][j] = U;
        }
    }
}
void run(int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (dis[i][k] == U) {
                continue;
            }
            for (int j = 0; j < n; j++) {
                if (dis[k][j] == U) {
                    continue;
                }
                if (dis[i][j] > dis[i][k] + dis[k][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
    }
}
ll dp[N];
const int C = 26;
struct Trie {
    int idx[C];
    int key;
};
Trie arr[N * M];
int idx;
int key;
void initTrie() {
    for (int i = 0; i < C; i++) {
        arr[0].idx[i] = -1;
    }
    idx = 1;
    key = 0;
}
int add(string& s) {
    int n = s.size();
    int id = 0;
    for (int i = 0; i < n; i++) {
        int c = s[i] - 'a';
        if (arr[id].idx[c] == -1) {
            for (int j = 0; j < C; j++) {
                arr[idx].idx[j] = -1;
            }
            arr[idx].key = -1;
            arr[id].idx[c] = idx++;
        }
        id = arr[id].idx[c];
    }
    if (arr[id].key == -1) {
        arr[id].key = key++;
    }
    return arr[id].key;
}
int oriKey[M];
int chaKey[M];

class Solution {
   public:
    long long minimumCost(string source, string target,
                          vector<string>& original, vector<string>& changed,
                          vector<int>& cost) {
        int n = source.size();
        int m = original.size();
        initTrie();
        for (int i = 0; i < m; i++) {
            oriKey[i] = add(original[i]);
            chaKey[i] = add(changed[i]);
        }
        initFloydWarshall(key);
        for (int i = 0; i < m; i++) {
            int a = oriKey[i];
            int b = chaKey[i];
            if (dis[a][b] > cost[i]) {
                dis[a][b] = cost[i];
            }
        }
        run(key);
        for (int i = n - 1; i >= 0; i--) {
            dp[i] = U;
            int x = 0;
            int y = 0;
            bool same = true;
            for (int j = i; j < n; j++) {
                int s = source[j] - 'a';
                int t = target[j] - 'a';
                if (s != t) {
                    same = false;
                }
                int a = -1;
                int b = -1;
                if (x != -1) {
                    if (arr[x].idx[s] == -1) {
                        x = -1;
                    } else {
                        x = arr[x].idx[s];
                        a = arr[x].key;
                    }
                }
                if (y != -1) {
                    if (arr[y].idx[t] == -1) {
                        y = -1;
                    } else {
                        y = arr[y].idx[t];
                        b = arr[y].key;
                    }
                }
                if (same) {
                    ll v = 0;
                    if (j + 1 < n) {
                        v += dp[j + 1];
                    }
                    if (dp[i] > v) {
                        dp[i] = v;
                    }
                    continue;
                }
                if (x == -1 || y == -1) {
                    break;
                }
                if (a != -1 && b != -1) {
                    ll v = dis[a][b];
                    if (j + 1 < n) {
                        v += dp[j + 1];
                    }
                    if (dp[i] > v) {
                        dp[i] = v;
                    }
                }
            }
        }
        if (dp[0] == U) {
            return -1;
        }
        return dp[0];
    }
};

int main() {
    string problemName = "2977";
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
        auto source = jread_string(line_in);
        getline(file_in, line_in);
        auto target = jread_string(line_in);
        getline(file_in, line_in);
        auto original = jread_vector_string(line_in);
        getline(file_in, line_in);
        auto changed = jread_vector_string(line_in);
        getline(file_in, line_in);
        auto cost = jread_vector(line_in);
        auto res = sol.minimumCost(source, target, original, changed, cost);
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