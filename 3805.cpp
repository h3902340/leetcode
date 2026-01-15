#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int C = 26;
class Solution {
   public:
    long long countPairs(vector<string>& words) {
        int n = words.size();
        int m = words[0].size();
        ll res = 0;
        unordered_map<string, int> cnt;
        for (int i = 0; i < n; i++) {
            char f = words[i][0];
            for (int j = 0; j < m; j++) {
                if (words[i][j] < f) {
                    words[i][j] += C;
                }
                words[i][j] -= f;
            }
            res += cnt[words[i]];
            cnt[words[i]]++;
        }
        return res;
    }
};

int main() {
    string problemName = "3805";
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
        auto words = jread_vector_string(line_in);
        auto res = sol.countPairs(words);
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