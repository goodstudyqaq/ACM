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

int idx(int v) {
    if (v == 0) {
        return 0;
    } else if (v == 1) {
        return 1;
    } else
        return 2;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    int num[3] = {0, 0, 0};
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        num[idx(a[i])]++;
    }

    if ((num[1] + num[2]) % 2) {
        cout << -1 << endl;
        return;
    }

    if (num[1] == num[2]) {
        cout << n << endl;
        for (int i = 1; i <= n; i++) {
            cout << i << ' ' << i << endl;
        }
        return;
    }

    int f = num[1] < num[2] ? 2 : 1;  // true 2多
    int cnt = (num[f] - num[3 - f]) / 2;

    int now = 0;
    vector<pii> res;
    while (now < n) {
        if (cnt == 0) {
            res.push_back({now, now});
            now++;
            continue;
        }
        int go = now;
        while (go < n && a[go] == 0) {
            res.push_back({go, go});
            go++;
        }
        now = go;

        if (idx(a[now]) != f) {
            res.push_back({now, now});
            now++;
            continue;
        } else {
            int go2 = now + 1;
            // 中间的 0 的个数
            while (go2 < n && a[go2] == 0) go2++;
            if (idx(a[go2]) != f) {
                // 不等
                for (int i = now; i <= go2; i++) {
                    res.push_back({i, i});
                }
                now = go2 + 1;
                continue;
            } else {
                int zero_num = go2 - (now + 1);
                if (zero_num % 2 == 0) {
                    res.push_back({now, go2});
                    now = go2 + 1;
                } else {
                    for (int i = now; i < go2 - 1; i++) {
                        res.push_back({i, i});
                    }
                    res.push_back({go2 - 1, go2});
                    now = go2 + 1;
                }
                cnt--;
            }
        }
    }
    cout << res.size() << endl;
    for (auto it : res) {
        cout << it.first + 1 << ' ' << it.second + 1 << endl;
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