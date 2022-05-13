#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    int sum = 0;
    for (int i = 0; i < n / 2; i++) {
        sum += s[i] - '0';
        sum -= s[n - i - 1] - '0';
    }
    cout << (sum == 0 ? "YES" : "NO") << endl;
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