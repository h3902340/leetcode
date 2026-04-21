#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    char v;
    int c;
};
class Solution {
   public:
    int maxRepOpt1(string text) {
        int n = text.size();
        vector<int> fre(26);
        for (int i = 0; i < n; i++) {
            fre[text[i] - 'a']++;
        }
        text += ' ';
        vector<Data> arr(2);
        char v = text[0];
        int c = 1;
        int res = 0;
        for (int i = 1; i <= n; i++) {
            if (text[i - 1] == text[i]) {
                c++;
            } else {
                if (fre[v - 'a'] > c) {
                    res = max(res, c + 1);
                } else {
                    res = max(res, c);
                }
                if (arr[0].v == v) {
                    if (arr[1].c == 1) {
                        int l = arr[0].c + c;
                        if (fre[v - 'a'] > arr[0].c + c) {
                            l++;
                        }
                        res = max(res, l);
                    }
                }
                arr[0] = arr[1];
                arr[1] = {v, c};
                v = text[i];
                c = 1;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "1156";
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
        auto text = jread_string(line_in);
        auto res = sol.maxRepOpt1(text);
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