#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int i;
    int c;
};
const int N = 5000;
Data q[N];
bool vis[N];
class Solution {
   public:
    int ladderLength(string beginWord, string endWord,
                     vector<string>& wordList) {
        int n = wordList.size();
        int m = beginWord.size();
        unordered_map<string, vector<int>> se;
        for (int i = 0; i < n; i++) {
            vis[i] = false;
            for (int j = 0; j < m; j++) {
                string t = wordList[i];
                t[j] = 0;
                se[t].push_back(i);
            }
        }
        wordList.push_back(beginWord);
        int l = 0;
        int r = 0;
        q[r++] = {n, 1};
        while (l < r) {
            Data a = q[l++];
            if (wordList[a.i] == endWord) {
                return a.c;
            }
            for (int j = 0; j < m; j++) {
                string t = wordList[a.i];
                t[j] = 0;
                if (se.count(t)) {
                    for (auto e : se[t]) {
                        if (vis[e]) {
                            continue;
                        }
                        q[r++] = {e, a.c + 1};
                        vis[e] = true;
                    }
                }
            }
        }
        return 0;
    }
};

int main() {
    string problemName = "127";
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
        auto beginWord = jread_string(line_in);
        getline(file_in, line_in);
        auto endWord = jread_string(line_in);
        getline(file_in, line_in);
        auto wordList = jread_vector_string(line_in);
        auto res = sol.ladderLength(beginWord, endWord, wordList);
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