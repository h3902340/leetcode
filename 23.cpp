#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int NUMLO = -1e4;
const int NUMHI = 1e4;
int cnt[NUMHI - NUMLO + 1];

class Solution {
   public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.size() == 0) {
            return nullptr;
        }
        memset(cnt, 0, sizeof(cnt));
        int min = NUMHI + 1;
        int max = NUMLO - 1;
        for (auto& l : lists) {
            while (l != nullptr) {
                cnt[l->val - NUMLO]++;
                if (min > l->val) {
                    min = l->val;
                }
                if (max < l->val) {
                    max = l->val;
                }
                l = l->next;
            }
        }
        if (min == NUMHI + 1) {
            return nullptr;
        }
        ListNode* root = new ListNode(min);
        ListNode* cur = root;
        cnt[min - NUMLO]--;
        for (int i = min; i <= max; i++) {
            for (int j = 0; j < cnt[i - NUMLO]; j++) {
                cur->next = new ListNode(i);
                cur = cur->next;
            }
        }
        return root;
    }
};

int main() {
    string problemName = "23";
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
        auto lists = jread_vector_list(line_in);
        auto res = sol.mergeKLists(lists);
        getline(file_out, line_out);
        auto ans = jread_list(line_out);
        printf("Case %d", ++caseCount);
        if (listEqual(res, ans)) {
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