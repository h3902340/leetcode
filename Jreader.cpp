#include "Jreader.h"

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