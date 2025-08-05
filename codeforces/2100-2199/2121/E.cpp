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

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

long long power(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b % 2) res *= a;
        a *= a;
        b /= 2;
    }
    return res;
}

void solve() {
    int l, r;
    cin >> l >> r;
    int ans = 0;
    auto work = [&](int val) {
        vector<int> v1;
        while (val) {
            v1.push_back(val % 10);
            val /= 10;
        }
        return v1;
    };

    auto v1 = work(l);
    auto v2 = work(r);
    int sz = v1.size();
    int a = 0, b = 0;
    for (int i = sz - 1; i >= 0; i--) {
        a = a * 10 + (v1[i] - '0');
        b = b * 10 + (v2[i] - '0');
        if (b - a >= 2) {
            break;
        }
        if (v1[i] == v2[i]) {
            ans += 2;
        } else {
            ans += 1;
        }
    }
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