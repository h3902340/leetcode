#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    bool hasCycle(ListNode* head) {
        if (head == nullptr) {
            return false;
        }
        // Floyd's tortoise and hare
        ListNode* a = head;
        ListNode* b = head->next;
        while (b) {
            if (a == b) return true;
            a = a->next;
            if (b->next == nullptr) {
                return false;
            }
            b = b->next->next;
        }
        return false;
    }
};

int main() {
    string problemName = "141";
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
        auto head = jread_list(line_in);
        getline(file_in, line_in);
        auto pos = jread_int(line_in);
        int i = 0;
        auto tail = head;
        ListNode* connection = nullptr;
        while (tail) {
            if (pos == i) {
                connection = tail;
            }
            if (tail->next == nullptr) {
                tail->next = connection;
                break;
            }
            tail = tail->next;
            i++;
        }
        auto res = sol.hasCycle(head);
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