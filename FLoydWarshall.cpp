#include "Jutil.h"
using namespace std;

const int N = 1e3;
int dis[N][N];
int U = 1e9;
void init(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            dis[i][j] = U;
        }
    }
}
void build(vector<vector<int>>& edges, int m) {
    for (int i = 0; i < m; i++) {
        if (dis[edges[i][0]][edges[i][1]] > edges[i][2]) {
            dis[edges[i][0]][edges[i][1]] = edges[i][2];
        }
    }
}
void run(int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dis[i][j] > dis[i][k] + dis[k][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
    }
}

int main() {
    int n = 10;
    vector<vector<int>> edges = {{0, 1, 1}, {0, 2, 4}, {1, 2, 2}};
    int m = edges.size();
    init(n);
    build(edges, m);
    run(n);
    printf("dis[0][2]:%d\n", dis[0][2]);  // dis[0][2]:3
    return 0;
}