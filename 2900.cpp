#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    vector<string> getLongestSubsequence(vector<string>& words,
                                         vector<int>& groups) {
        int n = groups.size();
        vector<string> res;
        int i = 0;
        while (i < n) {
            int bit = groups[i];
            res.push_back(words[i]);
            i++;
            while (i < n && groups[i] == bit) {
                i++;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "2900";
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
        auto res = sol.getLongestSubsequence(words, groups);
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
        jprint_vector_string(res, "res");
        jprint_vector_string(ans, "ans");
        printf("\n");
    }
    if (allPass) {
        printf("%sALL CORRECT [%d/%d]\n%s", KGRN, passCount, caseCount, KNRM);
    } else {
        printf("%sWRONG ANSWER [%d/%d]\n%s", KRED, passCount, caseCount, KNRM);
        if (isMultiAns) {
            printf("%sThe problem may have multiple answers.\n%s", KGRN, KNRM);
        }
    }
    auto end = jtimer();
    jprint_time(begin, end);
    return 0;
}