#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int BIT = 8;
const int TOTAL = 32;
const int BUCKET_SIZE = 1 << BIT;
const int MASK2 = BUCKET_SIZE - 1;
const int BIAS = 0x80000000;
int buckets[BUCKET_SIZE];
void radixSort(vector<int>& arr, int n) {
    vector<int> temp(n);
    for (int i = 0; i < n; i++) {
        arr[i] ^= BIAS;
    }
    for (int j = 0; j < TOTAL; j += BIT) {
        for (int i = 0; i < n; i++) {
            buckets[(arr[i] >> j) & MASK2]++;
        }
        for (int i = 1; i < BUCKET_SIZE; i++) {
            buckets[i] += buckets[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            temp[--buckets[(arr[i] >> j) & MASK2]] = arr[i];
        }
        for (int i = 0; i < BUCKET_SIZE; i++) {
            buckets[i] = 0;
        }
        swap(arr, temp);
    }
    for (int i = 0; i < n; i++) {
        arr[i] ^= BIAS;
    }
}

class Solution {
   public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        int n = arr.size();
        radixSort(arr, n);
        int mn = INT32_MAX;
        vector<vector<int>> res(n);
        int j = 0;
        for (int i = 1; i < n; i++) {
            int d = arr[i] - arr[i - 1];
            if (mn > d) {
                j = 0;
                res[j++] = {arr[i - 1], arr[i]};
                mn = d;
            } else if (mn == d) {
                res[j++] = {arr[i - 1], arr[i]};
            }
        }
        res.resize(j);
        return res;
    }
};

int main() {
    string problemName = "1200";
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
        auto arr = jread_vector(line_in);
        auto res = sol.minimumAbsDifference(arr);
        getline(file_out, line_out);
        auto ans = jread_vector2d(line_out);
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