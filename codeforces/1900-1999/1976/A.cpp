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
    string s;
    cin >> s;
    int now = 0;
    while (now < n && s[now] >= '0' && s[now] <= '9') {
        now++;
    }

    for (int i = 1; i < now; i++) {
        if (s[i] < s[i - 1]) {
            cout << "NO" << endl;
            return;
        }
    }

    for (int i = now + 1; i < n; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            cout << "NO" << endl;
            return;
        }
        if (s[i] < s[i - 1]) {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
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