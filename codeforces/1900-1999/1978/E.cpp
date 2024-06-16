#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;
int len;
struct Query {
    int l, r, idx;
    int block;
    Query(int _l, int _r, int _idx)
        : l(_l), r(_r), idx(_idx) {
        block = l / len;
    }
    Query() {}
    bool operator<(const Query& b) const {
        if (block != b.block) return block < b.block;
        return r < b.r;
    }
};

void solve() {
    int n;
    cin >> n;
    len = sqrt(n);
    string a, b;
    cin >> a >> b;
    int q;
    cin >> q;
    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        queries[i] = Query(l - 1, r - 1, i);
    }
    sort(queries.begin(), queries.end());
    vector<int> ans(q);

    string a2 = a;
    string b2 = b;

    int cnt = 0;
    int L = 0, R = -1;
    // 左闭右闭o
    for (int i = 0; i < q; i++) {
        Query it = queries[i];
        while (L < it.l) {
            // 删
            if (L + 2 <= R && a[L] == '0' && a[L + 2] == '0' && b[L + 1] == '0') {
                // b2[L + 1] = '1';
                if (L + 3 <= R && b2[L + 3] == '1') {
                    // a2[L + 2] = '1';
                    a2[L + 2] = '0';
                    cnt--;
                }
                b2[L + 1] = '0';
            }
            if (a[L] == '1') {
                cnt--;
            }

            if (L + 2 <= R && b[L] == '1' && b2[L + 2] == '1' && a[L + 1] == '0') {
                a2[L + 1] = '0';
                cnt--;
            }

            L++;
        }
        while (L > it.l) {
            // 加
            L--;
            if (a[L] == '1') {
                cnt++;
            }

            if (L + 2 <= R && b[L] == '1' && b2[L + 2] == '1' && a[L + 1] == '0') {
                a2[L + 1] = '1';
                cnt++;
            }

            if (L + 2 <= R && a[L] == '0' && a[L + 2] == '0' && b[L + 1] == '0') {
                b2[L + 1] = '1';
                if (L + 3 <= R && b2[L + 3] == '1') {
                    a2[L + 2] = '1';
                    cnt++;
                }
            }
        }
        while (R < it.r) {
            // 加
            R++;
            if (a[R] == '1') {
                cnt++;
            }

            if (R - 2 >= L && b[R] == '1' && b2[R - 2] == '1' && a[R - 1] == '0') {
                a2[R - 1] = '1';
                cnt++;
            }

            if (R - 2 >= L && a[R] == '0' && a[R - 2] == '0' && b[R - 1] == '0') {
                b2[R - 1] = '1';
                if (R - 3 >= L && b2[R - 3] == '1') {
                    a2[R - 2] = '1';
                    cnt++;
                }
            }
        }
        while (R > it.r) {
            // 减
            if (R - 2 >= L && a[R] == '0' && a[R - 2] == '0' && b[R - 1] == '0') {
                if (R - 3 >= L && b2[R - 3] == '1') {
                    a2[R - 2] = '0';
                    cnt--;
                }
                b2[R - 1] = '0';
            }
            if (a[R] == '1') {
                cnt--;
            }

            if (R - 2 >= L && b[R] == '1' && b2[R - 2] == '1' && a[R - 1] == '0') {
                a2[R - 1] = '0';
                cnt--;
            }
            R--;
        }
        ans[it.idx] = cnt;
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}