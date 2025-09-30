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
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    if (n == 1) {
        cout << a[0] << '\n';
        return;
    }

    long long ans = 0;

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            ans += a[i];
        } else {
            ans -= a[i];
        }
    }
    long long mx_ans = ans;
    // 跟自己换
    if (n % 2) {
        mx_ans += n - 1;
    } else {
        mx_ans += n - 2;
    }

    map<long long, int> M[2];
    for (int i = 0; i < n; i++) {
        M[i % 2][a[i] * 2 + i]++;
    }

    // 跟别人换
    for (int i = 0; i < n - 1; i++) {
        long long val = a[i] * 2 + i;
        M[i % 2][val]--;
        if (M[i % 2][val] == 0) {
            M[i % 2].erase(val);
        }
        if (i % 2 == 0) {
            long long tmp = ans - val + M[1].rbegin()->first;
            mx_ans = max(mx_ans, tmp);
        }
    }

    M[0].clear();
    M[1].clear();

    for (int i = 0; i < n; i++) {
        M[i % 2][a[i] * 2 - i]++;
    }

    for (int i = 0; i < n - 1; i++) {
        long long val = a[i] * 2 - i;
        M[i % 2][val]--;
        if (M[i % 2][val] == 0) {
            M[i % 2].erase(val);
        }
        if (i % 2 == 1) {
            long long tmp = ans + val - M[0].begin()->first;
            mx_ans = max(mx_ans, tmp);
        }
    }

    cout << mx_ans << '\n';
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