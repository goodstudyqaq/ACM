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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    vector<vector<int>> V1(n + 1), V2(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for (int i = 2; i <= n; i++) {
        V1[a[i]].push_back(a[i - 1]);
        V1[a[i - 1]].push_back(a[i]);

        V2[b[i]].push_back(b[i - 1]);
        V2[b[i - 1]].push_back(b[i]);
    }

    auto check_equal = [&]() {
        for (int i = 1; i <= n; i++) {
            if (V1[i].size() != V2[i].size()) return false;

            sort(V1[i].begin(), V1[i].end());
            sort(V2[i].begin(), V2[i].end());
            int sz = V1[i].size();
            for (int j = 0; j < sz; j++) {
                if (V1[i][j] != V2[i][j]) return false;
            }
        }
        return true;
    };

    if (a[1] != b[1] || a[n] != b[n] || !check_equal()) {
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;

    auto work = [&](int l, int r) {
        for (int i = l; i <= (l + r) / 2; i++) {
            swap(a[i], a[r + l - i]);
        }
    };

    vector<pii> ans;
    for (int i = 2; i < n; i++) {
        if (a[i] == b[i]) continue;
        debug(i, a, ans);

        bool flag = false;
        for (int j = i + 1; j < n; j++) {
            if (a[j] == b[i] && a[j + 1] == a[i - 1]) {
                ans.push_back({i - 1, j + 1});
                work(i - 1, j + 1);
                flag = true;
                break;
            }
        }

        if (flag) continue;
        vector<int> loc(n + 1, -1);

        for (int j = i; j < n; j++) {
            loc[a[j]] = j;
            if (a[j] == a[i - 1] && a[j + 1] == b[i]) {
                for (int k = j + 1; k <= n; k++) {
                    if (loc[a[k]] != -1) {
                        ans.push_back({loc[a[k]], k});
                        work(loc[a[k]], k);
                        break;
                    }
                }
                break;
            }
        }
        for (int j = i + 1; j < n; j++) {
            if (a[j] == b[i] && a[j + 1] == a[i - 1]) {
                ans.push_back({i - 1, j + 1});
                work(i - 1, j + 1);
                flag = true;
                break;
            }
        }
    }
    debug(a, b);
    cout << ans.size() << endl;
    for (auto it : ans) {
        cout << it.first << ' ' << it.second << endl;
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
}