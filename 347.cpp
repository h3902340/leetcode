#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int key;
    int value;
};
unordered_map<int, int> mp;
class Solution {
   public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int n = nums.size();
        mp.clear();
        for (auto e : nums) {
            mp[e]++;
        }
        int j = 0;
        int u = mp.size();
        vector<Data> nodes(u);
        for (auto& e : mp) {
            nodes[j++] = {e.first, e.second};
        }
        kth_element(nodes, 0, u - 1, u - k);
        vector<int> res(k);
        j = 0;
        for (int i = u - k; i < u; i++) {
            res[j++] = nodes[i].key;
        }
        return res;
    }
    // O(n) expected time
    void kth_element(vector<Data>& nums, int i, int j, int k) {
        srand(time(NULL));
        int l = i + 1;
        int r = j;
        int mid = rand() % (j - i + 1) + i;
        Data p = nums[mid];
        nums[mid] = nums[i];
        while (true) {
            while (l <= r) {
                if (nums[l].value > p.value) {
                    swap(nums[l], nums[r]);
                    --r;
                } else {
                    ++l;
                }
            }
            nums[i] = nums[r];
            nums[r] = p;
            if (r == k) break;
            if (r < k) {
                i = r + 1;
            } else {
                j = r - 1;
            }
            l = i + 1;
            r = j;
            mid = rand() % (j - i + 1) + i;
            p = nums[mid];
            nums[mid] = nums[i];
        }
    }
};

int main() {
    string problemName = "347";
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
        auto nums = jread_vector(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.topKFrequent(nums, k);
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
        printf("Case %d", ++caseCount);
        if (anyOrderEqual(res, ans)) {
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