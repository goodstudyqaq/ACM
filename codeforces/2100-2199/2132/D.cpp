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

void solve() {
    long long k;
    cin >> k;
    const int M = 19;
    vector<long long> ten(M);
    ten[0] = 1;
    for (int i = 1; i < M; i++) {
        ten[i] = ten[i - 1] * 10;
    }

    long long up;
    long long left;
    for (int l = 1; l < M; l++) {
        long long len = 1LL * l * 9 * ten[l - 1];
        if (k >= len) {
            k -= len;
            continue;
        }
        // k < len
        long long num = k / l;
        up = ten[l - 1] + num - 1;
        left = k % l;
        break;
    }

    auto get_v = [&](long long val) {
        vector<int> v;
        while (val) {
            v.push_back(val % 10);
            val /= 10;
        }
        reverse(v.begin(), v.end());
        return v;
    };

    auto v1 = get_v(up);

    long long ans = 0;
    for (int i = 0; i < v1.size(); i++) {
        int d = v1[i];
        int l = v1.size() - i;
        ans += 1LL * d * (d - 1) / 2 * ten[l - 1];
        if (l - 2 >= 0) {
            ans += 45LL * (l - 1) * d * ten[l - 2];
        }
        ans += 1LL * d * (up % ten[l - 1] + 1);
    }

    auto v2 = get_v(up + 1);
    for (int i = 0; i < left; i++) {
        ans += v2[i];
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