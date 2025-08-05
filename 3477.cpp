#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define LOG2(X) (8 * sizeof(int) - __builtin_clz(X))
const int N = 1e2;
const int H = LOG2(N);
const int BASE = 1 << H;
int tree[BASE << 1];

class Solution {
   public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        int n = fruits.size();
        int b = BASE;
        for (int i = 0; i < n; i++) {
            tree[b + i] = baskets[i];
        }
        int h = 0;
        int pre = n;
        int cur = (pre + 1) >> 1;
        int c = b;
        while (b > 1) {
            b >>= 1;
            int j = 0;
            for (int i = 0; i < cur; i++) {
                tree[b + i] = max(tree[c + j], tree[c + j + 1]);
                j += 2;
            }
            h++;
            if (pre & 1) {
                tree[c + j - 1] = 0;
                tree[b + cur - 1] = tree[c + j - 2];
            }
            pre = cur;
            cur = (cur + 1) >> 1;
            c >>= 1;
        }
        int res = 0;
        for (int i = 0; i < n; i++) {
            int a = fruits[i];
            int idx = 1;
            if (tree[idx] < a) {
                res++;
                continue;
            }
            for (int j = 0; j < h; j++) {
                int leftIdx = idx << 1;
                int rightIdx = leftIdx + 1;
                if (tree[leftIdx] >= a) {
                    idx = leftIdx;
                    continue;
                }
                idx = rightIdx;
            }
            tree[idx] = 0;
            for (int j = 0; j < h; j++) {
                int nxt = idx >> 1;
                if (idx & 1) {
                    tree[nxt] = max(tree[idx - 1], tree[idx]);
                } else {
                    tree[nxt] = max(tree[idx], tree[idx + 1]);
                }
                idx = nxt;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3477";
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
        auto fruits = jread_vector(line_in);
        getline(file_in, line_in);
        auto baskets = jread_vector(line_in);
        auto res = sol.numOfUnplacedFruits(fruits, baskets);
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