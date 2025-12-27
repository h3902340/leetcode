#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

// FenwickTree
const int N = 1e5;
int tree[N];
int n;
void add(int i, int delta) {
    while (i < n) {
        tree[i] += delta;
        i += i & -i;
    }
}
int query(int i) {
    int s = 0;
    while (i > 0) {
        s += tree[i];
        i -= i & -i;
    }
    return s;
}

class Solution {
   public:
    vector<int> minDeletions(string s, vector<vector<int>>& queries) {
        n = s.size();
        int q = queries.size();
        for (int i = 0; i < n; i++) {
            tree[i] = 0;
        }
        s[0] -= 'A';
        for (int i = 1; i < n; i++) {
            s[i] -= 'A';
            if (s[i - 1] == s[i]) {
                add(i, 1);
            }
        }
        vector<int> res;
        for (int i = 0; i < q; i++) {
            if (queries[i][0] == 1) {
                int idx = queries[i][1];
                s[idx] ^= 1;
                if (idx > 0) {
                    if (s[idx] == s[idx - 1]) {
                        add(idx, 1);
                    } else {
                        add(idx, -1);
                    }
                }
                if (idx < n - 1) {
                    if (s[idx] == s[idx + 1]) {
                        add(idx + 1, 1);
                    } else {
                        add(idx + 1, -1);
                    }
                }
            } else {
                int a = query(queries[i][2]) - query(queries[i][1]);
                res.push_back(a);
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3777";
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
        getline(file_in, line_in);
        auto queries = jread_vector2d(line_in);
        auto res = sol.minDeletions(s, queries);
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
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