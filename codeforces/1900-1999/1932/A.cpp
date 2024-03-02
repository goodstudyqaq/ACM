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
    string s;
    cin >> n >> s;
    int ans = 0;
    int now = 0;
    while (now < n) {
        if (now + 1 == n) break;
        if (s[now + 1] == '.') {
            now++;
        } else if (s[now + 1] == '@') {
            ans++;
            now++;
        } else {
            if (now + 2 == n) break;
            if (s[now + 2] == '*') break;
            if (s[now + 2] == '@') {
                ans++;
            }
            now += 2;
        }
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