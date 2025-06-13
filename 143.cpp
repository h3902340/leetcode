#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    void reorderList(ListNode *head) {
        ListNode *a = head;
        ListNode *b = head;
        while (b->next) {
            a = a->next;
            b = b->next->next;
            if (b == nullptr) break;
        }
        b = nullptr;
        while (a) {
            ListNode *temp = a->next;
            a->next = b;
            b = a;
            a = temp;
        }
        a = head;
        while (a->next) {
            ListNode *temp = a->next;
            a->next = b;
            a = temp;
            if (b == nullptr) {
                break;
            }
            temp = b->next;
            b->next = a;
            b = temp;
        }
    }
};

int main() {
    string problemName = "143";
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
        sol.reorderList(head);
        getline(file_out, line_out);
        auto ans = jread_list(line_out);
        printf("Case %d", ++caseCount);
        if (listEqual(head, ans)) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint(head, "res");
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