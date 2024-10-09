#include <bits/stdc++.h>
#include <stdio.h>

#include <cstdlib>
#include <iostream>

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

    int n;
    cin >> n;

    string line;
    getline(cin, line);
    vector<vector<int>> V(n);
    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        std::stringstream ss(line);  // 创建一个 stringstream 对象
        int num;
        // 从 stringstream 中提取整数
        while (ss >> num) {
            V[i].push_back(num);
        }
    }
    debug(V);

    vector<set<int>> groups(2);
    vector<int> vis(n, -1);
    vector<int> in_group(n, -1);
    vector<int> cnt(2);
    int flag = 0;

    function<void(int, int, int, int)> dfs = [&](int u, int pre, int color, int flag) {
        vis[u] = color;
        if (color == 0) {
            groups[flag].insert(u);
            in_group[u] = flag;
        } else {
            groups[flag ^ 1].insert(u);
            in_group[u] = flag ^ 1;
        }

        for (auto v : V[u]) {
            if (v == pre) continue;
            if (vis[v] == -1) {
                dfs(v, u, color ^ 1, flag);
            } else {
                if (vis[v] == vis[u]) {
                    cout << -1 << endl;
                    exit(0);
                }
            }
        }
    };

    for (int i = 0; i < n; i++) {
        if (vis[i] == -1) {
            flag = cnt[0] > cnt[1];
            dfs(i, -1, 0, flag);
        } else {
            cnt[in_group[i]]++;
        }
    }


    for (int i = 0; i < 2; i++) {
        for (auto u : groups[i]) {
            cout << u << ' ';
        }
        cout << endl;
    }
}