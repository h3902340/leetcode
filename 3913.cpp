#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int fre;
    int idx;
    char c;
};
auto cmp = [](Data& a, Data& b) {
    if (a.fre == b.fre) {
        return a.idx < b.idx;
    }
    return a.fre > b.fre;
};
Data arr[5];
class Solution {
   public:
    string sortVowels(string s) {
        int n = s.size();
        unordered_map<char, int> mp;
        unordered_map<int, char> inv;
        mp['a'] = 0;
        mp['e'] = 1;
        mp['i'] = 2;
        mp['o'] = 3;
        mp['u'] = 4;
        inv[0] = 'a';
        inv[1] = 'e';
        inv[2] = 'i';
        inv[3] = 'o';
        inv[4] = 'u';
        for (int i = 0; i < 5; i++) {
            arr[i] = {0, -1, inv[i]};
        }
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] != 'a' && s[i] != 'e' && s[i] != 'i' && s[i] != 'o' &&
                s[i] != 'u') {
                continue;
            }
            arr[mp[s[i]]].fre++;
            arr[mp[s[i]]].idx = i;
        }
        sort(begin(arr), end(arr), cmp);
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' ||
                s[i] == 'u') {
                while (arr[j].fre == 0) {
                    j++;
                }
                s[i] = arr[j].c;
                arr[j].fre--;
            }
        }
        return s;
    }
};

int main() {
    string problemName = "3913";
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
        auto res = sol.sortVowels(s);
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