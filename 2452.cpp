#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    vector<string> twoEditWords(vector<string>& queries,
                                vector<string>& dictionary) {
        int n = queries[0].size();
        if (n <= 2) {
            return queries;
        }
        vector<string> res;
        for (auto& e : queries) {
            int diff = 0;
            for (auto& f : dictionary) {
                diff = 0;
                for (int i = 0; i < n; i++) {
                    if (e[i] != f[i]) {
                        diff++;
                        if (diff > 2) {
                            break;
                        }
                    }
                }
                if (diff <= 2) {
                    break;
                }
            }
            if (diff <= 2) {
                res.push_back(e);
            }
        }
        return res;
    }
};

int main() {
    string problemName = "2452";
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
        auto queries = jread_vector_string(line_in);
        getline(file_in, line_in);
        auto dictionary = jread_vector_string(line_in);
        auto res = sol.twoEditWords(queries, dictionary);
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