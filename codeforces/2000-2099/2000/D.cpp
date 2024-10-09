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
    vector<int> a(n + 1);
    vector<long long> sum(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }
    string s;
    cin >> s;

    function<long long(int, int)> work = [&](int l, int r) -> long long {
        debug(l, r);
        while (l <= r && s[l - 1] == 'R') l++;

        while (l <= r && s[r - 1] == 'L') r--;
        if (l > r) return 0;

        return sum[r] - sum[l - 1] + work(l + 1, r - 1);
    };

    cout << work(1, n) << endl;
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