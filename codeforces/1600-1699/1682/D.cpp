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
    int n;
    string s;
    cin >> n >> s;

    int one = count(s.begin(), s.end(), '1');
    if (one == 0 || one % 2) {
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;

    vector<int> V;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            V.push_back(i);
        }
    }

    int sz = V.size();
    for (int i = 0; i < V.size(); i++) {
        for (int j = V[i]; (j + 1) % n != V[(i + 1) % sz]; j = (j + 1) % n) {
            cout << j + 1 << ' ' << (j + 1) % n + 1 << endl;
        }
    }

    int idx = (V[0] - 1 + n) % n;

    for (int i = 1; i < sz; i++) {
        int idx2 = (V[i] - 1 + n) % n;
        cout << idx + 1 << ' ' << idx2 + 1 << endl;
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
}