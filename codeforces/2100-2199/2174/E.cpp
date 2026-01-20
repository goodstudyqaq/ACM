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
typedef array<int, 2> a2;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

int quick(int x, int y, int p) {
    int res = 1;
    while (y) {
        if (y % 2) res = 1LL * res * x % p;
        y /= 2;
        x = 1LL * x * x % p;
    }
    return res;
}

void solve() {
    int n, m, p;
    cin >> n >> m >> p;

    int ans = 0;

    vector<int> Mpow(n + 1), Mpow_inv(n + 1);
    Mpow[0] = 1;
    for (int i = 1; i <= n; i++) {
        Mpow[i] = 1LL * Mpow[i - 1] * m % p;
    }

    Mpow_inv[n] = quick(Mpow[n], p - 2, p);
    for (int i = n - 1; i >= 1; i--) {
        Mpow_inv[i] = 1LL * Mpow_inv[i + 1] * m % p;
    }
    auto work = [&](int len) {
        int half = (len + 1) / 2;
        return 1LL * Mpow[half] * Mpow_inv[len] % p;
    };

    vector<int> a(n + 1), suma(n + 1);
    for (int i = 1; i <= n; i++) {
        a[i] = work(i);
        int num = n - i + 1;
        int val = 1LL * a[i] * num % p;
        ans = (ans + val) % p;
        suma[i] = suma[i - 1] + a[i];
    }

    debug(ans);

    int res2 = 0;

    int sum = 0;
    // 同心
    map<a2, int> M;

    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            int len = r - l + 1;
            int cnt = (len - 1) / 2;
            (res2 += 1LL * a[len] * cnt % p) %= p;

            (sum += a[len]) %= p;
            (M[{l + r >> 1, len % 2}] += a[len]) %= p;
        }
    }
    (res2 *= 2) %= p;
    debug(res2);
    debug(a, sum);


    // 不同心暴力
    // for (int l1 = 1; l1 <= n; l1++) {
    //     for (int r1 = l1; r1 <= n; r1++) {
    //         for (int l2 = 1; l2 <= n; l2++) {
    //             for (int r2 = l2; r2 <= n; r2++) {
    //                 int len1 = r1 - l1 + 1;
    //                 int len2 = r2 - l2 + 1;
    //                 int mid1 = l1 + r1 >> 1;
    //                 int mid2 = l2 + r2 >> 1;
    //                 if (mid1 == mid2 && (len1 % 2) == (len2 % 2)) continue;
    //                 (res2 += 1LL * a[len1] * a[len2] % p) %= p;
    //             }
    //         }


    //     }
    // }



    // 不同心
    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            int len = r - l + 1;
            int tmp = 1LL * a[len] * ((sum - M[{l + r >> 1, len % 2}]) % p) % p;
            (res2 += tmp) %= p;
            // debug(l, r, tmp);
        }
    }

    ans = (ans + res2) % p;
    ans = (ans + p) % p;
    cout << ans << '\n';
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