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
    int n;
    long long m;
    cin >> n >> m;
    int N = n;

    long long mx = 1LL * (1 + n) * n / 2;
    long long mi = n;
    if (m > mx || m < mi) {
        cout << -1 << '\n';
        return;
    }

    auto cal1 = [&](int n) {
        return n;
    };

    vector<int> V;
    long long now = 0;
    while (n) {
        long long val = now + n + n - 1;
        if (m >= val) {
            V.push_back(n);
            now += n;
            n--;
        } else {
            break;
        }
    }
    debug(V);

    long long left = m - n - now;
    debug(left);
    // 1, 2, ... n

    if (n) {
        V.push_back(left + 1);
        for (int i = 1; i <= n; i++) {
            if (i != left + 1) {
                V.push_back(i);
            }
        }
    }

    cout << V[0] << '\n';
    for (int i = 0; i < V.size() - 1; i++) {
        cout << V[i] << ' ' << V[i + 1] << '\n';
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
    return 0;
}