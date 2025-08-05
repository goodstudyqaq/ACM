#include <bits/stdc++.h>

#include <queue>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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
    vector<long long> a(n);
    vector<long long> sum(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum[i] = a[i];
        if (i) {
            sum[i] += sum[i - 1];
        }
    }
    if (sum[n - 1] % 2) {
        cout << -1 << '\n';
        return;
    }

    long long half = sum[n - 1] / 2;
    for (int i = 0; i < n; i++) {
        if (a[i] > half) {
            cout << -1 << '\n';
            return;
        }
    }

    int p = 0;
    for (int i = 0; i < n; i++) {
        if (sum[i] > half) {
            p = i;
            break;
        }
    }
    // [0, p - 1] <= half

    if (sum[p - 1] == half) {
        cout << 1 << '\n';
        for (int i = 0; i < n; i++) {
            cout << a[i] << ' ';
        }
        cout << '\n';
        return;
    }
    cout << 2 << '\n';
    long long sum1 = sum[p - 1];
    long long sum2 = sum[p] - sum[p - 1];
    long long sum3 = sum[n - 1] - sum[p];
    // [0, p - 1]

    // (sum1 - w) + (sum3 - w) = sum2

    // [0, p - 1] 减掉 sum1, sum2 减掉 sum1 - w, sum3 减掉 w
    long long w = (sum1 + sum3 - sum2) / 2;

    for (int i = 0; i < p; i++) {
        cout << a[i] << ' ';
    }
    cout << sum1 - w << ' ';
    long long need = w;
    for (int i = p + 1; i < n; i++) {
        long long have = a[i];
        long long use = min(have, need);
        cout << use << ' ';
        a[i] -= use;
        need -= use;
    }
    cout << '\n';

    for (int i = 0; i < p; i++) {
        cout << 0 << ' ';
    }
    cout << sum3 - w << ' ';
    for (int i = p + 1; i < n; i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';
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