#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    vector<vector<string>> wordSquares(vector<string>& words) {
        int n = words.size();
        sort(begin(words), end(words));
        vector<vector<string>> res;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (j == i) {
                    continue;
                }
                for (int k = 0; k < n; k++) {
                    if (k == i || k == j) {
                        continue;
                    }
                    for (int l = 0; l < n; l++) {
                        if (l == i || l == j || l == k) {
                            continue;
                        }
                        string& top = words[i];
                        string& left = words[j];
                        string& right = words[k];
                        string& bottom = words[l];
                        if (top[0] == left[0] && top[3] == right[0] &&
                            bottom[0] == left[3] && bottom[3] == right[3]) {
                            res.push_back({top, left, right, bottom});
                        }
                    }
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3799";
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
        auto res = sol.wordSquares(words);
        getline(file_out, line_out);
        auto ans = jread_vector2d_string(line_out);
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