#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int NMAX = 1e5;
const int COLORMAX = 26;
vector<int> parent[NMAX];
int dp[NMAX][COLORMAX];
int outDeg[NMAX];
int q[NMAX];

class Solution {
   public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int n = colors.size();
        int m = edges.size();
        unordered_map<int, int> map;
        int colorSize = 0;
        for (int i = 0; i < n; i++) {
            parent[i].clear();
            outDeg[i] = 0;
            if (!map.count(colors[i])) {
                map[colors[i]] = colorSize++;
            }
        }
        for (auto& e : edges) {
            parent[e[1]].push_back(e[0]);
            outDeg[e[0]]++;
        }
        int l = 0;
        int r = 0;
        for (int i = 0; i < n; i++) {
            if (outDeg[i] == 0) {
                q[r++] = i;
            }
            for (int j = 0; j < colorSize; j++) {
                dp[i][j] = 0;
            }
        }
        int maxAll = -1;
        while (l < r) {
            int f = q[l++];
            dp[f][map[colors[f]]]++;
            for (int j = 0; j < colorSize; j++) {
                if (maxAll < dp[f][j]) {
                    maxAll = dp[f][j];
                }
            }
            for (auto& e : parent[f]) {
                outDeg[e]--;
                m--;
                if (outDeg[e] == 0) {
                    q[r++] = e;
                }
                for (int j = 0; j < colorSize; j++) {
                    if (dp[e][j] < dp[f][j]) {
                        dp[e][j] = dp[f][j];
                    }
                }
            }
        }
        if (m > 0) {
            return -1;
        }
        return maxAll;
    }
};

int main() {
    string problemName = "1857";
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
        auto colors = jread_string(line_in);
        getline(file_in, line_in);
        auto edges = jread_vector2d(line_in);
        auto res = sol.largestPathValue(colors, edges);
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