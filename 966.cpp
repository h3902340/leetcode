#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    vector<string> spellchecker(vector<string>& wordlist,
                                vector<string>& queries) {
        int n = wordlist.size();
        int q = queries.size();
        unordered_set<string> ori;
        unordered_map<string, int> low;
        unordered_map<string, int> lowA;
        for (int i = 0; i < n; i++) {
            string& w = wordlist[i];
            ori.insert(w);
            string key = toLower(w);
            if (!low.count(key)) {
                low[key] = i;
            }
            string keyA = toVowelA(key);
            if (!lowA.count(keyA)) {
                lowA[keyA] = i;
            }
        }
        vector<string> res(q);
        for (int i = 0; i < q; i++) {
            string& w = queries[i];
            if (ori.count(w)) {
                res[i] = queries[i];
                continue;
            }
            string key = toLower(w);
            if (low.count(key)) {
                res[i] = wordlist[low[key]];
                continue;
            }
            string keyA = toVowelA(key);
            if (lowA.count(keyA)) {
                res[i] = wordlist[lowA[keyA]];
                continue;
            }
            res[i] = "";
        }
        return res;
    }
    string toLower(string s) {
        for (auto& c : s) {
            if (c >= 'A' && c <= 'Z') {
                c = c - 'A' + 'a';
            }
        }
        return s;
    }
    string toVowelA(string s) {
        for (auto& c : s) {
            if (c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                c = 'a';
            }
        }
        return s;
    }
};

int main() {
    string problemName = "966";
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
        auto wordlist = jread_vector_string(line_in);
        getline(file_in, line_in);
        auto queries = jread_vector_string(line_in);
        auto res = sol.spellchecker(wordlist, queries);
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