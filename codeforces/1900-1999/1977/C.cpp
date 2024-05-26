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
    int n;
    cin >> n;
    vector<long long> a(n);
    long long g = 0;
    set<long long> S;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    int ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        int num = 0;
        long long val = a[i];
        for (int j = i; j >= 0; j--) {
            if (val % a[j] == 0) {
                num++;
            } else {
                long long tmp = __gcd(a[j], val);
                long long lcm = val * a[j] / tmp;
                if (S.count(lcm) == 0) {
                    num++;
                    val = lcm;
                }
            }
        }
        if (val != a[i]) {
            ans = max(ans, num);
        }
        S.insert(a[i]);
    }
    cout << ans << endl;
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