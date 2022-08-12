#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios(){
        // cin.tie(nullptr);
        // ios::sync_with_stdio(false);
        // cout << fixed << setprecision(10);
    };
} fast_ios_;

int main() {
#ifdef LOCAL
    // freopen("./data.in", "r", stdin);
#endif

    auto ask = [&](int a, int b) {
        cout << "? " << a << ' ' << b << endl;
        fflush(stdout);
        int res;
        cin >> res;
        return res;
    };

    auto out = [&](int res) {
        cout << "! " << res << endl;
    };

    int T;
    cin >> T;
    while (T--) {
        int now = 0;
        for (int i = 0; i < 30; i++) {
            int tmp = (1 << i) - now;
            int res = ask(tmp, (1 << (i + 1)) + tmp);
            if (res == (1 << i)) {
                // 原来是 0
            } else {
                // 原来是 1
                now = (1 << i) + now;
            }
        }
        out(now);
    }
    return 0;
}