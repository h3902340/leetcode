#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 7;
const int C = 26;
const char A = 'A';
int fre[N + 1];
int mp[C];

class Solution {
   public:
    int numTilePossibilities(string tiles) {
        int n = tiles.size();
        for (int i = 0; i < n; i++) {
            tiles[i] -= A;
            mp[tiles[i]] = -1;
        }
        int j = 1;
        for (int i = 0; i < n; i++) {
            if (mp[tiles[i]] == -1) {
                mp[tiles[i]] = j++;
            }
        }
        unordered_set<int> seen;
        for (int i = 0; i < n; i++) {
            tiles[i] = mp[tiles[i]];
            fre[tiles[i]]++;
        }
        for (int i = 1; i < j; i++) {
            fre[i] += fre[i - 1];
        }
        string temp(n, 0);
        for (int i = n - 1; i >= 0; i--) {
            temp[--fre[tiles[i]]] = tiles[i];
        }
        for (int i = 0; i < j; i++) {
            fre[i] = 0;
        }
        swap(tiles, temp);
        int res = 0;
        int cap = 1 << n;
        for (int m = 1; m < cap; m++) {
            int v = 0;
            for (int i = 0; i < n; i++) {
                if (m & (1 << i)) {
                    fre[tiles[i]]++;
                    v = v * j + tiles[i];
                }
            }
            if (seen.count(v)) {
                for (int i = 0; i < n; i++) {
                    if (m & (1 << i)) {
                        fre[tiles[i]] = 0;
                    }
                }
                continue;
            }
            seen.insert(v);
            int tot = 1;
            int a = 0;
            for (int i = 0; i < n; i++) {
                if (m & (1 << i)) {
                    for (int j = 1; j <= fre[tiles[i]]; j++) {
                        a++;
                        tot = tot * a / j;
                    }
                    fre[tiles[i]] = 0;
                }
            }
            res += tot;
        }
        return res;
    }
};

int main() {
    string problemName = "1079";
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
        auto tiles = jread_string(line_in);
        auto res = sol.numTilePossibilities(tiles);
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