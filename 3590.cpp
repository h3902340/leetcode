#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 5e4;
const int M = N - 1;
const int C = 2;
const int BIT = 17;
int to[M << 1];
int nxt[M << 1];
int head[N];
int eCnt;
void addEdge(int u, int v) {
    to[eCnt] = v;
    nxt[eCnt] = head[u];
    head[u] = eCnt++;
}
void initGraph(int n) {
    eCnt = 0;
    for (int i = 0; i < n; i++) {
        head[i] = -1;
    }
}
struct Query {
    int idx;
    int k;
};
vector<Query> que[N];
int lev[N];
struct TrieNode {
    int child[C];
    int cnt;
};
vector<TrieNode> nodes;
class Trie {
    int root;

   public:
    Trie& operator=(const Trie& a) {
        root = a.root;
        return *this;
    }
    void init() {
        root = nodes.size();
        nodes.push_back(create());
    }
    TrieNode create() {
        TrieNode a;
        for (int i = 0; i < C; i++) {
            a.child[i] = -1;
        }
        a.cnt = 0;
        return a;
    }
    void insert(int a) {
        if (has(a)) {
            return;
        }
        int id = root;
        nodes[id].cnt++;
        for (int i = BIT - 1; i >= 0; i--) {
            int c = (a >> i) & 1;
            if (nodes[id].child[c] == -1) {
                nodes[id].child[c] = nodes.size();
                nodes.push_back(create());
            }
            id = nodes[id].child[c];
            nodes[id].cnt++;
        }
    }
    bool has(int a) {
        int id = root;
        for (int i = BIT - 1; i >= 0; i--) {
            int c = (a >> i) & 1;
            if (nodes[id].child[c] == -1) {
                return false;
            }
            id = nodes[id].child[c];
        }
        return true;
    }
    void merge(Trie& a) { mergeNode(root, a.root); }
    int size() { return nodes[root].cnt; }
    int kth_element(int k) {
        int id = root;
        int res = 0;
        for (int b = BIT - 1; b >= 0; b--) {
            int s = 0;
            for (int i = 0; i < C; i++) {
                int t = s;
                if (nodes[id].child[i] != -1) {
                    s += nodes[nodes[id].child[i]].cnt;
                }
                if (s >= k) {
                    k -= t;
                    id = nodes[id].child[i];
                    res |= (i << b);
                    break;
                }
            }
        }
        return res;
    }

   private:
    int mergeNode(int i, int j) {
        int uni = 0;
        bool bottom = true;
        for (int k = 0; k < C; k++) {
            if (nodes[j].child[k] == -1) {
                continue;
            }
            bottom = false;
            if (nodes[i].child[k] == -1) {
                nodes[i].child[k] = nodes[j].child[k];
                uni += nodes[nodes[j].child[k]].cnt;
            } else {
                uni += mergeNode(nodes[i].child[k], nodes[j].child[k]);
            }
        }
        if (bottom && nodes[i].cnt == 0 && nodes[j].cnt == 1) {
            uni++;
        }
        nodes[i].cnt += uni;
        return uni;
    }
};
Trie tree[N];

class Solution {
   public:
    vector<int> kthSmallest(vector<int>& par, vector<int>& vals,
                            vector<vector<int>>& queries) {
        int n = par.size();
        int q = queries.size();
        initGraph(n);
        nodes.clear();
        for (int i = 0; i < n; i++) {
            que[i].clear();
            if (par[i] != -1) {
                addEdge(i, par[i]);
                addEdge(par[i], i);
            }
            tree[i].init();
        }
        for (int i = 0; i < q; i++) {
            que[queries[i][0]].push_back({i, queries[i][1]});
        }
        lev[0] = 0;
        int l = 0;
        int r = 1;
        while (l < r) {
            int u = lev[l++];
            for (int i = head[u]; i != -1; i = nxt[i]) {
                int v = to[i];
                if (v == par[u]) {
                    continue;
                }
                lev[r++] = v;
                vals[v] ^= vals[u];
            }
        }
        vector<int> res(q);
        for (int i = n - 1; i >= 0; i--) {
            int u = lev[i];
            Trie& a = tree[u];
            a.insert(vals[u]);
            for (int j = head[u]; j != -1; j = nxt[j]) {
                int v = to[j];
                if (par[u] == v) {
                    continue;
                }
                Trie& b = tree[v];
                if (a.size() < b.size()) {
                    swap(a, b);
                }
                a.merge(b);
            }
            for (auto& qu : que[u]) {
                if (a.size() < qu.k) {
                    res[qu.idx] = -1;
                } else {
                    res[qu.idx] = a.kth_element(qu.k);
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3590";
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
        auto par = jread_vector(line_in);
        getline(file_in, line_in);
        auto vals = jread_vector(line_in);
        getline(file_in, line_in);
        auto queries = jread_vector2d(line_in);
        auto res = sol.kthSmallest(par, vals, queries);
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
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