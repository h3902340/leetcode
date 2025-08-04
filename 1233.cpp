#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    vector<string> removeSubfolders(vector<string> &folder) {
        int n = folder.size();
        sort(folder.begin(), folder.end());
        int i = 0;
        for (int j = 1; j < n; j++) {
            if (folder[i].size() > folder[j].size()) {
                i++;
                folder[i] = folder[j];
                continue;
            }
            if (folder[i].size() == folder[j].size()) {
                bool isEqual = true;
                int len = folder[i].size();
                for (int k = 0; k < len; k++) {
                    if (folder[i][k] != folder[j][k]) {
                        isEqual = false;
                        break;
                    }
                }
                if (!isEqual) {
                    i++;
                    folder[i] = folder[j];
                }
                continue;
            }
            bool isPrefix = true;
            int len = folder[i].size();
            for (int k = 0; k < len; k++) {
                if (folder[i][k] != folder[j][k]) {
                    isPrefix = false;
                    break;
                }
            }
            if (folder[j][len] != '/') {
                isPrefix = false;
            }
            if (!isPrefix) {
                i++;
                folder[i] = folder[j];
            }
        }
        folder.resize(i + 1);
        return folder;
    }
};

int main() {
    string problemName = "1233";
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
        auto folder = jread_vector_string(line_in);
        auto res = sol.removeSubfolders(folder);
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