#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int MMAX = 5e4;
const int BUCKET_SIZE = 256;
const int MASK = 255;
int q[MMAX];
int buckets[BUCKET_SIZE];
class Solution {
   public:
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills,
                      int strength) {
        int n = tasks.size();
        int m = workers.size();
        radixSort(tasks);
        radixSortReverse(workers);
        int res = 0;
        int l = 0;
        int r = min(m, n);
        int x = 0;
        int y = 0;
        int j = 0;
        while (l <= r) {
            int p = pills;
            int mid = (l + r) >> 1;
            int i = mid - 1;
            for (; i >= 0; i--) {
                int t = tasks[i];
                int tpill = t - strength;
                while (j < mid && workers[j] >= tpill) {
                    q[y++] = workers[j++];
                }
                if (x == y) break;
                if (q[x] >= t) {
                    x++;
                } else if (p > 0) {
                    y--;
                    p--;
                } else {
                    break;
                }
            }
            x = 0;
            if (i == -1) {
                l = mid + 1;
                res = mid;
                y = 0;
                j = 0;
            } else {
                r = mid - 1;
                y += pills - p;
            }
        }
        return res;
    }

   private:
    void radixSort(vector<int>& nums) {
        int n = nums.size();
        vector<int> temp(n);
        int max = BUCKET_SIZE - 1;
        for (int j = 0; j < 32; j += 8) {
            for (int i = 0; i <= max; i++) {
                buckets[i] = 0;
            }
            for (auto& e : nums) {
                int index = (e >> j) & MASK;
                buckets[index]++;
                if (max < index) {
                    max = index;
                }
            }
            for (int i = 1; i <= max; i++) {
                buckets[i] += buckets[i - 1];
            }
            for (int i = n - 1; i >= 0; i--) {
                temp[--buckets[(nums[i] >> j) & MASK]] = nums[i];
            }
            nums.swap(temp);
        }
    }
    void radixSortReverse(vector<int>& nums) {
        int n = nums.size();
        vector<int> temp(n);
        int max = BUCKET_SIZE - 1;
        for (int j = 0; j < 32; j += 8) {
            for (int i = 0; i <= max; i++) {
                buckets[i] = 0;
            }
            for (auto& e : nums) {
                int index = (e >> j) & MASK;
                buckets[index]++;
                if (max < index) {
                    max = index;
                }
            }
            for (int i = max; i >= 1; i--) {
                buckets[i - 1] += buckets[i];
            }
            for (int i = n - 1; i >= 0; i--) {
                temp[--buckets[(nums[i] >> j) & MASK]] = nums[i];
            }
            nums.swap(temp);
        }
    }
};

int main() {
    string problemName = "2071";
    auto begin = jtimer();
    Solution sol;
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    string line_in1;
    string line_in2;
    string line_in3;
    string line_in4;
    string line_out;
    while (getline(file_in, line_in1)) {
        auto tasks = jread_vector(line_in1);
        getline(file_in, line_in2);
        auto workers = jread_vector(line_in2);
        getline(file_in, line_in3);
        auto pills = jread_int(line_in3);
        getline(file_in, line_in4);
        auto strength = jread_int(line_in4);
        int res = sol.maxTaskAssign(tasks, workers, pills, strength);
        getline(file_out, line_out);
        int ans = jread_int(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        printf("tasks = %s\n", line_in1.c_str());
        printf("workers = %s\n", line_in2.c_str());
        printf("pills = %s\n", line_in3.c_str());
        printf("strength = %s\n", line_in4.c_str());
        jprint_int(res, "res");
        jprint_int(ans, "ans");
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