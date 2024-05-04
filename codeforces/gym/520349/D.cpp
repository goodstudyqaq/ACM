#include <bits/stdc++.h>

#include <cstdio>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

// #define endl '\n'

// struct fast_ios {
//     fast_ios() {
//         cin.tie(nullptr);
//         ios::sync_with_stdio(false);
//         cout << fixed << setprecision(10);
//     };
// } fast_ios_;

int main() {
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif

    int x;
    cin >> x;
    map<int, int> mp;
    mp[x] = 0;

    int limit = 1000;

    auto ask = [&](int s) {
        cout << "+ " << s << endl;
        fflush(stdout);
        int res;
        cin >> res;
        return res;
    };

    auto out = [&](int ans) {
        cout << "! " << ans << endl;
        fflush(stdout);
    };

    for (int i = 1; i <= limit; i++) {
        int go = ask(1);
        if (mp.count(go)) {
            out(i - mp[go]);
            return 0;
        }
        mp[go] = i;
    }

    int times = 0;

    while (true) {
        times++;
        int go = ask(limit);

        if (mp.count(go)) {
            int ans = limit - mp[go] + limit * times;
            out(ans);
            return 0;
        }
    }
}