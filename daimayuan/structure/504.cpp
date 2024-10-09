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
    cin >> n;

    vector<int> c(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    cin >> m;

    vector<array<int, 4>> que;
    for (int i = 0; i < m; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        que.push_back({l, r, k, i});
    }
    int B = 250;

    sort(que.begin(), que.end(), [&](array<int, 4> &x, array<int, 4> &y) {
        if (x[0] / B != y[0] / B) {
            return x[0] / B < y[0] / B;
        }
        return x[1] < y[1];
    });

    int L = 1, R = 0;

    vector<int> res(m);
    vector<int> cnt(n + 1);
    vector<int> fre(n + 1);
    auto add = [&](int idx) {
        fre[cnt[c[idx]]]--;
        cnt[c[idx]]++;
        fre[cnt[c[idx]]]++;
    };

    auto del = [&](int idx) {
        fre[cnt[c[idx]]]--;
        cnt[c[idx]]--;
        fre[cnt[c[idx]]]++;
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
        res[que[i][3]] = fre[que[i][2]];
    }
    for (int i = 0; i < m; i++) {
        cout << res[i] << '\n';
    }
}