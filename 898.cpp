#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 5e4;
const int LEN = N << 5;
const int BUCKET_SIZE = 256;
const int MASK = 255;
int buckets[BUCKET_SIZE];
vector<int> temp(LEN);
vector<int> all(LEN);
void radixSort(vector<int>& nums, int n) {
    for (int j = 0; j < 32; j += 8) {
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
        nums.swap(temp);
    }
}

class Solution {
   public:
    int subarrayBitwiseORs(vector<int>& arr) {
        int n = arr.size();
        int k = 0;
        for (int i = 0; i < n; i++) {
            all[k++] = arr[i];
            int a = 0;
            for (int j = i - 1; j >= 0; j--) {
                a |= arr[j];
                int b = a | arr[i];
                if (b == a) {
                    break;
                }
                all[k++] = b;
            }
        }
        radixSort(all, k);
        int c = 1;
        int cur = all[0];
        for (int i = 1; i < k; i++) {
            if (cur == all[i]) {
                continue;
            }
            cur = all[i];
            c++;
        }
        return c;
    }
};

int main() {
    string problemName = "898";
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
        auto res = sol.subarrayBitwiseORs(arr);
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