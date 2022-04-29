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
    int A, B, C, D, E, F, X;
    cin >> B >> A >> C >> E >> D >> F >> X;

    auto work = [&](int a, int b, int c, int x) {
        int tmp = b + c;
        int tmp2 = x / tmp;

        int lst = x % tmp;
        lst = min(lst, b);

        int res = a * tmp2 * b + lst * a;
        debug(tmp2, a, b, lst);
        debug(res);
        return res;
    };

    int a = work(A, B, C, X);
    int b = work(D, E, F, X);
    debug(a, b);
    if (a < b) {
        cout << "Aoki" << endl;
    } else if (a > b) {
        cout << "Takahashi" << endl;
    } else {
        cout << "Draw" << endl;
    }
    return 0;
}