#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 500;
const int BIT = 10;
const int BUCKET_SIZE = 1 << BIT;
const int MASK = BUCKET_SIZE - 1;
const int BITX = 11;
const int BITSIGN = BITX << 1;
// y may actually needs 22 bits
const int BITY = 18;
const int BITPOS = BITX + BITY;
const int MX = (1 << BITX) - 1;
const int MY = (1 << BITY) - 1;
const ll MPOS = (1L << BITPOS) - 1;
const int MSLOPE = BITPOS + BITX;
const ll MG = MPOS | ((1L << (BITSIGN + 1)) - 1) << MSLOPE;
ll temp[2][N * (N - 1) >> 1];
int buckets[BUCKET_SIZE];
int gcd(int a, int b) {
    int atz = __builtin_ctz(a);
    int btz = __builtin_ctz(b);
    int d = min(atz, btz);
    a >>= atz;
    b >>= btz;
    while (a != b) {
        if (a < b) {
            swap(a, b);
        }
        a -= b;
        a >>= __builtin_ctz(a);
    }
    return a <<= d;
}
void radixSort(int n) {
    bool p = false;
    for (int j = 0; j < 64; j += BIT) {
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
}

class Solution {
   public:
    int countTrapezoids(vector<vector<int>>& points) {
        int n = points.size();
        int k = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int x1 = points[i][0];
                int y1 = points[i][1];
                int x2 = points[j][0];
                int y2 = points[j][1];
                int a = abs(x1 - x2);
                int b = abs(y1 - y2);
                int g = 0;
                if (a == 0 || b == 0) {
                    if (a == 0) {
                        g = b;
                        b = 1;
                        y1 = 0;
                    } else {
                        g = a;
                        a = 1;
                        x1 = 0;
                    }
                    int slope = a | (b << BITX);
                    ll pos = (x1 & MX) | ((ll)(y1 & MY) << BITX);
                    temp[0][k] =
                        pos | ((ll)g << BITPOS) | ((ll)slope << MSLOPE);
                    k++;
                    continue;
                }
                g = gcd(a, b);
                a /= g;
                b /= g;
                bool sign = ((x1 - x2) ^ (y1 - y2)) < 0;
                int q = x1 / a;
                x1 -= q * a;
                if (sign) {
                    y1 += q * b;
                } else {
                    y1 -= q * b;
                }
                if (x1 < 0) {
                    x1 += a;
                    if (sign) {
                        y1 -= b;
                    } else {
                        y1 += b;
                    }
                }
                int slope = a | (b << BITX) | (sign << BITSIGN);
                ll pos = (x1 & MX) | ((ll)(y1 & MY) << BITX);
                temp[0][k] = pos | ((ll)g << BITPOS) | ((ll)slope << MSLOPE);
                k++;
            }
        }
        radixSort(k);
        int parallel = 0;
        int i = 0;
        while (i < k) {
            ll pos = temp[0][i] & MPOS;
            ll l = temp[0][i] >> BITPOS;
            i++;
            int pre = 1;
            int cur = 0;
            while (i < k) {
                ll pos2 = temp[0][i] & MPOS;
                ll l2 = temp[0][i] >> BITPOS;
                if (l == l2 && pos == pos2) {
                    pre++;
                } else {
                    break;
                }
                i++;
            }
            if (i == k) {
                break;
            }
            pos = temp[0][i] & MPOS;
            while (i < k) {
                ll pos2 = temp[0][i] & MPOS;
                ll l2 = temp[0][i] >> BITPOS;
                if (l2 == l) {
                    if (pos != pos2) {
                        pos = pos2;
                        pre += cur;
                        cur = 0;
                    }
                    cur++;
                    parallel += pre;
                } else {
                    break;
                }
                i++;
            }
        }
        parallel >>= 1;
        for (int i = 0; i < k; i++) {
            temp[0][i] &= MG;
        }
        radixSort(k);
        int res = 0;
        i = 0;
        while (i < k) {
            ll pos = temp[0][i] & MPOS;
            ll slope = temp[0][i] >> MSLOPE;
            i++;
            int pre = 1;
            int cur = 0;
            while (i < k) {
                ll pos2 = temp[0][i] & MPOS;
                ll slope2 = temp[0][i] >> MSLOPE;
                if (slope == slope2 && pos == pos2) {
                    pre++;
                } else {
                    break;
                }
                i++;
            }
            if (i == k) {
                break;
            }
            pos = temp[0][i] & MPOS;
            while (i < k) {
                ll pos2 = temp[0][i] & MPOS;
                ll slope2 = temp[0][i] >> MSLOPE;
                if (slope2 == slope) {
                    if (pos != pos2) {
                        pos = pos2;
                        pre += cur;
                        cur = 0;
                    }
                    cur++;
                    res += pre;
                } else {
                    break;
                }
                i++;
            }
        }
        return res - parallel;
    }
};

int main() {
    string problemName = "3625";
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