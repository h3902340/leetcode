#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Task {
    int userId;
    int taskId;
    int priority;
};
const int TASK_ID = 1e5;
const int USER_NIL = -1;
int taskToUser[TASK_ID + 1];
int taskToPriority[TASK_ID + 1];
// builtin priority_queue is better
Task heap[TASK_ID + 1];
int n;
class TaskManager {
   public:
    TaskManager(vector<vector<int>>& tasks) {
        n = tasks.size();
        for (int i = n - 1; i >= 0; i--) {
            int userId = tasks[i][0];
            int taskId = tasks[i][1];
            int priority = tasks[i][2];
            heap[i].userId = userId;
            heap[i].taskId = taskId;
            heap[i].priority = priority;
            taskToUser[taskId] = userId;
            taskToPriority[taskId] = priority;
            down(i);
        }
    }
    void down(int i) {
        while (true) {
            int l = (i << 1) + 1;
            if (l >= n) {
                return;
            }
            int r = l + 1;
            int bigChild = l;
            if (r < n) {
                if (isLessThan(heap[l], heap[r])) {
                    bigChild = r;
                }
            }
            if (isLessThan(heap[i], heap[bigChild])) {
                swap(heap[i], heap[bigChild]);
                i = bigChild;
            } else {
                return;
            }
        }
    }
    void up(int i) {
        while (i != 0) {
            int bigChild = i;
            if ((i & 1) == 0) {
                if (isLessThan(heap[i], heap[i - 1])) {
                    bigChild--;
                }
            }
            int p = (i - 1) >> 1;
            if (isLessThan(heap[p], heap[bigChild])) {
                swap(heap[p], heap[bigChild]);
                i = p;
            } else {
                return;
            }
        }
    }
    bool isLessThan(Task& a, Task& b) {
        if (a.priority == b.priority) {
            return a.taskId < b.taskId;
        }
        return a.priority < b.priority;
    }
    void add(int userId, int taskId, int priority) {
        heap[n] = {userId, taskId, priority};
        up(n);
        n++;
        taskToUser[taskId] = userId;
        taskToPriority[taskId] = priority;
    }

    void edit(int taskId, int newPriority) {
        heap[n] = {taskToUser[taskId], taskId, newPriority};
        up(n);
        n++;
        taskToPriority[taskId] = newPriority;
    }

    void rmv(int taskId) { taskToUser[taskId] = USER_NIL; }

    int execTop() {
        while (n != 0) {
            Task t = heap[0];
            heap[0] = heap[--n];
            down(0);
            if (taskToUser[t.taskId] == USER_NIL) {
                continue;
            }
            if (taskToUser[t.taskId] != t.userId) {
                continue;
            }
            if (taskToPriority[t.taskId] != t.priority) {
                continue;
            }
            rmv(t.taskId);
            return t.userId;
        }
        return USER_NIL;
    }
};

int main() {
    string problemName = "3408";
    auto begin = jtimer();
    vector<string> cmd = {"TaskManager", "add", "edit",   "execTop",
                          "rmv",         "add", "execTop"};
    vector<vector<int>> tasks = {{1, 101, 10}, {2, 102, 20}, {3, 103, 15}};
    vector<vector<int>> add = {{}, {2, 102, 20}, {}, {}, {}, {5, 105, 15}, {}};
    vector<vector<int>> edit = {{}, {}, {102, 8}, {}, {}, {}, {}};
    vector<int> rmv = {0, 0, 0, 0, 101, 0, 0};
    vector<int> ans = {0, 0, 0, 3, 0, 0, 5};
    TaskManager sol(tasks);
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    printf("Case %d\n", ++caseCount);
    for (int i = 0; i < cmd.size(); i++) {
        string& c = cmd[i];
        if (c == "TaskManager") {
            continue;
        }
        if (c == "add") {
            sol.add(add[i][0], add[i][1], add[i][2]);
            continue;
        }
        if (c == "edit") {
            sol.edit(edit[i][0], edit[i][1]);
            continue;
        }
        if (c == "rmv") {
            sol.rmv(rmv[i]);
            continue;
        }
        if (c == "execTop") {
            int res = sol.execTop();
            if (res != ans[i]) {
                printf("wrong i:%d\n", i);
                printf("res:%d,ans[i]:%d\n", res, ans[i]);
                allPass = false;
                break;
            }
        }
    }
    if (allPass) {
        passCount++;
        printf("%sALL CORRECT [%d/%d]\n%s", KGRN, passCount, caseCount, KNRM);
    } else {
        printf("%sWRONG ANSWER [%d/%d]\n%s", KRED, passCount, caseCount, KNRM);
    }
    auto end = jtimer();
    jprint_time(begin, end);
    return 0;
}