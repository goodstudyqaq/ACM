#include <bits/stdc++.h>

#include <limits>

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
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    const long long init = -1e7;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> idx;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            idx.push_back(i);
        }
    }

    auto check = [&]() -> bool {
        vector<long long> sum(n);
        for (int i = 0; i < n; i++) {
            if (i == 0) {
                sum[i] = a[i];
            } else {
                sum[i] = sum[i - 1] + a[i];
            }
        }

        long long mi = 0;
        long long mx_val = -numeric_limits<long long>::max() / 2;
        for (int i = 0; i < n; i++) {
            long long val = sum[i] - mi;
            mi = min(mi, sum[i]);
            mx_val = max(mx_val, val);
        }
        if (mx_val != k) {
            return false;
        }
        return true;
    };

    auto out = [&]() {
        for (int i = 0; i < n; i++) {
            cout << a[i] << ' ';
        }
        cout << '\n';
    };

    auto work = [&](int l, int r, int idx) {
        vector<long long> sum1(idx - l);
        for (int i = l; i < idx; i++) {
            if (i == l) {
                sum1[i - l] = a[i];
            } else {
                sum1[i - l] = sum1[i - l - 1] + a[i];
            }
        }

        vector<long long> sum2(r - idx);
        for (int i = r; i > idx; i--) {
            if (i == r) {
                sum2[r - i] = a[i];
            } else {
                sum2[r - i] = sum2[r - i - 1] + a[i];
            }
        }

        long long mi1 = 0;
        long long mx_val1 = -numeric_limits<long long>::max() / 2;
        long long last_val = 0;
        for (int i = 0; i < idx - l; i++) {
            last_val = sum1[i] - mi1;
            mi1 = min(mi1, sum1[i]);
            mx_val1 = max(mx_val1, last_val);
        }
        if (mx_val1 > k) {
            return;
        }
        if (mx_val1 == k) {
            a[idx] = init;
            return;
        }
        long long mi2 = 0;
        long long mx_val2 = -numeric_limits<long long>::max() / 2;
        long long last_val2 = 0;
        for (int i = 0; i < r - idx; i++) {
            last_val2 = sum2[i] - mi2;
            mi2 = min(mi2, sum2[i]);
            mx_val2 = max(mx_val2, last_val2);
        }
        if (mx_val2 > k) {
            return;
        }
        if (mx_val2 == k) {
            a[idx] = init;
            return;
        }
        last_val = max(last_val, 0LL);
        last_val2 = max(last_val2, 0LL);
        a[idx] = k - (last_val2 + last_val);
    };

    if (idx.size() == 0) {
        if (check()) {
            cout << "Yes\n";
            out();
        } else {
            cout << "No\n";
        }
        return;
    }

    for (int i = 0; i < idx.size() - 1; i++) {
        a[idx[i]] = init;
    }
    int l, r;
    if (idx.size() == 1) {
        l = 0, r = n - 1;
    } else {
        l = idx[idx.size() - 2] + 1, r = n - 1;
    }
    work(l, r, idx[idx.size() - 1]);
    debug(a);
    if (check()) {
        
        cout << "Yes\n";
        out();
    } else {
        cout << "No\n";
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