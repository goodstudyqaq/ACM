#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> v;
    for (int i = 1; i <= sqrt(m); i++) {
        if (m % i == 0) {
            v.push_back(i);
            if (i != m / i) {
                v.push_back(m / i);
            }
        }
    }
    auto get_val = [&](int a, int g) {
        return a % g;
    };

    sort(v.begin(), v.end());
    int sz = v.size();
    map<int, int> idx;
    for (int i = 0; i < sz; i++) {
        idx[v[i]] = i;
    }
    vector<int> cnt(sz);
    for (int i = 0; i < sz; i++) {
        cnt[i] = 1;
        for (int j = 0; j < n - 1; j++) {
            int val1 = get_val(a[j], v[i]);
            int val2 = get_val(a[j + 1], v[i]);
            if (val1 > val2) {
                cnt[i]++;
            }
        }
    }

    auto get_mx_num = [&](int k, int g) {
        // 需要优化
        return m / g;
    };

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int i, x;
            cin >> i >> x;
            i--;
            // 去除之前的影响 i, i + 1
            if (i + 1 < n) {
                for (int j = 0; j < sz; j++) {
                    int val1 = get_val(a[i], v[j]);
                    int val2 = get_val(a[i + 1], v[j]);
                    if (val1 > val2) {
                        cnt[j]--;
                    }
                }
            }

            if (i - 1 >= 0) {
                for (int j = 0; j < sz; j++) {
                    int val1 = get_val(a[i - 1], v[j]);
                    int val2 = get_val(a[i], v[j]);
                    if (val1 > val2) {
                        cnt[j]--;
                    }
                }
            }

            a[i] = x;

            if (i + 1 < n) {
                for (int j = 0; j < sz; j++) {
                    int val1 = get_val(a[i], v[j]);
                    int val2 = get_val(a[i + 1], v[j]);
                    if (val1 > val2) {
                        cnt[j]++;
                    }
                }
            }

            if (i - 1 >= 0) {
                for (int j = 0; j < sz; j++) {
                    int val1 = get_val(a[i - 1], v[j]);
                    int val2 = get_val(a[i], v[j]);
                    if (val1 > val2) {
                        cnt[j]++;
                    }
                }
            }

        } else {
            int k;
            cin >> k;
            int g = gcd(k, m);
            if (g == 1) {
                cout << "Yes" << endl;
            } else {
                // debug(g, idx[g]);
                int num = cnt[idx[g]];
                // 段数
                int mx_num = get_mx_num(k, g);
                // debug(num, mx_num);
                if (num <= mx_num) {
                    cout << "Yes" << endl;
                } else {
                    cout << "No" << endl;
                }
            }
        }
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