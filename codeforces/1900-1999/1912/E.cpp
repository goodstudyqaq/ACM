#include <bits/stdc++.h>

#include <algorithm>
#include <functional>
#include <numeric>

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

    long long p, q;
    cin >> p >> q;
    if (p == 0 && q == 0) {
        cout << 0 << endl;
        return 0;
    }

    auto get_small = [&](long long val) {
        // debug(val);
        if (val < 10) return val;
        vector<int> v;
        long long val2 = val;
        while (val2) {
            v.push_back(val2 % 10);
            val2 /= 10;
        }
        reverse(v.begin(), v.end());
        if (v[0] == 1) {
            // 1000000
            bool flag = true;
            for (int j = 1; j < v.size(); j++) {
                if (v[j] != 0) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                return val - 1;
            }
        }

        int n = v.size();

        for (int i = n / 2; i < n; i++) {
            v[i] = v[n - 1 - i];
        }

        long long res = 0;
        for (int i = 0; i < n; i++) {
            res = res * 10 + v[i];
        }
        if (res <= val) return res;

        if (v[n / 2] != 0) {
            v[n / 2]--;
            if (n % 2 == 0) {
                v[n / 2 - 1]--;
            }
            res = 0;
            for (int i = 0; i < n; i++) {
                res = res * 10 + v[i];
            }
            return res;
        } else {
            int now = n / 2;
            if (n % 2 == 0) now--;
            while (v[now] == 0) now--;
            v[now]--;
            for (int i = now + 1; i < n / 2; i++) {
                v[i] = 9;
            }
            for (int i = n / 2; i < n; i++) {
                v[i] = v[n - 1 - i];
            }
            res = 0;
            for (int i = 0; i < n; i++) {
                res = res * 10 + v[i];
            }
            return res;
        }
    };

    function<void(long long, long long)> work = [&](long long p, long long q) -> void {
        if (p == 0 && q == 0) return;
        if (abs(p - q) % 2) {
            cout << "12+";
            work(p - 12, q - 21);
            return;
        }

        // p q 现在同号
        long long tmp = (p + q) / 2;
        long long tmp2 = tmp;
        // debug(tmp);
        // 首先构造一个 tmp
        if (tmp > 0) {
            while (tmp) {
                long long val = get_small(tmp);
                cout << val << "+";
                tmp -= val;
            }
        } else {
            cout << "0-";
            tmp = -tmp;
            while (tmp) {
                long long val = get_small(tmp);
                cout << val << '-';
                tmp -= val;
            }
            cout << "0+";
        }

        p -= tmp2;
        q -= tmp2;
        // debug(p);
        if (p > 0) {
            while (p) {
                long long val = get_small(p);
                cout << val << "-0+";
                p -= val;
            }
        } else {
            cout << "0-";
            p = -p;
            while (p) {
                long long val = get_small(p);
                cout << val << "+0-";
                p -= val;
            }
        }
        cout << 0 << endl;
    };
    work(p, q);
}