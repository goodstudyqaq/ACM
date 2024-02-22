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
    fast_ios(){
        // cin.tie(nullptr);
        // ios::sync_with_stdio(false);
        // cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n;
    cin >> n;
    unordered_set<int> S;
    for (int i = 1; i <= n; i++) S.insert(i);

    auto ask = [&](int a, int b) {
        cout << "? " << a << ' ' << b << endl;
        fflush(stdout);
        int g;
        cin >> g;
        return g;
    };

    while (S.size() > 2) {
        auto i = S.begin();
        auto j = next(i);
        auto k = next(j);

        int l = ask(*i, *k);
        int r = ask(*j, *k);
        if (l == r) {
            S.erase(k);
        } else if (l > r) {
            S.erase(j);
        } else {
            S.erase(i);
        }
    }
    auto res1 = S.begin();
    auto res2 = next(res1);
    cout << "! " << *res1 << ' ' << *res2 <<endl;
    fflush(stdout);
    int ans;
    cin >> ans;
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