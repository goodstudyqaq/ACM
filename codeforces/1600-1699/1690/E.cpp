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
    int n, k;
    cin >> n >> k;
    vector<ll> a(n);
    ll ans = 0;
    vector<int> num(k);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ans += a[i] / k;
        a[i] %= k;
        num[a[i]]++;
    }
    debug(ans, num);

    if (k == 1) {
        cout << ans << endl;
        return;
    }

    int left = 1, right = k - 1;

    while (left < right) {
        if (left + right < k) {
            left++;
            continue;
        }
        int mi = min(num[left], num[right]);
        num[left] -= mi;
        num[right] -= mi;
        ans += mi;
        if (num[left] == 0) {
            left++;
        } else {
            right--;
        }
    }
    if (left + left >= k) {
        ans += num[left] / 2;
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
}