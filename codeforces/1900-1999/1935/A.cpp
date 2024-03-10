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
    string bef = s;

    string s2 = s;

    reverse(s2.begin(), s2.end());

    if (s > s2) {
        swap(s, s2);
        n--;
    }

    string ans = s;
    if (n % 2) {
        ans += bef;
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