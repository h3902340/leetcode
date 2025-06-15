#include <queue>
#include <set>
#include <unordered_set>
#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    long long sum;
    int index;
    int modCount;
};

const int NMAX = 1e5;
long long temp[NMAX];
int pre[NMAX];
int nxt[NMAX];
int modCount[NMAX - 1];

class Solution {
   public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();
        auto cmp = [](Data a, Data b) {
            if (a.sum == b.sum) {
                return a.index > b.index;
            }
            return a.sum > b.sum;
        };
        priority_queue<Data, vector<Data>, decltype(cmp)> pq(cmp);
        int cnt = 0;
        for (int i = 0; i < n - 1; i++) {
            pre[i] = i - 1;
            nxt[i] = i + 1;
            if (nums[i] > nums[i + 1]) {
                cnt++;
            }
            Data node = {nums[i] + nums[i + 1], i, 0};
            pq.emplace(node);
            modCount[i] = 0;
            temp[i] = nums[i];
        }
        pre[n - 1] = n - 2;
        nxt[n - 1] = -1;
        temp[n - 1] = nums[n - 1];
        int ans = 0;
        while (cnt > 0) {
            Data t = pq.top();
            pq.pop();
            if (t.modCount != modCount[t.index]) continue;
            ans++;
            int left = pre[t.index];
            int right = nxt[t.index];
            int rr = nxt[right];
            if (temp[t.index] > temp[right]) {
                cnt--;
            }
            long long mergedSum = temp[t.index] + temp[right];
            if (left != -1) {
                if (temp[left] > temp[t.index]) {
                    if (temp[left] <= mergedSum) {
                        cnt--;
                    }
                } else {
                    if (temp[left] > mergedSum) {
                        cnt++;
                    }
                }
                modCount[left]++;
                nxt[left] = right;
                Data node = {temp[left] + mergedSum, left, modCount[left]};
                pq.emplace(node);
            }
            if (rr != -1) {
                if (temp[right] > temp[rr]) {
                    if (mergedSum <= temp[rr]) {
                        cnt--;
                    }
                } else {
                    if (mergedSum > temp[rr]) {
                        cnt++;
                    }
                }
                modCount[right]++;
                Data node = {mergedSum + temp[rr], right, modCount[right]};
                pq.emplace(node);
            }
            temp[right] = mergedSum;
            pre[right] = left;
        }
        return ans;
    }
};

int main() {
    string problemName = "3510";
    auto begin = jtimer();
    Solution sol;
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    string line_in1;
    string line_out;
    while (getline(file_in, line_in1)) {
        auto nums = jread_vector(line_in1);
        jprint(nums, "nums");
        auto res = sol.minimumPairRemoval(nums);
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