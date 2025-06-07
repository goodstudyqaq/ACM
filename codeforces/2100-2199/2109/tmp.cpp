#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif


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

    auto work = [&](int x) {
        int res = 0;
        while (x) {
            res += x % 10;
            x /= 10;
        }
        return res;
    };


    for (int j = 99; j <= 99999; j = j * 10 + 9) {
        set<int> S;
        for (int i = 1; i <= 101; i++) {
            S.insert(work(j * i));
        }
        if (S.size() == 1) {
            debug(j, S);
        }

    }


}