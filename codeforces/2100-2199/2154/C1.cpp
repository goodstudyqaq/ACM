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
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        int b;
        cin >> b;
    }

    map<int, int> M;
    map<int, int> M2;

    auto work = [&](int val, map<int, int>& M) {
        for (int j = 2; j * j <= val; j++) {
            if (val % j == 0) {
                M[j]++;
                while (val % j == 0) {
                    val /= j;
                }
            }
        }
        if (val != 1) {
            M[val]++;
        }
    };

    for (int i = 0; i < n; i++) {
        int val = a[i];
        work(val, M);
        work(val + 1, M2);
    }
    for (auto it : M) {
        if (it.second > 1) {
            cout << 0 << '\n';
            return;
        }
    }

    for (auto it : M) {
        if (it.second >= 1 && M2[it.first] >= 1) {
            cout << 1 << '\n';
            return;
        }
    }
    cout << 2 << '\n';
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