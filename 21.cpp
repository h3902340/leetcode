#include <vector>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
    {
        ListNode *head = new ListNode();
        ListNode *current = head;
        while (list1 && list2)
        {
            if (list1->val > list2->val)
            {
                current->next = list2;
                list2 = list2->next;
            }
            else
            {
                current->next = list1;
                list1 = list1->next;
            }
            current = current->next;
        }
        if (list1)
        {
            current->next = list1;
        }
        else
        {
            current->next = list2;
        }
        return head->next;
    }
};

int main()
{
    vector<int> list1Int = {1, 2, 4};
    vector<int> list2Int = {1, 3, 4};
    ListNode *list1 = new ListNode(list1Int[0]);
    ListNode *list2 = new ListNode(list2Int[0]);
    ListNode *list1Current = list1;
    ListNode *list2Current = list2;
    for (int i = 1; i < list1Int.size(); i++)
    {
        list1Current->next = new ListNode(list1Int[i]);
        list1Current = list1Current->next;
    }
    for (int i = 1; i < list2Int.size(); i++)
    {
        list2Current->next = new ListNode(list2Int[i]);
        list2Current = list2Current->next;
    }
    Solution sol;
    ListNode *ans = sol.mergeTwoLists(list1, list2);
    printf("ans = [%d", ans->val);
    ans = ans->next;
    while (ans)
    {
        printf(", %d", ans->val);
        ans = ans->next;
    }
    printf("]\n"); // [1, 1, 2, 3, 4, 4]
    return 0;
}