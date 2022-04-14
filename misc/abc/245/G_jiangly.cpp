#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k, l;
    std::cin >> n >> m >> k >> l;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i]--;
    }

    std::vector<std::array<std::pair<i64, int>, 2>> dis(n, {std::pair(-1LL, -1), std::pair(-1LL, -1)});

    std::vector<std::vector<std::pair<int, int>>> adj(n);

    std::priority_queue<std::pair<std::pair<i64, int>, int>,
                        std::vector<std::pair<std::pair<i64, int>, int>>, std::greater<>>
        h;

    for (int i = 0; i < l; i++) {
        int x;
        std::cin >> x;
        x--;
        h.emplace(std::pair(0LL, a[x]), x);
    }

    for (int i = 0; i < m; i++) {
        int u, v, c;
        std::cin >> u >> v >> c;
        u--;
        v--;
        adj[u].emplace_back(v, c);
        adj[v].emplace_back(u, c);
    }

    while (!h.empty()) {
        auto [d, u] = h.top();
        h.pop();
        if (dis[u][0].second == -1) {
            dis[u][0] = d;
        } else if (dis[u][1].second == -1 && d.second != dis[u][0].second) {
            dis[u][1] = d;
        } else {
            continue;
        }

        for (auto [v, c] : adj[u]) {
            h.emplace(std::pair(d.first + c, d.second), v);
        }
    }

    for (int i = 0; i < n; i++) {
        i64 ans;
        if (dis[i][0].second != a[i]) {
            ans = dis[i][0].first;
        } else {
            ans = dis[i][1].first;
        }
        std::cout << ans << " \n"[i == n - 1];
    }

    return 0;
}