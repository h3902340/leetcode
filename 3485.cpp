#include <map>
#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int LENSUM = 1e5;
struct Trie {
    int cnt[26];
    int idx[26];
};
Trie arr[LENSUM];
const int WORDLEN = 1e4;
int fre[WORDLEN + 1];

class Solution {
   public:
    vector<int> longestCommonPrefix(vector<string> &words, int k) {
        int n = words.size();
        int maxLen = 0;
        for (int i = 0; i < 26; i++) {
            arr[0].cnt[i] = 0;
            arr[0].idx[i] = -1;
        }
        for (auto &w : words) {
            if (maxLen < w.size()) {
                maxLen = w.size();
            }
        }
        for (int i = 1; i <= maxLen; i++) {
            fre[i] = 0;
        }
        int r = 0;
        for (auto &w : words) {
            int index = 0;
            for (int j = 0; j < w.size(); j++) {
                int c = w[j] - 'a';
                arr[index].cnt[c]++;
                if (arr[index].cnt[c] >= k) {
                    fre[j + 1]++;
                }
                if (arr[index].idx[c] == -1) {
                    r++;
                    arr[index].idx[c] = r;
                    index = r;
                    for (int i = 0; i < 26; i++) {
                        arr[index].cnt[i] = 0;
                        arr[index].idx[i] = -1;
                    }
                } else {
                    index = arr[index].idx[c];
                }
            }
        }
        vector<int> res(n);
        for (int i = 0; i < n; i++) {
            string &w = words[i];
            int mx = 0;
            for (int j = maxLen; j > w.size(); j--) {
                if (fre[j] > 0) {
                    mx = j;
                    break;
                }
            }
            if (mx > 0) {
                res[i] = mx;
                continue;
            }
            int index = 0;
            for (int j = 0; j < w.size(); j++) {
                int c = w[j] - 'a';
                if (arr[index].cnt[c] < k) {
                    if (fre[j + 1] == 0) {
                        break;
                    }
                }
                if (arr[index].cnt[c] == k) {
                    if (fre[j + 1] == 1) {
                        break;
                    }
                }
                index = arr[index].idx[c];
                mx = j + 1;
            }
            res[i] = mx;
        }
        return res;
    }
};

int main() {
    string problemName = "3485";
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
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.longestCommonPrefix(words, k);
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
        jprint_vector(res, "res");
        jprint_vector(ans, "ans");
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