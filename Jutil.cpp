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

vector<string> jread_vector_string(string line) {
    vector<string> res;
    if (line[1] == ']') return res;
    for (int i = 1; i < line.size(); i++) {
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

vector<TreeNode*> jread_binary_tree(string line) {
    vector<TreeNode*> res;
    if (line[1] == ']') return res;
    for (int i = 1; i < line.size(); i++) {
        if (line[i] == 'n') {
            res.push_back(nullptr);
            i += 4;
            continue;
        }
        int d = 0;
        while (line[i] != ']' && line[i] != ',') {
            d = d * 10 + line[i] - '0';
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

void jprint_int(int num, string name) {
    printf("%s = %d\n", name.c_str(), num);
}

void jprint_long(long num, string name) {
    printf("%s = %ld\n", name.c_str(), num);
}

void jprint_longlong(long long num, string name) {
    printf("%s = %lld\n", name.c_str(), num);
}

void jprint_char(char c, string name) { printf("%s = %c\n", name.c_str(), c); }

void jprint_string(string s, string name) {
    printf("%s = %s\n", name.c_str(), s.c_str());
}

void jprint_vector(vector<int> vec, string name) {
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

void jprint_vector_char(vector<char> vec, string name) {
    if (vec.size() == 0) {
        printf("%s = []\n", name.c_str());
        return;
    }
    printf("%s = [%c", name.c_str(), vec[0]);
    for (int i = 1; i < vec.size(); i++) {
        printf(",%c", vec[i]);
    }
    printf("]\n");
}

void jprint_vector_string(vector<string> vec, string name) {
    if (vec.size() == 0) {
        printf("%s = []\n", name.c_str());
        return;
    }
    printf("%s = [%s", name.c_str(), vec[0].c_str());
    for (int i = 1; i < vec.size(); i++) {
        printf(",%s", vec[i].c_str());
    }
    printf("]\n");
}

void jprint_vector2d(vector<vector<int>> vec, string name) {
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

void jprint_vector2d_string(vector<vector<string>> vec, string name) {
    if (vec.size() == 0) {
        printf("%s = [[]]\n", name.c_str());
        return;
    }
    printf("%s = [\n", name.c_str());
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].size() == 0) {
            printf("[]");
        } else {
            printf("[%s", vec[i][0].c_str());
            for (int j = 1; j < vec[i].size(); j++) {
                printf(",%s", vec[i][j].c_str());
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

void jprint_array(int vec[], int n, string name) {
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

void jprint_array_char(char vec[], int n, string name) {
    if (n == 0) {
        printf("%s = []\n", name.c_str());
        return;
    }
    printf("%s = [%c", name.c_str(), vec[0]);
    for (int i = 1; i < n; i++) {
        printf(",%c", vec[i]);
    }
    printf("]\n");
}

void jprint_vector2d_size(vector<vector<int>> vec, string name) {
    printf("%s: %zux%zu\n", name.c_str(), vec.size(), vec[0].size());
}

void jprint_binary_tree(TreeNode* root, string name) {
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
    printf("[%d", q[l]->val);
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

chrono::steady_clock::time_point jtimer() {
    return std::chrono::steady_clock::now();
}

void jprint_time(chrono::steady_clock::time_point begin,
                 chrono::steady_clock::time_point end) {
    printf(
        "time = %lld (ms)\n",
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