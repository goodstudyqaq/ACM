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
    int n;
    cin >> n;
    long long res = 0;
    int lst;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;

        if (i == 0) {
            res = 1LL << a;
        } else {
            if (lst > a) {
                long long tmp = res + (1LL << a);
                res = tmp;
            } else if (lst == a) {
                long long tmp = (((res >> (a + 1)) + 1) << (a + 1)) + (1LL << a);
                res = tmp;
            } else {
                if ((res >> a) & 1) {
                    long long tmp = (((res >> (a + 1)) + 1) << (a + 1)) + (1LL << a);
                    res = tmp;
                } else {
                    long long tmp = ((res >> a) + 1) << a;
                    res = tmp;
                }
            }
        }
        debug(i, res);
        lst = a;
    }
    cout << res << endl;
}