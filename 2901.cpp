#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int NMAX = 1e3;
int dp[NMAX];
int pre[NMAX];

class Solution {
   public:
    vector<string> getWordsInLongestSubsequence(vector<string>& words,
                                                vector<int>& groups) {
        int n = words.size();
        int maxIndex = -1;
        for (int i = 0; i < n; i++) {
            int max = 0;
            pre[i] = -1;
            for (int j = 0; j < i; j++) {
                if (groups[i] == groups[j]) continue;
                if (words[i].size() != words[j].size()) continue;
                int dis = 0;
                for (int k = 0; k < words[i].size(); k++) {
                    if (words[i][k] != words[j][k]) dis++;
                    if (dis == 2) break;
                }
                if (dis == 1) {
                    if (max < dp[j]) {
                        max = dp[j];
                        pre[i] = j;
                    }
                }
            }
            dp[i] = max + 1;
            if (maxIndex == -1 || dp[maxIndex] < dp[i]) {
                maxIndex = i;
            }
        }
        int j = dp[maxIndex];
        vector<string> res(j);
        j--;
        for (; j >= 0; j--) {
            res[j] = words[maxIndex];
            maxIndex = pre[maxIndex];
        }
        return res;
    }
};

int main() {
    string problemName = "2901";
    bool isMultiAns = true;
    auto begin = jtimer();
    Solution sol;
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    string line_in1;
    string line_in2;
    string line_out;
    while (getline(file_in, line_in1)) {
        auto words = jread_vector_string(line_in1);
        getline(file_in, line_in2);
        auto groups = jread_vector(line_in2);
        auto res = sol.getWordsInLongestSubsequence(words, groups);
        getline(file_out, line_out);
        auto ans = jread_vector_string(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        printf("words = %s\n", line_in1.c_str());
        printf("groups = %s\n", line_in2.c_str());
        jprint(res, "res");
        jprint(ans, "ans");
        printf("\n");
    }
    if (allPass) {
        printf("%sALL CORRECT [%d/%d]\n%s", KGRN, passCount, caseCount, KNRM);
    } else {
        printf("%sWRONG ANSWER [%d/%d]\n%s", KRED, passCount, caseCount, KNRM);
    }
    if (isMultiAns) {
        printf("%sThe problem may have multiple answers.\n%s", KGRN, KNRM);
    }
    auto end = jtimer();
    jprint_time(begin, end);
    return 0;
}