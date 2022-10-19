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
    vector d = vector(2, vector(n, 0));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            cin >> d[i][j];
        }
    }

    auto work = [&](int dis) -> bool {
        int p1 = 0, p2 = dis;
        multiset<int> s[2];
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < n; j++) {
                s[i].insert(d[i][j]);
            }
        }

        auto get_big = [&](int idx) {
            if (s[idx].size() == 0) return -1;
            return *s[idx].rbegin();
        };

        auto get_biggest = [&]() -> int {
            int val1 = get_big(0);
            int val2 = get_big(1);
            return max(val1, val2);
        };

        vector<int> ans;
        while (get_biggest() > dis) {
            int f = get_big(1) > get_big(0);
            int biggest = get_biggest();

            int tmp = biggest - dis;

            if (s[f ^ 1].count(tmp) == 0) {
                // debug(tmp);
                return false;
            }

            // 存在
            if (f == 0) {
                ans.push_back(biggest);
            } else {
                ans.push_back(dis - biggest);
            }

            s[f].erase(s[f].find(biggest));
            s[f ^ 1].erase(s[f ^ 1].find(tmp));
        }

        int sz = s[0].size();

        while (s[0].size()) {
            int v1 = *s[0].begin();
            int v2 = *s[1].rbegin();
            if (v1 + v2 != dis) return false;
            ans.push_back(v1);
            s[0].erase(s[0].find(v1));
            s[1].erase(s[1].find(v2));
        }

        sort(ans.begin(), ans.end());
        int mi = ans[0];

        if (mi < 0) {
            int delta = -mi;
            p1 += delta, p2 += delta;
            for (int i = 0; i < ans.size(); i++) {
                ans[i] += delta;
            }
        }

        cout << "YES" << endl;

        for (auto it : ans) {
            cout << it << ' ';
        }
        cout << endl;
        cout << p1 << ' ' << p2 << endl;
        return true;
    };

    for (int i = 0; i < n; i++) {
        if (work(d[0][0] + d[1][i])) {
            return;
        }
        if (work(abs(d[0][0] - d[1][i]))) {
            return;
        }
    }
    cout << "NO" << endl;
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