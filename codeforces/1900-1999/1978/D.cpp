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
    long long n, c;
    cin >> n >> c;
    vector<long long> a(n + 1);
    vector<long long> sum(n + 1);
    long long mx_idx = 1;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (i == 1) a[i] += c;
        sum[i] = sum[i - 1] + a[i];
        if (a[i] > a[mx_idx]) {
            mx_idx = i;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (i == mx_idx) {
            cout << 0 << ' ';
        } else {
            long long tmp = sum[i];
            if (tmp >= a[mx_idx]) {
                cout << i - 1 << ' ';
            } else {
                cout << i << ' ';
            }
        }
    }
    cout << endl;




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