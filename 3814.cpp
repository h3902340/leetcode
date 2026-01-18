#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int c;
    int v;
};
const int N = 1e5;
const int BIT = 8;
const int TOTAL_BIT = 32;
const int BUCKET_SIZE = 1 << BIT;
const int MASK = BUCKET_SIZE - 1;
int buckets[BUCKET_SIZE];
Data arr[2][N];
void radixSort(int n) {
    bool p = 0;
    bool q = 1;
    for (int j = 0; j < TOTAL_BIT; j += BIT) {
        for (int i = 0; i < n; i++) {
            buckets[(arr[p][i].c >> j) & MASK]++;
        }
        for (int i = 1; i < BUCKET_SIZE; i++) {
            buckets[i] += buckets[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            arr[q][--buckets[(arr[p][i].c >> j) & MASK]] = arr[p][i];
        }
        fill(begin(buckets), end(buckets), 0);
        swap(p, q);
    }
}
int prefixMx[N];

class Solution {
   public:
    int maxCapacity(vector<int>& costs, vector<int>& capacity, int budget) {
        int n = costs.size();
        for (int i = 0; i < n; i++) {
            arr[0][i] = {costs[i], capacity[i]};
        }
        radixSort(n);
        prefixMx[0] = arr[0][0].v;
        int j = n - 1;
        int res = arr[0][0].c < budget ? arr[0][0].v : 0;
        for (int i = 1; i < n; i++) {
            prefixMx[i] = max(prefixMx[i - 1], arr[0][i].v);
            int b = budget - arr[0][i].c;
            if (b <= 0) {
                break;
            }
            while (j >= 0 && arr[0][j].c >= b) {
                j--;
            }
            if (j == -1) {
                res = max(res, arr[0][i].v);
            } else {
                int k = min(i - 1, j);
                res = max(res, arr[0][i].v + prefixMx[k]);
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3814";
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
        auto costs = jread_vector(line_in);
        getline(file_in, line_in);
        auto capacity = jread_vector(line_in);
        getline(file_in, line_in);
        auto budget = jread_int(line_in);
        auto res = sol.maxCapacity(costs, capacity, budget);
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