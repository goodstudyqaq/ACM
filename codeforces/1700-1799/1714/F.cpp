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
    int n, d12, d23, d31;
    cin >> n >> d12 >> d23 >> d31;
    vector<vector<int>> d(4, vector<int>(4));
    d[1][2] = d[2][1] = d12;
    d[2][3] = d[3][2] = d23;
    d[1][3] = d[3][1] = d31;

    auto work = [&](int rt) {
        vector<int> son;
        for (int i = 1; i <= 3; i++) {
            if (i != rt) {
                son.push_back(i);
            }
        }
        if (d[rt][son[0]] < d[rt][son[1]]) swap(son[0], son[1]);

        int tmp = d[rt][son[0]] - d[rt][son[1]];
        int tmp2 = d[son[0]][son[1]];
        if (tmp % 2 != tmp2 % 2) {
            cout << "NO" << endl;
            return;
        }
        if (tmp2 < tmp) {
            cout << "NO" << endl;
            return;
        }

        int tmp3 = tmp2 - tmp;
        int all = d[rt][son[0]] + 1 + tmp3 / 2;
        if (all > n) {
            cout << "NO" << endl;
            return;
        }

        cout << "YES" << endl;
        int last = rt;

        int idx = -1;
        if (tmp3 == 0) {
            idx = d[rt][son[1]];
        }

        int now = 4;
        for (int i = 1; i < d[rt][son[0]]; i++) {
            if (idx == i) {
                cout << last << ' ' << son[1] << endl;
                last = son[1];
            } else {
                cout << last << ' ' << now << endl;
                last = now;
                now++;
            }
        }
        cout << last << ' ' << son[0] << endl;

        int idx2 = last - tmp + 1 - tmp3 / 2;
        int ct = idx2 - 3;
        last = idx2;
        if (tmp3) {
            for (int i = 0; i < d[rt][son[1]] - ct - 1; i++) {
                cout << last << ' ' << now << endl;
                last = now;
                now++;
            }
            cout << last << ' ' << son[1] << endl;
        }

        while (now <= n) {
            cout << rt << ' ' << now << endl;
            now++;
        }
    };

    int mx = max({d12, d23, d31});
    if (mx == d12 || mx == d31) {
        work(1);
    } else {
        work(2);
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