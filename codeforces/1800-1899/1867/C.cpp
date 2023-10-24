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

// struct fast_ios {
//     fast_ios() {
//         cin.tie(nullptr);
//         ios::sync_with_stdio(false);
//         cout << fixed << setprecision(10);
//     };
// } fast_ios_;

void solve() {
    int n;
    cin >> n;

    vector<int> s(n);
    for (int i = 0; i < n; i++) cin >> s[i];

    if (s[0] != 0) {
        cout << 0 << endl;
        fflush(stdout);
        int y;
        cin >> y;
        return;
    } else {
        int idx = n;
        for (int i = 0; i < n; i++)
            if (s[i] != i) {
                idx = i;
                break;
            }
        while (true) {
            cout << idx << endl;
            fflush(stdout);
            int y;
            cin >> y;
            if (y == -1) break;
            idx = y;
        }
    }
}

int main() {
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}