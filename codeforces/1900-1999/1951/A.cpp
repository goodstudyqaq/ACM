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

    vector<int> V;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            V.push_back(i);
        }
    }
    if (V.size() == 0) {
        cout << "YES" << endl;
        return;
    }

    if (V.size() % 2) {
        cout << "NO" << endl;
    } else {
        if (V.size() > 2) {
            cout << "YES" << endl;
        } else {
            // = 2
            if (V[0] == V[1] - 1) {
                cout << "NO" << endl;
            } else {
                cout << "YES" << endl;
            }
        }
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