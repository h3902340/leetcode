#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int CHARMAX = 26;
vector<int> c[CHARMAX];

class Solution {
   public:
    string clearStars(string s) {
        int n = s.size();
        int size = n;
        for (int i = 0; i < CHARMAX; i++) {
            c[i].clear();
        }
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int i = 0; i < n; i++) {
            if (s[i] == '*') {
                int j = pq.top();
                s[c[j].back()] = '*';
                c[j].pop_back();
                if (c[j].size() == 0) {
                    pq.pop();
                }
                size -= 2;
            } else {
                int ch = s[i] - 'a';
                if (c[ch].size() == 0) {
                    pq.push(ch);
                }
                c[ch].push_back(i);
            }
        }
        string res(size, 0);
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] != '*') {
                res[j++] = s[i];
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3170";
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
        auto s = jread_string(line_in);
        auto res = sol.clearStars(s);
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