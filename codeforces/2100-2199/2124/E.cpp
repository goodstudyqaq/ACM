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
    vector<long long> a(n + 1);
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    if (sum % 2) {
        cout << -1 << '\n';
        return;
    }

    long long sum2 = 0;
    bool f = false;
    for (int i = 1; i <= n; i++) {
        sum2 += a[i];
        if (sum == sum2 * 2) {
            f = true;
            break;
        }
    }
    if (f) {
        cout << 1 << '\n';
        for (int i = 1; i <= n; i++) {
            cout << a[i] << ' ';
        }
        cout << '\n';
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (a[i] > sum / 2) {
            cout << -1 << '\n';
            return;
        }
    }

    sum2 = 0;
    int i;
    for (i = 1; i <= n; i++) {
        sum2 += a[i];
        if (sum2 >= sum - sum2) {
            break;
        }
    }

    long long diff = sum2 - (sum - sum2);

    diff /= 2;

    vector<int> V;
    for (int j = 1; j <= i; j++) {
        if (a[j] >= diff) {
            V.push_back(j);
        }
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