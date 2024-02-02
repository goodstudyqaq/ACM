#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

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

    auto check = [&](int val) {
        vector<int> v;
        while (val) {
            v.push_back(val % 10);
            val /= 10;
        }
        int sz = v.size();
        for (int i = 0; i < sz / 2; i++) {
            if (v[i] != v[sz - 1 - i]) return false;
        }
        return true;
    };

    int mx = 0;
    for (int i = 100; i <= 999; i++) {
        for (int j = 100; j <= 999; j++) {
            int val = i * j;
            if (check(val)) {
                mx = max(mx, val);
            }
        }
    }
    cout << mx << endl;
}