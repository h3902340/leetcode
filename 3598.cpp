#include <set>
#include <unordered_set>
#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    vector<int> longestCommonPrefix(vector<string>& words) {
        int n = words.size();
        if (n == 1) return {0};
        vector<int> prefix(n - 1);
        set<int, greater<int>> se;
        unordered_map<int, int> cnt;
        se.insert(0);
        cnt[0]++;
        for (int i = 1; i < n; i++) {
            int j = 0;
            while (j < words[i - 1].size() && j < words[i].size() &&
                   words[i - 1][j] == words[i][j]) {
                j++;
            }
            j--;
            int len = j + 1;
            se.insert(len);
            cnt[len]++;
            prefix[i - 1] = len;
        }
        vector<int> res(n);
        cnt[prefix[0]]--;
        if (cnt[prefix[0]] == 0) {
            se.erase(prefix[0]);
        }
        res[0] = *se.begin();
        cnt[prefix[0]]++;
        se.insert(prefix[0]);
        for (int i = 1; i < n - 1; i++) {
            cnt[prefix[i - 1]]--;
            cnt[prefix[i]]--;
            if (cnt[prefix[i - 1]] == 0) {
                se.erase(prefix[i - 1]);
            }
            if (cnt[prefix[i]] == 0) {
                se.erase(prefix[i]);
            }
            int j = 0;
            while (j < words[i - 1].size() && j < words[i + 1].size() &&
                   words[i - 1][j] == words[i + 1][j]) {
                j++;
            }
            j--;
            int len = j + 1;
            cnt[len]++;
            se.insert(len);
            res[i] = *se.begin();
            if (j != -1) {
                cnt[len]--;
                if (cnt[len] == 0) {
                    se.erase(len);
                }
            }
            cnt[prefix[i - 1]]++;
            cnt[prefix[i]]++;
            se.insert(prefix[i - 1]);
            se.insert(prefix[i]);
        }
        cnt[prefix[n - 2]]--;
        if (cnt[prefix[n - 2]] == 0) {
            se.erase(prefix[n - 2]);
        }
        res[n - 1] = *se.begin();
        return res;
    }
};

int main() {
    string problemName = "3598";
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
        auto words = jread_vector_string(line_in);
        auto res = sol.longestCommonPrefix(words);
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