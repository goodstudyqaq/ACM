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
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
    }

    int ask_num = 0;
    auto ask = [&](int u) {
        ask_num++;
        assert(ask_num <= n + 200);
        cout << "? 1 1 " << u + 1 << '\n';
        fflush(stdout);
        int res;
        cin >> res;
        return res;
    };

    auto change = [&](int u) {
        ask_num++;
        assert(ask_num <= n + 200);
        cout << "? 2 " << u + 1 << '\n';
        fflush(stdout);
    };

    vector<int> V(n);

    auto out = [&]() {
        cout << "!";
        for (int i = 0; i < n; i++) {
            cout << " " << V[i];
        }
        cout << endl;
    };

    V[0] = ask(0);

    if ((V[0] + 2) % 2 == 0) {
        // rt not 0
        change(0);
        int tmp = ask(0);

        int root_val;
        if (tmp > V[0]) {
            // 从 -1 变成了 1
            V[0] = 1;
            root_val = tmp - V[0];
        } else {
            V[0] = -1;
            root_val = tmp - V[0];
        }

        if (root_val == V[0]) {
            change(0);
            V[0] *= -1;
        }
        for (int i = 1; i < n; i++) {
            V[i] = ask(i);
        }
        out();

    } else {
        // rt = 0
        for (int i = 1; i < n; i++) {
            V[i] = ask(i);
            V[i] = V[i] - V[0];
        }
        out();
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