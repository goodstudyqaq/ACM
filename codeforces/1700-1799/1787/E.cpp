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
    int n, k, x;
    cin >> n >> k >> x;
    set<int> S;
    set<int> left;
    for (int i = 1; i <= n; i++) {
        S.insert(i);
    }

    vector<vector<int>> ans;

    while (S.size()) {
        auto it = *S.begin();

        int tmp = it ^ x;

        if (tmp == 0) {
            // x == it
            ans.push_back({it});
            S.erase(it);
            continue;
        }
        if (S.count(tmp)) {
            ans.push_back({it, tmp});
            S.erase(tmp);
            S.erase(it);
        } else {
            S.erase(it);
            left.insert(it);
        }
    }
    debug(left);
    if (left.size()) {
        int tmp = 0;
        for (auto it : left) {
            tmp ^= it;
        }

        if (tmp == 0) {
            int sz = ans.size();
            if (sz == 0) {
                cout << "NO" << endl;
                return;
            }

            for (auto it : left) {
                ans[sz - 1].push_back(it);
            }
        } else if (tmp == x) {
            ans.push_back({});
            int sz = ans.size();
            for (auto it : left) {
                ans[sz - 1].push_back(it);
            }
        } else {
            cout << "NO" << endl;
            return;
        }
    }
    int sz = ans.size();

    if (k > sz || (sz % 2) != (k % 2)) {
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;
    for (int i = 0; i < k - 1; i++) {
        cout << ans[i].size() << ' ';
        for (auto it : ans[i]) {
            cout << it << ' ';
        }
        cout << endl;
    }

    vector<int> res;
    for (int i = k - 1; i < sz; i++) {
        for (auto it : ans[i]) {
            res.push_back(it);
        }
    }

    cout << res.size() << ' ';
    for (auto it : res) {
        cout << it << ' ';
    }
    cout << endl;
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