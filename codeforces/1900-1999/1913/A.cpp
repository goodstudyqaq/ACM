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
    string s;
    cin >> s;
    int now = 0;
    int n = s.size();
    while (now + 1 < n && s[now + 1] == '0') now++;

    int a = 0, b = 0;
    for (int i = 0; i <= now; i++) {
        a = a * 10 + s[i] - '0';
    }
    for (int i = now + 1; i < n; i++) {
        b = b * 10 + s[i] - '0';
    }

    if (a >= b) {
        cout << -1 << endl;
    } else {
        cout << a << ' ' << b << endl;
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