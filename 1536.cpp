#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 100;
vector<int> mp[N];
class FenwickTree {
    int tree[N + 1];
    int sz;

   public:
    void init(int n) {
        sz = n + 1;
        for (int i = 1; i < sz; i++) {
            tree[i] = 0;
        }
    }
    void add(int i, int delta) {
        i++;
        while (i < sz) {
            tree[i] += delta;
            i += i & -i;
        }
    }
    int query(int i) {
        i++;
        int s = 0;
        while (i > 0) {
            s += tree[i];
            i -= i & -i;
        }
        return s;
    }
};
FenwickTree t;

class Solution {
   public:
    int minSwaps(vector<vector<int>>& grid) {
        int n = grid.size();
        t.init(n);
        for (int i = 0; i < n; i++) {
            mp[i].clear();
        }
        for (int i = n - 1; i >= 0; i--) {
            bool allZero = true;
            for (int j = n - 1; j >= 0; j--) {
                if (grid[i][j] == 1) {
                    mp[j].push_back(i);
                    allZero = false;
                    break;
                }
            }
            if (allZero) {
                mp[0].push_back(i);
            }
        }
        priority_queue<int, vector<int>, greater<int>> pq;
        int res = 0;
        for (int i = 0; i < n; i++) {
            for (auto e : mp[i]) {
                pq.push(e);
            }
            if (pq.empty()) {
                return -1;
            }
            int a = pq.top();
            pq.pop();
            res += a + t.query(a) - i;
            t.add(0, 1);
            t.add(a, -1);
        }
        return res;
    }
};

int main() {
    string problemName = "1536";
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
        auto grid = jread_vector2d(line_in);
        auto res = sol.minSwaps(grid);
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