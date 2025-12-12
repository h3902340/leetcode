#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 100;
const char OFFLINE = 'O';
const char MESSAGE = 'M';
const char ALL = 'A';
const char HERE = 'H';
const char SPACE = ' ';
const char ZERO = '0';
const int WAIT = 60;
int online[N];
int strToInt(string& s) {
    int res = 0;
    for (auto& c : s) {
        res = res * 10 + c - ZERO;
    }
    return res;
}

class Solution {
   public:
    vector<int> countMentions(int numberOfUsers,
                              vector<vector<string>>& events) {
        vector<int> res(numberOfUsers);
        for (int i = 0; i < numberOfUsers; i++) {
            online[i] = 0;
        }
        auto cmp = [](vector<string>& a, vector<string>& b) {
            int x = strToInt(a[1]);
            int y = strToInt(b[1]);
            if (x == y) {
                return a[0][0] == OFFLINE;
            }
            return x < y;
        };
        sort(begin(events), end(events), cmp);
        int all = 0;
        for (auto& e : events) {
            if (e[0][0] == MESSAGE) {
                if (e[2][0] == ALL) {
                    all++;
                } else if (e[2][0] == HERE) {
                    int t = strToInt(e[1]);
                    for (int i = 0; i < numberOfUsers; i++) {
                        if (online[i] <= t) {
                            res[i]++;
                        }
                    }
                } else {
                    int sz = e[2].size();
                    int i = 2;
                    while (i < sz) {
                        int id = 0;
                        while (i < sz && e[2][i] != SPACE) {
                            id = id * 10 + e[2][i] - ZERO;
                            i++;
                        }
                        res[id]++;
                        i += 3;
                    }
                }
            } else {
                int id = strToInt(e[2]);
                int t = strToInt(e[1]);
                online[id] = t + WAIT;
            }
        }
        for (int i = 0; i < numberOfUsers; i++) {
            res[i] += all;
        }
        return res;
    }
};

int main() {
    string problemName = "3433";
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
        auto numberOfUsers = jread_int(line_in);
        getline(file_in, line_in);
        auto events = jread_vector2d_string(line_in);
        auto res = sol.countMentions(numberOfUsers, events);
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
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