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
    typedef pair<int, int> pii;
    vector<pii> V(3);
    for (int i = 0; i < 3; i++) {
        cin >> V[i].first >> V[i].second;
    }
    for (int i = 1; i < 3; i++) {
        if (V[i].second < V[0].second) {
            swap(V[i], V[0]);
        }
    }

    if (V[1].second == V[2].second) {
        cout << abs(V[1].first - V[2].first) << endl;
    } else {
        cout << 0 << endl;
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