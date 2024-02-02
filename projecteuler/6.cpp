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
    long long s1 = 0, s2 = 0;
    for (int i = 1; i <= 100; i++) {
        s1 += i;
        s2 += i * i;
    }
    s1 *= s1;
    cout << s1 - s2 << endl;

}