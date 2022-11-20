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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int q;
    cin >> q;

    set<ll> S;
    map<ll, ll> M;
    while (q--) {
        char it;
        ll x;
        cin >> it >> x;
        if (it == '+') {
            S.insert(x);
        } else {
            if (M.count(x) == 0) M[x] = x;
            while (S.count(M[x])) {
                M[x] += x;
            }
            cout << M[x] << endl;
        }
    }
    return 0;
}