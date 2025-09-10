#include <bitset>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 500;
const int M = 500;
bitset<N> lang[M];
bool need[M];
int know[N];

class Solution {
   public:
    int minimumTeachings(int n, vector<vector<int>>& languages,
                         vector<vector<int>>& friendships) {
        int m = languages.size();
        for (int i = 0; i < m; i++) {
            lang[i] = 0;
            need[i] = false;
        }
        for (int i = 0; i < n; i++) {
            know[i] = 0;
        }
        for (int i = 0; i < m; i++) {
            auto& l = languages[i];
            for (auto& e : l) {
                lang[i][e - 1] = 1;
            }
        }
        int needCnt = 0;
        for (auto& f : friendships) {
            int a = f[0] - 1;
            int b = f[1] - 1;
            if ((lang[a] & lang[b]).any()) {
                continue;
            }
            if (!need[a]) {
                for (int i = 0; i < languages[a].size(); i++) {
                    know[languages[a][i] - 1]++;
                }
                need[a] = true;
                needCnt++;
            }
            if (!need[b]) {
                for (int i = 0; i < languages[b].size(); i++) {
                    know[languages[b][i] - 1]++;
                }
                need[b] = true;
                needCnt++;
            }
        }
        int max = 0;
        for (int i = 0; i < n; i++) {
            if (max < know[i]) {
                max = know[i];
            }
        }
        return needCnt - max;
    }
};

int main() {
    string problemName = "1733";
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
        auto n = jread_int(line_in);
        getline(file_in, line_in);
        auto languages = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto friendships = jread_vector2d(line_in);
        auto res = sol.minimumTeachings(n, languages, friendships);
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