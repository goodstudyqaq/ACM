#include <bits/stdc++.h>

#include <limits>
#include <queue>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

struct state {
    long long times, val;

    int now_idx, mx_idx;

    bool operator<(const state& s) const {
        if (times != s.times) {
            return times > s.times;
        } else {
            return val < s.val;
        }
    }
};

void solve() {
    int n, m, p;
    cin >> n >> m >> p;
    vector<int> w(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    typedef pair<int, long long> pil;
    typedef pair<long long, long long> pll;
    vector<vector<pil>> V(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        V[u].push_back({v, c});
    }
    priority_queue<state> Q;
    Q.push(state{0, p, 1, 1});
    vector<vector<int>> vis(n + 1, vector<int>(n + 1, 0));

    const long long inf = numeric_limits<long long>::max() / 2;
    vector<vector<pll>> d(n + 1, vector<pll>(n + 1, pll(inf, inf)));
    d[1][1] = {0, p};

    while (!Q.empty()) {
        auto now = Q.top();
        Q.pop();

        if (vis[now.now_idx][now.mx_idx]) continue;
        vis[now.now_idx][now.mx_idx] = 1;

        for (auto e : V[now.now_idx]) {
            int v = e.first;
            long long ct = e.second;

            long long nxt_times = now.times;
            long long nxt_val = now.val;

            if (now.val >= ct) {
                nxt_val -= ct;
            } else {
                long long need = ct - now.val;

                long long ct_times = (need - 1) / w[now.mx_idx] + 1;
                nxt_times += ct_times;
                nxt_val = nxt_val + ct_times * w[now.mx_idx] - ct;
            }

            int nxt_mx_idx = now.mx_idx;
            if (w[v] > w[nxt_mx_idx]) {
                nxt_mx_idx = v;
            }

            if (d[v][nxt_mx_idx].first > nxt_times || (d[v][nxt_mx_idx].first == nxt_times && d[v][nxt_mx_idx].second < nxt_val)) {
                d[v][nxt_mx_idx] = {nxt_times, nxt_val};
                Q.push(state{d[v][nxt_mx_idx].first, d[v][nxt_mx_idx].second, v, nxt_mx_idx});
            }
        }
    }

    long long res = inf;
    for (int i = 1; i <= n; i++) {
        auto it = d[n][i];
        res = min(res, it.first);
    }
    // debug(inf);
    if (res == inf) res = -1;
    cout << res << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}