#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
struct Data {
    int y;
    int v;
};
const int N = 5e4;
const auto cmp = [](Data& a, Data& b) { return a.y < b.y; };
#define ll long long
const int LEN = N << 1;
Data arr[2][LEN];
const int BIT = 8;
const int TOTAL_BIT = 32;
const int BUCKET_SIZE = 1 << BIT;
const int MASK2 = BUCKET_SIZE - 1;
const int BIAS = 0x80000000;
int buckets[BUCKET_SIZE];
void radixSort(int n) {
    bool p = 0;
    bool q = 1;
    for (int i = 0; i < n; i++) {
        arr[p][i].y ^= BIAS;
    }
    for (int j = 0; j < TOTAL_BIT; j += BIT) {
        for (int i = 0; i < n; i++) {
            buckets[(arr[p][i].y >> j) & MASK2]++;
        }
        for (int i = 1; i < BUCKET_SIZE; i++) {
            buckets[i] += buckets[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            arr[q][--buckets[(arr[p][i].y >> j) & MASK2]] = arr[p][i];
        }
        for (int i = 0; i < BUCKET_SIZE; i++) {
            buckets[i] = 0;
        }
        swap(p, q);
    }
    for (int i = 0; i < n; i++) {
        arr[p][i].y ^= BIAS;
    }
}

class Solution {
   public:
    double separateSquares(vector<vector<int>>& squares) {
        int n = squares.size();
        int j = 0;
        ll total = 0;
        for (int i = 0; i < n; i++) {
            int y = squares[i][1];
            int v = squares[i][2];
            arr[0][j++] = {y, v};
            arr[0][j++] = {y + v, -v};
            total += (ll)v * v;
        }
        radixSort(j);
        ll v = arr[0][0].v;
        int y = arr[0][0].y;
        ll a = 0;
        for (int i = 1; i < j; i++) {
            ll d = v * (arr[0][i].y - y);
            if (((a + d) << 1) >= total) {
                return y + ((double)total / 2 - a) / v;
            }
            a += d;
            v += arr[0][i].v;
            y = arr[0][i].y;
        }
        return 0;
    }
};

int main() {
    string problemName = "3453";
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
        auto squares = jread_vector2d(line_in);
        auto res = sol.separateSquares(squares);
        getline(file_out, line_out);
        auto ans = jread_double(line_out);
        printf("Case %d", ++caseCount);
        const double TOL = .00001;
        if (res - ans < TOL && res - ans > -TOL) {
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