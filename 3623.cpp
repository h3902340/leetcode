#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int MOD = 1e9 + 7;
const int BUCKET_SIZE = 256;
const int MASK = 255;
const int BIAS = 0x80000000;
const int N = 1e5;
int temp[2][N];
int buckets[BUCKET_SIZE];
void radixSort(int n) {
    for (int i = 0; i < BUCKET_SIZE; i++) {
        buckets[i] = 0;
    }
    bool p = false;
    for (int i = 0; i < n; i++) {
        temp[p][i] ^= BIAS;
    }
    for (int j = 0; j < 32; j += 8) {
        for (int i = 0; i < n; i++) {
            buckets[(temp[p][i] >> j) & MASK]++;
        }
        for (int i = 1; i < BUCKET_SIZE; i++) {
            buckets[i] += buckets[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            temp[!p][--buckets[(temp[p][i] >> j) & MASK]] = temp[p][i];
        }
        for (int i = 0; i < BUCKET_SIZE; i++) {
            buckets[i] = 0;
        }
        p = !p;
    }
    for (int i = 0; i < n; i++) {
        temp[p][i] ^= BIAS;
    }
}

class Solution {
   public:
    int countTrapezoids(vector<vector<int>>& points) {
        int n = points.size();
        for (int i = 0; i < n; i++) {
            temp[0][i] = points[i][1];
        }
        radixSort(n);
        ll res = 0;
        ll acc = 0;
        int i = 0;
        while (i < n) {
            int b = temp[0][i];
            ll c = 1;
            i++;
            while (i < n) {
                if (temp[0][i] == b) {
                    c++;
                    i++;
                } else {
                    break;
                }
            }
            ll a = c * (c - 1) >> 1;
            res += acc * a;
            acc += a;
        }
        return res % MOD;
    }
};

int main() {
    string problemName = "3623";
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
        auto points = jread_vector2d(line_in);
        auto res = sol.countTrapezoids(points);
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