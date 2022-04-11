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

vector<int> f;
int find(int u) {
    return u == f[u] ? u : f[u] = find(f[u]);
}

bool Union(int u, int v) {
    int fu = find(u), fv = find(v);
    if (fu != fv) {
        f[fu] = fv;
        return true;
    }
    return false;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n;
    cin >> n;
    vector<string> s(3);
    for (int i = 0; i < 3; i++) {
        cin >> s[i];
    }
    f.resize(3 * n);
    iota(f.begin(), f.end(), 0);

    vector<int> sum1, sum2, sum3;
    sum1.resize(n);
    sum2.resize(n);
    sum3.resize(n);

    for (int i = 0; i < n; i++) {
        // 先垂直
        int cnt = 0;
        for (int j = 0; j < 2; j++) {
            if (s[j][i] == '1' && s[j + 1][i] == '1' && Union(j * n + i, (j + 1) * n + i)) {
                cnt++;
            }
        }
        sum1[i] = cnt;
        cnt = 0;
        if (i != 0) {
            for (int j = 0; j < 3; j++) {
                if (s[j][i] == '1' && s[j][i - 1] == '1' && Union(j * n + i, j * n + i - 1)) {
                    cnt++;
                }
            }
        }
        sum2[i] = cnt;

        cnt = 0;
        for (int j = 0; j < 3; j++) {
            if (s[j][i] == '1') cnt++;
        }
        sum3[i] = cnt;

        if (i != 0) {
            sum1[i] += sum1[i - 1];
            sum2[i] += sum2[i - 1];
            sum3[i] += sum3[i - 1];
        }
    }
    debug(sum1);
    debug(sum2);
    debug(sum3);

    vector<int> nxt(n + 1, n);
    for (int i = n - 1; i >= 0; i--) {
        if (s[0][i] == '1' && s[1][i] == '0' && s[2][i] == '1') {
            nxt[i] = nxt[i + 1];
        } else {
            nxt[i] = i;
        }
    }

    auto get_sum = [&](int l, int r, vector<int> &sum) {
        int res = sum[r];
        if (l != 0) {
            res -= sum[l - 1];
        }
        return res;
    };

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        int no101 = nxt[l];
        if (no101 > r) {
            cout << 2 << endl;
            continue;
        }

        int res = get_sum(no101, r, sum3) - get_sum(no101, r, sum1) - get_sum(no101 + 1, r, sum2);
        // debug(res);

        if (no101 != l) {
            if (s[0][no101] == '0' && s[2][no101] == '0') {
                res += 2;
            } else if (s[0][no101] == '1' && s[2][no101] == '1') {
            } else {
                res++;
            }
        }
        cout << res << endl;
    }
    return 0;
}