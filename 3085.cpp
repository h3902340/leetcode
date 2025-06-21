#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int v;
    int cnt;
};
const int C = 26;
int fre[C];
Data uniqueFre[C];
class Solution {
   public:
    int minimumDeletions(string word, int k) {
        int n = word.size();
        for (int i = 0; i < C; i++) {
            fre[i] = 0;
        }
        for (auto e : word) {
            fre[e - 'a']++;
        }
        sort(begin(fre), end(fre));
        int i = 0;
        while (fre[i] == 0) {
            i++;
        }
        int j = 0;
        while (i < C) {
            int f = fre[i];
            int c = 0;
            while (i < C && fre[i] == f) {
                c++;
                i++;
            }
            uniqueFre[j++] = {f, c};
        }
        i = 0;
        j--;
        int cost = 0;
        while (uniqueFre[j].v - uniqueFre[i].v > k) {
            cost += uniqueFre[i].v * uniqueFre[i].cnt;
            i++;
        }
        i--;
        int res = cost;
        while (i >= 0) {
            cost -= uniqueFre[i].v * uniqueFre[i].cnt;
            while (uniqueFre[j].v - uniqueFre[i].v > k) {
                cost += uniqueFre[j].cnt;
                uniqueFre[j].v--;
                if (uniqueFre[j].v == uniqueFre[j - 1].v) {
                    uniqueFre[j - 1].cnt += uniqueFre[j].cnt;
                    j--;
                }
            }
            i--;
            if (res > cost) {
                res = cost;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3085";
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
        auto k = jread_int(line_in);
        auto res = sol.minimumDeletions(word, k);
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