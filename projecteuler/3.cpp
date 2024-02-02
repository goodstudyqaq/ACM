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
    long long number = 600851475143;
    int mx = 1;
    for (long long i = 2; i * i <= number; i++) {
        if (number % i == 0) {
            mx = i;
            while (number % i == 0) number /= i;
        }
    }
    if (number != 1) mx = number;
    cout << mx << endl;
}