#include <unordered_set>
#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long

// TODO: use suffix tree instead, this solution is bad because it just uses a large p and hope for no collisions
// base has to be 27 to distinguish between "aaab" and "b"
const int BASE = 27;
const ll p = pow(2, 53);
const int N = 3e4;
ll pow27[N];
ll hashing[N];
bool isInit = false;
static void init() {
    if (isInit) return;
    isInit = true;
    pow27[0] = 1;
    for (int i = 1; i < N; i++) {
        pow27[i] = pow27[i - 1] * BASE % p;
    }
}

class Solution {
   public:
    string longestDupSubstring(string s) {
        init();
        int n = s.size();
        string t(n, 0);
        for (int i = 0; i < n; i++) {
            t[i] = s[i] - 'a' + 1;
        }
        hashing[0] = t[0];
        for (int i = 1; i < n; i++) {
            hashing[i] = (hashing[i - 1] * BASE + t[i]) % p;
        }
        int l = 1;
        int r = n;
        int max = 0;
        int maxIndex = -1;
        unordered_set<ll> se;
        while (l <= r) {
            int mid = (l + r) >> 1;
            ll b = pow27[mid - 1];
            ll a = hashing[mid - 1];
            se.clear();
            se.insert(a);
            bool same = false;
            for (int i = 0; i + mid < n; i++) {
                a = ((a - b * t[i]) * BASE + t[i + mid]) % p;
                if (a < 0) {
                    a += p;
                }
                if (se.count(a)) {
                    max = mid;
                    maxIndex = i + 1;
                    same = true;
                    break;
                }
                se.insert(a);
            }
            if (same) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        if (maxIndex == -1) return "";
        return s.substr(maxIndex, max);
    }
};

int main() {
    string problemName = "1044";
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
        auto res = sol.longestDupSubstring(s);
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
        // jprint(res, "res");
        // jprint(ans, "ans");
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