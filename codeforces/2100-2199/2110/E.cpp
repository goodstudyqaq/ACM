#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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

struct edge {
    int to;
    bool exists;
    int revref;
    int eidx;

    bool operator<(const edge& b) const { return to < b.to; }
};

void solve() {
    int n;
    cin >> n;
    vector<int> v(n), p(n);
    vector<int> X;
    for (int i = 0; i < n; i++) {
        cin >> v[i] >> p[i];
        X.push_back(v[i]);
        X.push_back(p[i]);
    }
    sort(X.begin(), X.end());

    X.resize(unique(X.begin(), X.end()) - X.begin());

    int sz = X.size();
    for (int i = 0; i < n; i++) {
        v[i] = lower_bound(X.begin(), X.end(), v[i]) - X.begin();
        p[i] = lower_bound(X.begin(), X.end(), p[i]) - X.begin();
        p[i] += sz;
    }

    int N = sz * 2;
    vector<vector<edge>> beg(N);
    vector<int> cnt(N);
    vector<int> ans;

    function<void(int, int)> dfs = [&](int x, int lst_idx) {
        for (int& i = cnt[x]; i < beg[x].size();) {
            if (beg[x][i].exists) {
                auto e = beg[x][i];
                beg[x][i].exists = 0;
                beg[e.to][e.revref].exists = 0;
                ++i;
                dfs(e.to, e.eidx);
            } else {
                i++;
            }
        }
        if (lst_idx != -1) {
            ans.push_back(lst_idx);
        }
    };

    auto add_edge = [&](int u, int v, int idx) {
        int sz1 = beg[u].size();
        int sz2 = beg[v].size();
        beg[u].push_back(edge{v, true, sz2, idx});
        beg[v].push_back(edge{u, true, sz1, idx});
    };

    for (int i = 0; i < n; i++) {
        add_edge(v[i], p[i], i);
    }

    int go = -1;
    int odd_num = 0;
    for (int i = 0; i < N; i++) {
        if (beg[i].size() % 2) {
            go = i;
            odd_num++;
        }
    }

    if (odd_num > 2) {
        cout << "NO\n";
        return;
    }
    if (odd_num == 0) {
        for (int i = 0; i < N; i++) {
            if (beg[i].size()) {
                go = i;
                break;
            }
        }
    }
    dfs(go, -1);

    if (ans.size() == n) {
        cout << "YES\n";
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i] + 1 << ' ';
        }
        cout << '\n';
    } else {
        cout << "NO\n";
    }
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