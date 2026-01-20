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
typedef array<int, 2> a2;

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
    s += s;
    vector<int> last(n * 2, -1);

    int ans = 0;
    for (int i = 0; i < n * 2; i++) {
        if (s[i] == '1') {
            last[i] = i;
        } else {
            if (i != 0) {
                last[i] = last[i - 1];
            }
        }

        if (last[i] != -1) {
            ans = max(ans, i - last[i]);
        }
    }
    cout << ans << '\n';
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