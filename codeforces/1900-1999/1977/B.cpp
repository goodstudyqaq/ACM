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
    int x;
    cin >> x;
    vector<int> V;
    while (x) {
        V.push_back(x % 2);
        x /= 2;
    }

    V.push_back(0);

    int now = 0;
    int n = V.size();
    while (now < n) {
        int go = now;
        while (go < n && V[go] == 0) go++;
        if (go == n) break;
        if (go + 1 == n) break;
        if (V[go + 1] != 0) {
            if (V[go] != V[go + 1]) {
                V[go + 1] = 0;
                V[go] *= -1;
                now = go + 1;
            } else {
                int go2 = go + 1;
                while (go2 < n && V[go2] == V[go]) {
                    V[go2] = 0;
                    go2++;
                }
                V[go2] = V[go];
                V[go] *= -1;
                now = go + 1;
            }
        } else {
            now = go + 1;
        }
    }

    cout << V.size() << endl;
    for (int i = 0; i < V.size(); i++) {
        cout << V[i] << ' ';
    }
    cout << endl;
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