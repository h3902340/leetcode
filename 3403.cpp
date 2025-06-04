#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    string answerString(string word, int numFriends) {
        if (numFriends == 1) {
            return word;
        }
        int n = word.size();
        int i = 0;
        int j = 1;
        int k = 0;
        while (j + k < n) {
            while (j + k < n && word[i + k] == word[j + k]) {
                k++;
            }
            if (j + k < n) {
                if (word[i + k] < word[j + k]) {
                    int t = i;
                    i = j;
                    j = max(j + 1, t + k + 1);
                } else {
                    j = j + k + 1;
                }
                k = 0;
            }
        }
        int len = n - i;
        int limit = n - numFriends + 1;
        if (len > limit) {
            return word.substr(i, limit);
        } else {
            return word.substr(i, len);
        }
    }
};

int main() {
    string problemName = "3403";
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
        auto word = jread_string(line_in);
        getline(file_in, line_in);
        auto numFriends = jread_int(line_in);
        auto res = sol.answerString(word, numFriends);
        getline(file_out, line_out);
        auto ans = jread_string(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint_string(res, "res");
        jprint_string(ans, "ans");
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