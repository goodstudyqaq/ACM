#include <bits/stdc++.h>

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

struct Event {
    int t, f, val, idx;
    bool operator<(const Event &e) {
        if (t != e.t) return t < e.t;
        return f < e.f;  // 0 插入 1 删除
    }
};

struct Edge {
    int u, v, w;
    bool operator<(const Edge &e) {
        return w < e.w;
    }
};
struct DSU {
    std::vector<int> f;
    DSU(int n) : f(n) { std::iota(f.begin(), f.end(), 0); }
    int leader(int x) {
        if (f[x] == x) {
            return x;
        }
        int y = leader(f[x]);
        f[x] = y;
        return f[x];
    }
    bool merge(int a, int b) {
        auto x = leader(a);
        auto y = leader(b);
        if (x == y) {
            return false;
        }
        f[x] = y;
        return true;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> l(n + 1), r(n + 1), a(n + 1);
    vector<Event> events;
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i] >> a[i];
        events.push_back(Event{l[i], 0, a[i], i});
        events.push_back(Event{r[i], 1, a[i], i});
    }
    sort(events.begin(), events.end());
    multiset<pair<int, int>> S;

    vector<Edge> edges;

    for (int i = 0; i < events.size(); i++) {
        if (events[i].f == 0) {
            int val = events[i].val;
            auto it = S.lower_bound({val, 0});
            if (it != S.end()) {
                edges.push_back(Edge{events[i].idx, it->second, abs(val - it->first)});
            }
            if (it != S.begin()) {
                it--;
                edges.push_back(Edge{events[i].idx, it->second, abs(val - it->first)});
            }
            S.insert({events[i].val, events[i].idx});
        } else {
            S.erase(S.find({events[i].val, events[i].idx}));
        }
    }

    sort(edges.begin(), edges.end());
    DSU dsu(n + 1);
    long long ans = 0;
    int cnt = 0;
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        if (dsu.leader(u) != dsu.leader(v)) {
            ans += w;
            dsu.merge(u, v);
            cnt++;
        }
    }
    if (cnt != n - 1) {
        cout << -1 << endl;
        return;
    }
    cout << ans << endl;

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