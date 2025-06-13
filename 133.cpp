#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    Node* cloneGraph(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        vector<Node*> arr;
        stack<Node*> st;
        st.push(node);
        unordered_map<int, bool> vis;
        while (!st.empty()) {
            Node* t = st.top();
            st.pop();
            if (vis[t->val]) continue;
            int i = t->val - 1;
            while (i >= arr.size()) {
                arr.push_back(new Node());
            }
            arr[i]->val = t->val;
            vis[t->val] = true;
            for (auto& e : t->neighbors) {
                if (vis[e->val]) continue;
                st.push(e);
            }
        }
        st.push(node);
        vis.clear();
        while (!st.empty()) {
            Node* t = st.top();
            st.pop();
            if (vis[t->val]) continue;
            vis[t->val] = true;
            for (auto& e : t->neighbors) {
                arr[t->val - 1]->neighbors.push_back(arr[e->val - 1]);
                if (vis[e->val]) continue;
                st.push(e);
            }
        }
        return arr[0];
    }
};

int main() {
    string problemName = "133";
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
        auto nodes = jread_graph(line_in);
        Node* node = nullptr;
        if (nodes.size() > 0) {
            node = nodes[0];
        }
        auto res = sol.cloneGraph(node);
        getline(file_out, line_out);
        auto anss = jread_graph(line_out);
        Node* ans = nullptr;
        if (anss.size() > 0) {
            ans = anss[0];
        }
        printf("Case %d", ++caseCount);
        if (graphEqual(res, ans)) {
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