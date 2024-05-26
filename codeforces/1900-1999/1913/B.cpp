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

    int n = s.size();
    int num[2] = {0, 0};
    for (int i = 0; i < n; i++) {
        num[s[i] - '0']++;
    }

    int now = 0;
    while (now < n && num[0] > 0 && num[1] > 0) {
        if (s[now] == '0') {
            num[1]--;
        } else {
            num[0]--;
        }
        now++;
    }
    if (now == n) {
        cout << 0 << endl;
        return;
    }

    int full = (num[0] == 0 ? 1 : 0);

    while (now < n && s[now] - '0' != full) {
        now++;
    }

    cout << n - now << endl;
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