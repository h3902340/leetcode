#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int business;
    string code;
    Data(int b, string c) {
        business = b;
        code = c;
    }
};
unordered_map<string, int> mp{
    {"electronics", 0}, {"grocery", 1}, {"pharmacy", 2}, {"restaurant", 3}};
class Solution {
   public:
    vector<string> validateCoupons(vector<string>& code,
                                   vector<string>& businessLine,
                                   vector<bool>& isActive) {
        int n = code.size();
        vector<Data> tmp;
        for (int i = 0; i < n; i++) {
            if (!isActive[i]) continue;
            int business = getBusiness(businessLine[i]);
            if (business == -1) continue;
            if (!isCodeValid(code[i])) continue;
            tmp.emplace_back(business, code[i]);
        }
        auto cmp = [&](Data a, Data b) {
            if (a.business != b.business) {
                return a.business < b.business;
            }
            return a.code < b.code;
        };
        sort(tmp.begin(), tmp.end(), cmp);
        vector<string> res(tmp.size());
        for (int i = 0; i < tmp.size(); i++) {
            res[i] = tmp[i].code;
        }
        return res;
    }
    int getBusiness(string& s) {
        if (mp.count(s)) {
            return mp[s];
        }
        return -1;
    }
    bool isCodeValid(string& s) {
        int n = s.size();
        if (n == 0) {
            return false;
        }
        for (int i = 0; i < n; i++) {
            if ((s[i] < '0' || s[i] > '9') && (s[i] < 'a' || s[i] > 'z') &&
                (s[i] < 'A' || s[i] > 'Z') && s[i] != '_') {
                return false;
            }
        }
        return true;
    }
};

int main() {
    string problemName = "3606";
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
        auto code = jread_vector_string(line_in);
        getline(file_in, line_in);
        auto businessLine = jread_vector_string(line_in);
        getline(file_in, line_in);
        auto isActive = jread_vector_bool(line_in);
        auto res = sol.validateCoupons(code, businessLine, isActive);
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