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
const int maxn = 5e5;
const int S = 20;
int sum[maxn + 2][26];
int par[maxn + 1][S];
int dep[maxn + 1];

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, m;
    cin >> n >> m;
    dep[1] = 1;
    vector<vector<int>> V(n + 1);
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        par[i][0] = p;
        dep[i] = dep[p] + 1;
        V[p].push_back(i);
    }

    for (int i = 1; i < S; i++) {
        for (int j = 1; j <= n; j++) {
            int p = par[j][i - 1];
            if (p != -1) {
                par[j][i] = par[p][i - 1];
            }
        }
    }

    string s;
    cin >> s;

    vector<vector<pair<int, int>>> query(n + 1);
    for (int i = 0; i < m; i++) {
        int v, h;
        cin >> v >> h;
        query[h].push_back({v, i});
    }

    vector<int> now{1};
    vector<int> ans(m);
    vector<int> idx(n + 1);
    sum[0][s[0] - 'a'] = 1;
    idx[1] = 0;

    auto check = [&](int l, int r) {
        int odd_num = 0;
        for (int i = 0; i < 26; i++) {
            int cnt = sum[r][i];
            if (l) cnt -= sum[l - 1][i];
            if (cnt % 2) {
                odd_num++;
            }

            if (odd_num > 1) {
                return false;
            }
        }
        return true;
    };

    auto run = [&](int u, int step) {
        for (int i = S - 1; i >= 0; i--) {
            if ((step >> i) & 1) {
                u = par[u][i];
            }
        }
        return u;
    };

    for (int i = 1; i <= n; i++) {
        debug(i, now, idx);
        if (query[i].size()) {
            for (auto it : query[i]) {
                int fa = it.first;
                if (dep[fa] > i) {
                    ans[it.second] = true;
                    continue;
                }
                int fa_dep = dep[fa];

                int go = i - fa_dep;
                // 往上走 go 次

                int l = 0, r = now.size() - 1;
                int ans_l = -1;
                int _idx = -1;
                while (l <= r) {
                    int m = l + r >> 1;
                    int v = run(now[m], go);
                    if (idx[v] >= idx[fa]) {
                        _idx = idx[v];
                        ans_l = m;
                        r = m - 1;
                    } else {
                        l = m + 1;
                    }
                }
                if (ans_l == -1 || _idx > idx[fa]) {
                    ans[it.second] = true;
                    continue;
                }

                l = 0, r = now.size() - 1;
                int ans_r = -1;
                while (l <= r) {
                    int m = l + r >> 1;
                    int v = run(now[m], go);
                    if (idx[v] <= idx[fa]) {
                        ans_r = m;
                        l = m + 1;
                    } else {
                        r = m - 1;
                    }
                }
                debug(fa, ans_l, ans_r);
                // [ans_l, ans_r]
                ans[it.second] = check(ans_l, ans_r);
            }
        }
        vector<int> dnow;
        for (int u : now) {
            for (auto v : V[u]) {
                idx[v] = dnow.size();
                dnow.push_back(v);
            }
        }
        now = dnow;
        for (int i = 0; i < 26; i++) {
            sum[0][i] = 0;
        }
        for (int i = 0; i < now.size(); i++) {
            if (i) {
                for (int j = 0; j < 26; j++) {
                    sum[i][j] = sum[i - 1][j];
                }
            }
            sum[i][s[now[i] - 1] - 'a']++;
        }
    }

    for (int i = 0; i < m; i++) {
        if (ans[i]) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}
