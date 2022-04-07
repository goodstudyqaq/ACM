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

int Len = 15;
long long X, Y;

long long ten(long long a, int m) {
    while (m--) {
        a *= 10;
    }
    return a;
}

int get_len(long long val) {
    int res = 0;
    while (val) {
        res++;
        val /= 10;
    }
    return res;
}

void dfs(long long a, long long b, long long c, int f, long long x, long long y, int len, int m) {
    if (len >= Len) return;
    if (!a && !b && !c && !f) {
        Len = len;
        X = x;
        Y = y;
        return;
    }

    if (c == 0) {
        dfs(0, 0, 0, 0, ten(a, m) + x, ten(b, m) + y, len + get_len(a + b + f), m);
        return;
    }
    int a0 = a % 10, b0 = b % 10, c0 = c % 10;
    if ((a0 + b0 + f) % 10 == c0) {
        dfs(a / 10, b / 10, c / 10, (a0 + b0 + f - c0) / 10, ten(a0, m) + x, ten(b0, m) + y, len, m + 1);
    } else {
        int tmp_a = ((c0 - b0 - f) % 10 + 10) % 10;
        dfs(a * 10 + tmp_a, b, c, f, x, y, len + 1, m);
        int tmp_b = ((c0 - a0 - f) % 10 + 10) % 10;
        dfs(a, b * 10 + tmp_b, c, f, x, y, len + 1, m);
        int tmp_c = (a0 + b0 + f) % 10;
        dfs(a, b, c * 10 + tmp_c, f, x, y, len + 1, m);
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    long long a, b, c;
    char it;
    cin >> a >> it >> b >> it >> c;
    debug(a, b, c);
    dfs(a, b, c, 0, 0, 0, 0, 0);
    cout << X << '+' << Y << '=' << X + Y << endl;
    debug(Len);
    return 0;
}