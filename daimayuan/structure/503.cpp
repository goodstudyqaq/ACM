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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;

    vector<int> c(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }

    vector<array<int, 3>> que;
    vector<long long> res2(m);
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        int len = r - l + 1;
        res2[i] = 1LL * len * (len - 1) / 2;
        que.push_back({l, r, i});
    }
    int B = 250;

    sort(que.begin(), que.end(), [&](array<int, 3> &x, array<int, 3> &y) {
        if (x[0] / B != y[0] / B) {
            return x[0] / B < y[0] / B;
        }
        return x[1] < y[1];
    });

    long long ans = 0;
    int L = 1, R = 0;

    vector<long long> res(m);
    vector<int> cnt(n + 1);
    auto add = [&](int idx) {
        ans += cnt[c[idx]];
        cnt[c[idx]]++;
    };

    auto del = [&](int idx) {
        cnt[c[idx]]--;
        ans -= cnt[c[idx]];
    };

    for (int i = 0; i < m; i++) {
        // 先加，后删
        while (R < que[i][1]) {
            R++;
            add(R);
        }
        while (L > que[i][0]) {
            L--;
            add(L);
        }
        while (R > que[i][1]) {
            del(R);
            R--;
        }
        while (L < que[i][0]) {
            del(L);
            L++;
        }
        res[que[i][2]] = ans;
    }
    for (int i = 0; i < m; i++) {
        long long g = __gcd(res[i], res2[i]);
        cout << res[i] / g << "/" << res2[i] / g << '\n';
    }
}