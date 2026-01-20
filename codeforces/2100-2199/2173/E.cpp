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
    vector<int> a(n + 1);
    vector<int> idx(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        idx[a[i]] = i;
    }

    typedef array<int, 2> a2;
    auto ask = [&](int x, int y) -> a2 {
        cout << "? " << x << ' ' << y << '\n';
        fflush(stdout);
        cin >> x >> y;

        swap(a[x], a[y]);
        idx[a[x]] = x;
        idx[a[y]] = y;
        debug(a);
        return {x, y};
    };

    // if (n % 2) {
    //     int mid = (n + 1) / 2;

    //     while (idx[mid] != mid) {
    //         ask(mid, idx[mid]);
    //     }
    // }

    auto check = [&](int x, int y) {
        assert(x + y == n + 1);

        if (idx[x] != x) {
            return false;
        }
        if (idx[y] != y) {
            return false;
        }
        return true;
    };

    int half = n / 2;
    for (int i = 1; i <= half; i++) {
        int l = i, r = n - i + 1;
        if (l == r) break;
        int l_loc = idx[l], r_loc = idx[r];

        int x = l_loc;
        int y = n - r_loc + 1;

        if (x != y) {
            ask(x, y);
        }

        l_loc = idx[l];
        while (check(l, r) == false) {
            ask(i, l_loc);
        }
    }
    cout << "!\n";
    fflush(stdout);
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