#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, m, k;
    cin >> n >> m >> k;
    map<vector<string>, int> M;
    int m_idx = 0;
    vector<vector<string>> pics;
    vector<vector<int>> idx;
    for (int i = 0; i <= k; i++) {
        vector<string> pic(n);
        for (int j = 0; j < n; j++) {
            cin >> pic[j];
        }
        if (M.count(pic) == 0) {
            idx.push_back({});
            M[pic] = m_idx++;
            pics.push_back(pic);
        }
        idx[M[pic]].push_back(i);
    }

    int N = pics.size();
    vector<vector<int>> g(N);

    vector<int> in(N);

    int dir[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
    auto check = [&](int x, int y) -> bool {
        for (int i = 1; i < n - 1; i++) {
            for (int j = 1; j < m - 1; j++) {
                if (pics[x][i][j] != pics[y][i][j]) {
                    for (int k = 0; k < 4; k++) {
                        int i2 = i + dir[k][0], j2 = j + dir[k][1];
                        if (pics[x][i2][j2] != pics[y][i][j]) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    };

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            if (check(i, j)) {
                g[i].push_back(j);
                in[j]++;
            }
        }
    }

    int root = -1;
    for (int i = 0; i < N; i++) {
        if (in[i] == 0) {
            root = i;
            break;
        }
    }

    cout << idx[root][0] + 1 << endl;

    typedef array<int, 3> op;
    vector<op> ops;

    for (int i = 1; i < idx[root].size(); i++) {
        ops.push_back({2, idx[root][i]});
    }

    auto work = [&](int x, int y) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (pics[x][i][j] != pics[y][i][j]) {
                    ops.push_back({1, i, j});
                }
            }
        }
    };

    queue<int> Q;
    Q.push(root);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        for (auto v : g[u]) {
            in[v]--;
            if (in[v] == 0) {
                work(u, v);
                for (int i = 0; i < idx[v].size(); i++) {
                    ops.push_back({2, idx[v][i]});
                }
                Q.push(v);
            }
        }
    }
    cout << ops.size() << endl;
    for (int i = 0; i < ops.size(); i++) {
        int ty = ops[i][0];
        if (ty == 1) {
            cout << ty << ' ' << ops[i][1] + 1 << ' ' << ops[i][2] + 1 << '\n';
        } else {
            cout << ty << ' ' << ops[i][1] + 1 << '\n';
        }
    }
}