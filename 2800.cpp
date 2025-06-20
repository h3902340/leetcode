#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int strCount = 3;
const int N = 100;
string strs[3];
int failure[N];
class Solution {
   public:
    string minimumString(string a, string b, string c) {
        strs[0] = a;
        strs[1] = b;
        strs[2] = c;
        return perm(0);
    }
    string perm(int i) {
        if (i == strCount) {
            string res = f();
            return res;
        }
        string res = perm(i + 1);
        for (int j = i + 1; j < strCount; j++) {
            swap(strs[i], strs[j]);
            string tmp = perm(i + 1);
            if (res.size() > tmp.size() ||
                (res.size() == tmp.size() && isLessThan(tmp, res))) {
                res = tmp;
            }
            swap(strs[i], strs[j]);
        }
        return res;
    }
    string f() {
        string &a = strs[0];
        string &b = strs[1];
        string &c = strs[2];
        string res = a;
        buildFailure(b);
        int len = KMP(res, b);
        for (int i = len; i < b.size(); i++) {
            res += b[i];
        }
        buildFailure(c);
        len = KMP(res, c);
        for (int i = len; i < c.size(); i++) {
            res += c[i];
        }
        return res;
    }
    bool isLessThan(string a, string b) {
        int m = a.size();
        int n = b.size();
        int i = 0;
        while (i < m && i < n) {
            if (a[i] < b[i]) return true;
            if (a[i] > b[i]) return false;
            i++;
        }
        return m < n;
    }
    void buildFailure(string pattern) {
        int p = pattern.size();
        failure[0] = 0;
        for (int i = 1; i < p; i++) {
            int j = failure[i - 1];
            while (true) {
                if (pattern[j] == pattern[i]) {
                    failure[i] = j + 1;
                    break;
                }
                if (j == 0) {
                    failure[i] = 0;
                    break;
                }
                j = failure[j - 1];
            }
        }
    }
    int KMP(string s, string pattern) {
        int n = s.size();
        int p = pattern.size();
        int k = 0;
        for (int i = 0; i < n; i++) {
            while (true) {
                if (s[i] == pattern[k]) {
                    k++;
                    if (k == p) {
                        return k;
                    }
                    break;
                }
                if (k == 0) {
                    break;
                }
                k = failure[k - 1];
            }
        }
        return k;
    }
};

int main() {
    string problemName = "2800";
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
        auto a = jread_string(line_in);
        getline(file_in, line_in);
        auto b = jread_string(line_in);
        getline(file_in, line_in);
        auto c = jread_string(line_in);
        auto res = sol.minimumString(a, b, c);
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