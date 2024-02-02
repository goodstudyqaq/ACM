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
    long long sum = 0;
    vector<long long> v;
    v.push_back(1);
    v.push_back(2);

    int limit = 4000000;
    while (true) {
        int sz = v.size();
        long long now = v[sz - 1] + v[sz - 2];
        if (now > limit) break;
        if (now % 2 == 0) sum += now;
        v.push_back(now);
    }
    debug(v);
    cout << sum + 2 << endl;
}