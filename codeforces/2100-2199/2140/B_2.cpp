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

    int x = 90;

    int y = 1;
    auto get = [&](int val) {
        vector<int> v;
        while (val) {
            v.push_back(val % 10);
            val /= 10;
        }
        return v;
    };
    while (y <= 1000) {
        auto v = get(y);
        int val = x;
        for (int i = v.size() - 1; i >= 0; i--) {
            val = val * 10 + v[i];
        }
        if (val % (x + y) == 0) {
            cout << y << '\n';
        }
        y++;
    }
}