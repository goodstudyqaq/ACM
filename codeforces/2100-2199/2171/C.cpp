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
    vector<int> a(n), b(n);
    int suma = 0, sumb = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    const int LIMIT = 19;
    for (int i = LIMIT; i >= 0; i--) {
        int cnt = 0;
        int mx_idx = -1;
        for (int j = 0; j < n; j++) {
            int abit = (a[j] >> i) & 1;
            int bbit = (b[j] >> i) & 1;
            if (abit != bbit) {
                cnt++;
                mx_idx = j;
            }
        }
        if (cnt % 2) {
            bool f = (mx_idx % 2 == 0);
            if (f) {
                cout << "Ajisai\n";
            } else {
                cout << "Mai\n";
            }
            return;
        }
    }
    cout << "Tie\n";
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