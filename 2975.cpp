#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int MOD = 1e9 + 7;
const int N = 602;
const int BIT = 8;
const int TOTAL_BIT = 32;
const int BUCKET_SIZE = 1 << BIT;
const int MASK = BUCKET_SIZE - 1;
int buckets[BUCKET_SIZE];
vector<int> temp(N);
void radixSort(vector<int>& nums, int n) {
    for (int j = 0; j < TOTAL_BIT; j += BIT) {
        for (int i = 0; i < n; i++) {
            buckets[(nums[i] >> j) & MASK]++;
        }
        for (int i = 1; i < BUCKET_SIZE; i++) {
            buckets[i] += buckets[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            temp[--buckets[(nums[i] >> j) & MASK]] = nums[i];
        }
        fill(begin(buckets), end(buckets), 0);
        swap(nums, temp);
    }
}
const int TABLE_SIZE = N * N;
int se[TABLE_SIZE];
void init() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        se[i] = 0;
    }
}
void insert(int a) {
    int k = a % TABLE_SIZE;
    while (se[k]) {
        if (se[k] == a) {
            return;
        }
        k++;
        if (k == TABLE_SIZE) {
            k = 0;
        }
    }
    se[k] = a;
}
bool search(int a) {
    int k = a % TABLE_SIZE;
    while (se[k] && se[k] != a) {
        k++;
        if (k == TABLE_SIZE) {
            k = 0;
        }
    }
    return se[k] == a;
}

class Solution {
   public:
    int maximizeSquareArea(int m, int n, vector<int>& hFences,
                           vector<int>& vFences) {
        hFences.push_back(1);
        hFences.push_back(m);
        vFences.push_back(1);
        vFences.push_back(n);
        int x = hFences.size();
        int y = vFences.size();
        radixSort(hFences, x);
        radixSort(vFences, y);
        init();
        for (int i = 0; i < x; i++) {
            for (int j = i + 1; j < x; j++) {
                insert(hFences[j] - hFences[i]);
            }
        }
        int res = 0;
        for (int l = y - 1; l >= 1; l--) {
            bool allSmaller = true;
            for (int i = 0; i + l < y; i++) {
                int d = vFences[i + l] - vFences[i];
                if (res < d) {
                    allSmaller = false;
                    if (search(d)) {
                        res = d;
                    }
                }
            }
            if (allSmaller) {
                break;
            }
        }
        if (res == 0) {
            return -1;
        }
        return (ll)res * res % MOD;
    }
};

int main() {
    string problemName = "2975";
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
        auto m = jread_int(line_in);
        getline(file_in, line_in);
        auto n = jread_int(line_in);
        getline(file_in, line_in);
        auto hFences = jread_vector(line_in);
        getline(file_in, line_in);
        auto vFences = jread_vector(line_in);
        auto res = sol.maximizeSquareArea(m, n, hFences, vFences);
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