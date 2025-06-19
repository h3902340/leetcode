#include "Jutil.h"

int jread_int(string line) {
    int i = 0;
    bool isNeg = false;
    if (line[0] == '-') {
        isNeg = true;
        i++;
    }
    int num = 0;
    for (; i < line.size(); i++) {
        num *= 10;
        if (isNeg) {
            num -= (line[i] - '0');
        } else {
            num += (line[i] - '0');
        }
    }
    return num;
}
double jread_double(string line) {
    int i = 0;
    bool isNeg = false;
    if (line[0] == '-') {
        isNeg = true;
        i++;
    }
    double num = 0;
    double multi = .1;
    bool isAfterDot = false;
    for (; i < line.size(); i++) {
        if (line[i] == '.') {
            isAfterDot = true;
            i++;
            continue;
        }
        if (isAfterDot) {
            if (isNeg) {
                num -= multi * (line[i] - '0');
            } else {
                num += multi * (line[i] - '0');
            }
            multi *= 0.1;
        } else {
            num *= 10;
            if (isNeg) {
                num -= (line[i] - '0');
            } else {
                num += (line[i] - '0');
            }
        }
    }
    return num;
}

long jread_long(string line) {
    int i = 0;
    bool isNeg = false;
    if (line[0] == '-') {
        isNeg = true;
        i++;
    }
    long num = 0;
    for (; i < line.size(); i++) {
        num *= 10;
        if (isNeg) {
            num -= (line[i] - '0');
        } else {
            num += (line[i] - '0');
        }
    }
    return num;
}

long long jread_longlong(string line) {
    int i = 0;
    bool isNeg = false;
    if (line[0] == '-') {
        isNeg = true;
        i++;
    }
    long long num = 0;
    for (; i < line.size(); i++) {
        num *= 10;
        if (isNeg) {
            num -= (line[i] - '0');
        } else {
            num += (line[i] - '0');
        }
    }
    return num;
}

char jread_char(string line) { return line[1]; }

string jread_string(string line) {
    if (line.size() == 2) return "";
    return line.substr(1, line.size() - 2);
}

vector<int> jread_vector(string line) {
    vector<int> res;
    if (line[1] == ']') return res;
    for (int i = 1; i < line.size(); i++) {
        if (line[i] == ' ') continue;
        bool isNeg = false;
        if (line[i] == '-') {
            isNeg = true;
            i++;
        }
        int num = 0;
        while (line[i] != ',' && line[i] != ']') {
            num *= 10;
            if (isNeg) {
                num -= (line[i] - '0');
            } else {
                num += (line[i] - '0');
            }
            i++;
        }
        res.push_back(num);
        if (line[i] == ']') break;
    }
    return res;
}

vector<double> jread_vector_double(string line) {
    vector<double> res;
    if (line[1] == ']') return res;
    for (int i = 1; i < line.size(); i++) {
        if (line[i] == ' ') continue;
        bool isNeg = false;
        if (line[i] == '-') {
            isNeg = true;
            i++;
        }
        double num = 0;
        double multi = .1;
        bool isAfterDot = false;
        while (line[i] != ',' && line[i] != ']') {
            if (line[i] == '.') {
                isAfterDot = true;
                i++;
                continue;
            }
            if (isAfterDot) {
                if (isNeg) {
                    num -= multi * (line[i] - '0');
                } else {
                    num += multi * (line[i] - '0');
                }
                multi *= .1;
            } else {
                num *= 10;
                if (isNeg) {
                    num -= (line[i] - '0');
                } else {
                    num += (line[i] - '0');
                }
            }
            i++;
        }
        res.push_back(num);
        if (line[i] == ']') break;
    }
    return res;
}

vector<char> jread_vector_char(string line) {
    vector<char> res;
    if (line[1] == ']') return res;
    for (int i = 1; i < line.size(); i++) {
        if (line[i] == ' ') continue;
        i++;
        res.push_back(line[i]);
        i += 2;
        if (line[i] == ']') break;
    }
    return res;
}

vector<vector<int>> jread_vector2d(string line) {
    vector<vector<int>> res;
    for (int i = 1; i < line.size(); i++) {
        if (line[i] == '[') {
            vector<int> vec = jread_vector(line.substr(i));
            res.push_back(vec);
        }
    }
    return res;
}

vector<vector<char>> jread_vector2d_char(string line) {
    vector<vector<char>> res;
    for (int i = 1; i < line.size(); i++) {
        if (line[i] == '[') {
            vector<char> vec = jread_vector_char(line.substr(i));
            res.push_back(vec);
        }
    }
    return res;
}

vector<string> jread_vector_string(string line) {
    vector<string> res;
    if (line[1] == ']') return res;
    for (int i = 1; i < line.size(); i++) {
        if (line[i] == ' ') continue;
        i++;
        string s;
        while (line[i] != '"') {
            s += line[i];
            i++;
        }
        res.push_back(s);
        i++;
        if (line[i] == ']') break;
    }
    return res;
}

vector<vector<string>> jread_vector2d_string(string line) {
    vector<vector<string>> res;
    for (int i = 1; i < line.size(); i++) {
        if (line[i] == '[') {
            vector<string> vec = jread_vector_string(line.substr(i));
            res.push_back(vec);
        }
    }
    return res;
}

ListNode* jread_list(string line) {
    ListNode* res = nullptr;
    ListNode* cur = nullptr;
    if (line[1] == ']') return res;
    for (int i = 1; i < line.size(); i++) {
        if (line[i] == ' ') continue;
        bool isNeg = false;
        if (line[i] == '-') {
            isNeg = true;
            i++;
        }
        int num = 0;
        while (line[i] != ',' && line[i] != ']') {
            num *= 10;
            if (isNeg) {
                num -= (line[i] - '0');
            } else {
                num += (line[i] - '0');
            }
            i++;
        }
        if (res == nullptr) {
            res = new ListNode(num);
            cur = res;
        } else {
            cur->next = new ListNode(num);
            cur = cur->next;
        }
        if (line[i] == ']') break;
    }
    return res;
}

vector<ListNode*> jread_vector_list(string line) {
    vector<ListNode*> res;
    for (int i = 1; i < line.size(); i++) {
        if (line[i] == '[') {
            ListNode* vec = jread_list(line.substr(i));
            res.push_back(vec);
        }
    }
    return res;
}

vector<TreeNode*> jread_binary_tree(string line) {
    vector<TreeNode*> res;
    int i = 0;
    while (line[i] == ' ') {
        i++;
    }
    i++;
    while (line[i] == ' ') {
        i++;
    }
    if (line[i] == ']') return res;
    for (int i = 1; i < line.size(); i++) {
        if (line[i] == ' ') continue;
        if (line[i] == 'n') {
            res.push_back(nullptr);
            i += 4;
            continue;
        }
        bool isNeg = false;
        if (line[i] == '-') {
            isNeg = true;
            i++;
        }
        int d = 0;
        while (line[i] != ']' && line[i] != ',') {
            if (isNeg) {
                d = d * 10 - line[i] + '0';
            } else {
                d = d * 10 + line[i] - '0';
            }
            i++;
        }
        res.push_back(new TreeNode(d));
        if (line[i] == ']') break;
    }
    for (int i = 0; i < res.size(); i++) {
        if (res[i] == nullptr) continue;
        if (i * 2 + 1 < res.size()) {
            res[i]->left = res[i * 2 + 1];
        } else {
            res[i]->left = nullptr;
            res[i]->right = nullptr;
            continue;
        }
        if (i * 2 + 2 < res.size()) {
            res[i]->right = res[i * 2 + 2];
        } else {
            res[i]->right = nullptr;
        }
    }
    return res;
}

vector<Node*> jread_graph(string line) {
    vector<vector<int>> arr = jread_vector2d(line);
    vector<Node*> nodes(arr.size());
    for (int i = 0; i < arr.size(); i++) {
        nodes[i] = new Node(i + 1);
    }
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr[i].size(); j++) {
            int index = arr[i][j] - 1;
            nodes[i]->neighbors.push_back(nodes[index]);
        }
    }
    return nodes;
}

void jprint(int num, string name) { printf("%s = %d\n", name.c_str(), num); }

void jprint(double num, string name) { printf("%s = %f\n", name.c_str(), num); }

void jprint(long num, string name) { printf("%s = %ld\n", name.c_str(), num); }

void jprint(long long num, string name) {
    printf("%s = %lld\n", name.c_str(), num);
}

void jprint(char c, string name) { printf("%s = \"%c\"\n", name.c_str(), c); }

void jprint(string s, string name) {
    printf("%s = \"%s\"\n", name.c_str(), s.c_str());
}

void jprint(ListNode* vec, string name) {
    if (vec == nullptr) {
        printf("%s = []\n", name.c_str());
        return;
    }
    printf("%s = [%d", name.c_str(), vec->val);
    while (vec->next != nullptr) {
        vec = vec->next;
        printf(",%d", vec->val);
    }
    printf("]\n");
}

void jprint(vector<int> vec, string name) {
    if (vec.size() == 0) {
        printf("%s = []\n", name.c_str());
        return;
    }
    printf("%s = [%d", name.c_str(), vec[0]);
    for (int i = 1; i < vec.size(); i++) {
        printf(",%d", vec[i]);
    }
    printf("]\n");
}

void jprint(vector<long long> vec, string name) {
    if (vec.size() == 0) {
        printf("%s = []\n", name.c_str());
        return;
    }
    printf("%s = [%lld", name.c_str(), vec[0]);
    for (int i = 1; i < vec.size(); i++) {
        printf(",%lld", vec[i]);
    }
    printf("]\n");
}

void jprint(vector<double> vec, string name) {
    printf("%s = [", name.c_str());
    if (vec.size() == 0) {
        printf("]\n");
        return;
    }
    printf("%f", vec[0]);
    for (int i = 1; i < vec.size(); i++) {
        printf(",%f", vec[i]);
    }
    printf("]\n");
}

void jprint(vector<char> vec, string name) {
    printf("%s = [", name.c_str());
    if (vec.size() == 0) {
        printf("]\n");
        return;
    }
    printf("\"%c\"", vec[0]);
    for (int i = 1; i < vec.size(); i++) {
        printf(",\"%c\"", vec[i]);
    }
    printf("]\n");
}

void jprint(vector<string> vec, string name) {
    printf("%s = [", name.c_str());
    if (vec.size() == 0) {
        printf("]\n");
        return;
    }
    printf("\"%s\"", vec[0].c_str());
    for (int i = 1; i < vec.size(); i++) {
        printf(",\"%s\"", vec[i].c_str());
    }
    printf("]\n");
}

void jprint(vector<vector<int>> vec, string name) {
    if (vec.size() == 0) {
        printf("%s = [[]]\n", name.c_str());
        return;
    }
    printf("%s = [\n", name.c_str());
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].size() == 0) {
            printf("[]");
        } else {
            printf("[%d", vec[i][0]);
            for (int j = 1; j < vec[i].size(); j++) {
                printf(",%d", vec[i][j]);
            }
            printf("]");
        }
        if (i == vec.size() - 1) {
            printf("]\n");
        } else {
            printf(",\n");
        }
    }
}

void jprint(vector<vector<char>> vec, string name) {
    printf("%s = [", name.c_str());
    if (vec.size() == 0) {
        printf("[]]\n");
        return;
    }
    printf("\n");
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].size() == 0) {
            printf("[]");
        } else {
            printf("[\"%c\"", vec[i][0]);
            for (int j = 1; j < vec[i].size(); j++) {
                printf(",\"%c\"", vec[i][j]);
            }
            printf("]");
        }
        if (i == vec.size() - 1) {
            printf("]\n");
        } else {
            printf(",\n");
        }
    }
}

void jprint(vector<vector<string>> vec, string name) {
    printf("%s = [", name.c_str());
    if (vec.size() == 0) {
        printf("[]]\n");
        return;
    }
    printf("\n");
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].size() == 0) {
            printf("[]");
        } else {
            printf("[\"%s\"", vec[i][0].c_str());
            for (int j = 1; j < vec[i].size(); j++) {
                printf(",\"%s\"", vec[i][j].c_str());
            }
            printf("]");
        }
        if (i == vec.size() - 1) {
            printf("]\n");
        } else {
            printf(",\n");
        }
    }
}

void jprint_vector_size(vector<int> vec, string name) {
    printf("%s: %zu\n", name.c_str(), vec.size());
}

void jprint(bool vec[], int n, string name) {
    if (n == 0) {
        printf("%s = []\n", name.c_str());
        return;
    }
    printf("%s = [%d", name.c_str(), vec[0]);
    for (int i = 1; i < n; i++) {
        printf(",%d", vec[i]);
    }
    printf("]\n");
}

void jprint(int vec[], int n, string name) {
    if (n == 0) {
        printf("%s = []\n", name.c_str());
        return;
    }
    printf("%s = [%d", name.c_str(), vec[0]);
    for (int i = 1; i < n; i++) {
        printf(",%d", vec[i]);
    }
    printf("]\n");
}

void jprint(long long vec[], int n, string name) {
    if (n == 0) {
        printf("%s = []\n", name.c_str());
        return;
    }
    printf("%s = [%lld", name.c_str(), vec[0]);
    for (int i = 1; i < n; i++) {
        printf(",%lld", vec[i]);
    }
    printf("]\n");
}

void jprint(char vec[], int n, string name) {
    printf("%s = [", name.c_str());
    if (n == 0) {
        printf("]\n");
        return;
    }
    printf("\"%c\"", vec[0]);
    for (int i = 1; i < n; i++) {
        printf(",\"%c\"", vec[i]);
    }
    printf("]\n");
}

void jprint_vector2d_size(vector<vector<int>> vec, string name) {
    printf("%s: %zux%zu\n", name.c_str(), vec.size(), vec[0].size());
}

void jprint(TreeNode* root, string name) {
    printf("%s = ", name.c_str());
    if (root == nullptr) {
        printf("[]\n");
        return;
    }
    int l = 0;
    int r = 1;
    vector<TreeNode*> q;
    q.push_back(root);
    while (l < r) {
        auto t = q[l++];
        if (t == nullptr) {
            continue;
        }
        q.push_back(t->left);
        q.push_back(t->right);
        r += 2;
    }
    while (q.back() == nullptr) {
        q.pop_back();
        r--;
    }
    l = 0;
    printf("[%d", q[l++]->val);
    while (l < r) {
        if (q[l] == nullptr) {
            printf(",null");
        } else {
            printf(",%d", q[l]->val);
        }
        l++;
    }
    printf("]\n");
}

void jprint(Node* root, string name) {
    vector<vector<int>> arr;
    stack<Node*> st;
    st.push(root);
    unordered_map<int, bool> vis;
    while (!st.empty()) {
        Node* t = st.top();
        st.pop();
        if (t == nullptr) continue;
        int j = t->val - 1;
        if (vis[j]) continue;
        while (j >= arr.size()) {
            arr.push_back({});
        }
        vis[j] = true;
        for (int i = 0; i < t->neighbors.size(); i++) {
            int index = t->neighbors[i]->val;
            arr[j].push_back(index);
            if (vis[index - 1]) continue;
            st.push(t->neighbors[i]);
        }
    }
    jprint(arr, name);
}

chrono::steady_clock::time_point jtimer() {
    return std::chrono::steady_clock::now();
}

void jprint_time(chrono::steady_clock::time_point begin,
                 chrono::steady_clock::time_point end) {
    jprint_time(begin, end, "time");
}

void jprint_time(chrono::steady_clock::time_point begin,
                 chrono::steady_clock::time_point end, string name) {
    printf(
        "%s = %lld (ms)\n", name.c_str(),
        chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
}

bool anyOrderEqual(vector<int> a, vector<int> b) {
    if (a.size() != b.size()) return false;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

bool anyOrderEqual(vector<vector<int>> a, vector<vector<int>> b) {
    if (a.size() != b.size()) return false;
    auto cmp = [](vector<int>& a, vector<int>& b) { return a[0] < b[0]; };
    sort(a.begin(), a.end(), cmp);
    sort(b.begin(), b.end(), cmp);
    for (int i = 0; i < a.size(); i++) {
        bool tmp = anyOrderEqual(a[i], b[i]);
        if (!tmp) return false;
    }
    return true;
}

bool anyOrderEqual(vector<string> a, vector<string> b) {
    if (a.size() != b.size()) return false;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

bool anyOrderEqual(vector<vector<string>> a, vector<vector<string>> b) {
    if (a.size() != b.size()) return false;
    for (int i = 0; i < a.size(); i++) {
        bool tmp = anyOrderEqual(a[i], b[i]);
        if (!tmp) return false;
    }
    return true;
}

bool listEqual(ListNode* a, ListNode* b) {
    while (true) {
        if (a == nullptr && b == nullptr) {
            return true;
        }
        if (a == nullptr && b != nullptr) {
            return false;
        }
        if (a != nullptr && b == nullptr) {
            return false;
        }
        if (a->val != b->val) {
            return false;
        }
        a = a->next;
        b = b->next;
    }
}

// this does not account for graph isomorphism
bool graphEqual(Node* a, Node* b) {
    stack<Node*> sta;
    stack<Node*> stb;
    sta.push(a);
    stb.push(b);
    unordered_map<int, bool> vis;
    while (!sta.empty()) {
        Node* ta = sta.top();
        Node* tb = stb.top();
        sta.pop();
        stb.pop();
        if (ta == nullptr) {
            if (tb == nullptr) {
                continue;
            } else {
                return false;
            }
        }
        if (tb == nullptr) {
            return false;
        }
        if (ta->val != tb->val) {
            return false;
        }
        int a = ta->neighbors.size();
        int b = tb->neighbors.size();
        if (a != b) {
            return false;
        }
        vis[ta->val] = true;
        auto cmp = [](Node* a, Node* b) { return a->val < b->val; };
        sort(ta->neighbors.begin(), ta->neighbors.end(), cmp);
        sort(tb->neighbors.begin(), tb->neighbors.end(), cmp);
        for (int i = 0; i < ta->neighbors.size(); i++) {
            if (ta->neighbors[i]->val != tb->neighbors[i]->val) {
                return false;
            }
            if (vis[ta->neighbors[i]->val]) continue;
            sta.push(ta->neighbors[i]);
            stb.push(tb->neighbors[i]);
        }
    }
    return true;
}

bool binaryTreeEqual(TreeNode* a, TreeNode* b) {
    if (a == nullptr) {
        if (b == nullptr) {
            return true;
        } else {
            return false;
        }
    }
    if (b == nullptr) {
        return false;
    }
    if (a->val != b->val) return false;
    bool isEqual = binaryTreeEqual(a->left, b->left);
    if (!isEqual) return false;
    isEqual = binaryTreeEqual(a->right, b->right);
    if (!isEqual) return false;
    return true;
}