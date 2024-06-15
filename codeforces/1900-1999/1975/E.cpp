#include <bits/stdc++.h>

#include <algorithm>
#include <functional>

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

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> c(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    vector<vector<int>> V(n + 1);
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        V[x].push_back(y);
        V[y].push_back(x);
    }
    V[0].push_back(1);

    vector<int> fa(n + 1);
    function<void(int, int)> dfs = [&](int u, int pre) {
        fa[u] = pre;
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs(v, u);
        }
    };

    dfs(0, -1);
    map<int, int> mp;

    auto add = [&](int idx) {
        mp[idx]++;
        if (mp[idx] == 0) mp.erase(idx);
    };

    auto del = [&](int idx) {
        mp[idx]--;
        if (mp[idx] == 0) mp.erase(idx);
    };

    for (int i = 1; i <= n; i++) {
        if (c[i]) {
            add(i);
            del(fa[i]);
        }
    }

    while (q--) {
        int x;
        cin >> x;

        if (c[x]) {
            del(x);
            add(fa[x]);
        } else {
            add(x);
            del(fa[x]);
        }
        c[x] ^= 1;

        if (mp.size() == 2) {
            vector<int> v;
            for (auto it : mp) {
                v.push_back(it.second);
            }

            if (v[0] > v[1]) swap(v[0], v[1]);
            if (v[0] == -1 && v[1] == 1) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        } else if (mp.size() == 4) {
            vector<int> v;
            for (auto it : mp) {
                v.push_back(it.second);
            }
            sort(v.begin(), v.end());
            if (v[0] == -1 && v[1] == -1 && v[2] == 1 && v[3] == 1) {
                vector<int> v2;
                for (auto it : mp) {
                    if (it.second == -1) v2.push_back(it.first);
                }
                if (fa[v2[0]] == v2[1] || fa[v2[1]] == v2[0]) {
                    if (c[v2[0]] || c[v2[1]]) {
                        cout << "YES" << endl;
                    } else {
                        cout << "NO" << endl;
                    }
                } else {
                    cout << "NO" << endl;
                }

            } else {
                cout << "NO" << endl;
            }
        } else {
            cout << "NO" << endl;
        }
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