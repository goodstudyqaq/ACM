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
    if (n <= 2) {
        cout << 1 << endl;
        cout << 1 << ' ' << 1 << endl;
        return 0;
    }

    auto work = [&](int n) {
        if (n <= 2) {
            cout << 1 << ' ' << 1 << endl;
            return;
        }
        int x = (n - 2) / 3;
        int nowr = x + 1, nowc = 1;
        while (nowr > 0) {
            cout << nowr << ' ' << nowc << endl;
            nowr--;
            nowc++;
        }
        nowr = n, nowc = n - x + 1;
        while (nowc <= n) {
            cout << nowr << ' ' << nowc << endl;
            nowr--;
            nowc++;
        }
    };

    if (n % 3 == 2) {
        int res = (n * 2 - 1) / 3;
        cout << res << endl;
        work(n);
    } else if (n % 3 == 1) {
        int tmp = n - 2;
        int res = (tmp * 2 - 1) / 3 + 2;
        cout << res << endl;
        cout << n << ' ' << n << endl;
        cout << n - 1 << ' ' << n - 1 << endl;
        work(tmp);
    } else {
        int tmp = n - 1;
        int res = (tmp * 2 - 1) / 3 + 1;
        cout << res << endl;
        cout << n << ' ' << n << endl;
        work(tmp);
    }
    return 0;
}