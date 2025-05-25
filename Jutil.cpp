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

chrono::steady_clock::time_point jtimer() {
    return std::chrono::steady_clock::now();
}

void jprint_time(chrono::steady_clock::time_point begin,
                 chrono::steady_clock::time_point end) {
    printf(
        "time = %lld (ms)\n",
        chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
}
