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

int ask(int i, int j, int k) {
    cout << "? " << i << ' ' << j << ' ' << k << endl;
    fflush(stdout);
    int res;
    cin >> res;
    return res;
}

void solve() {
    int n;
    cin >> n;

    auto work = [&](vector<int> a) -> pii {
        vector<pii> V(4);
        for (int i = 0; i < 4; i++) {
            vector<int> tmp = a;
            tmp.erase(tmp.begin() + i);
            int val = ask(tmp[0], tmp[1], tmp[2]);
            V[i] = {val, a[i]};
        }

        sort(V.begin(), V.end());
        return {V[0].second, V[1].second};
    };

    pii possible = {1, 2};
    for (int i = 3; i <= n - 1; i += 2) {
        vector<int> a = {possible.first, possible.second, i, i + 1};
        possible = work(a);
    }

    if (n % 2 == 1) {
        int other = 1;
        while (other == possible.first || other == possible.second) other++;
        vector<int> a = {possible.first, possible.second, other, n};
        possible = work(a);
    }
    cout << "! " << possible.first << ' ' << possible.second << endl;
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
}