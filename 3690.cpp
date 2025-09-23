#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int v;
    int i;
};
const int N = 6;
const int ST = 720;  // 6!
const int STEPS = 1 << (N * 3);
const int LO = -1e5;
const int HI = 1e5;
const int MP = HI - LO + 1;
Data st[ST];
bool steps[STEPS];
int mp[MP];
// time: O(N!), space: O(N!)
class Solution {
   public:
    int minSplitMerge(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int n3 = n * 3;
        int b = 0;
        int idx = 0;
        for (int i = 0; i < MP; i++) {
            mp[i] = -1;
        }
        for (int i = 0; i < n; i++) {
            int key = nums2[i] - LO;
            if (mp[key] == -1) {
                mp[key] = idx++;
            }
            b = (b << 3) + mp[key];
        }
        int a = 0;
        for (int i = 0; i < n; i++) {
            int key = nums1[i] - LO;
            a = (a << 3) + mp[key];
        }
        if (a == b) {
            return 0;
        }
        for (int i = 0; i < STEPS; i++) {
            steps[i] = false;
        }
        steps[b] = true;
        int l = 0;
        int r = 0;
        st[r++] = {b, 0};
        while (r > l) {
            Data t = st[l++];
            b = t.v;
            int step = t.i + 1;
            for (int i = 0; i < n3; i += 3) {
                for (int j = i + 3; j < n3; j += 3) {
                    for (int k = j + 3; k <= n3; k += 3) {
                        int c = (b & ((1 << n3) - (1 << k))) +
                                ((b & ((1 << k) - (1 << j))) >> (j - i)) +
                                ((b & ((1 << j) - (1 << i))) << (k - j)) +
                                (b & ((1 << i) - 1));
                        if (c == a) {
                            return step;
                        }
                        if (steps[c]) {
                            continue;
                        }
                        steps[c] = true;
                        st[r++] = {c, step};
                    }
                }
            }
        }
        return -1;
    }
};

int main() {
    string problemName = "3690";
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
        auto nums1 = jread_vector(line_in);
        getline(file_in, line_in);
        auto nums2 = jread_vector(line_in);
        auto res = sol.minSplitMerge(nums1, nums2);
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