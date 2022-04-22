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

//时间复杂度O(n)
const int maxn = 1e5 + 5;
bool is[maxn];
int prm[maxn], id;
// 每个数的最小质因子
int minp[maxn];
void get_prime() {
    /*
    数被筛掉的顺序：3 -> 3^2 -> 2*3^2 -> 2^2 * 3^2
    即从最大的质数去填
    */
    int k = 0;
    memset(is, 1, sizeof(is));
    is[0] = is[1] = 0;
    for (int i = 2; i < maxn; ++i) {
        if (is[i]) {
            prm[k++] = i;
            minp[i] = i;
        }
        for (int j = 0; j < k && (i * prm[j] < maxn); ++j) {
            is[i * prm[j]] = 0;
            minp[i * prm[j]] = prm[j];
            if (i % prm[j] == 0) break;
        }
    }
    id = k;
}

bool is_prime(int val) {
    for (int i = 0; i < id && 1LL * prm[i] * prm[i] <= val; i++) {
        if (val % prm[i] == 0) return false;
    }
    return true;
}

void no() {
    cout << "no" << endl;
}

void yes() {
    cout << "yes" << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    get_prime();
    int T;
    cin >> T;
    while (T--) {
        int x, d;
        cin >> x >> d;

        bool f1 = is_prime(d);

        int _x = x;
        int d_num = 0;
        while (_x % d == 0) {
            _x /= d;
            d_num++;
        }

        if (d_num < 2) {
            no();
            continue;
        }
        debug(d_num, _x);
        // d_num >= 2
        int tmp = _x;
        if (tmp == 1) {
            if (d_num == 2 || f1) {
                no();
            } else {
                yes();
            }
        } else {
            bool f = is_prime(tmp);
            debug(f);
            if (!f) {
                yes();
            } else {
                debug(f1);
                if (f1) {
                    no();
                } else {
                    if (d_num == 3) {
                        if (1LL * tmp * tmp == d && is_prime(tmp)) {
                            no();
                        } else {
                            yes();
                        }
                    } else if (d_num == 2) {
                        no();
                    } else {
                        yes();
                    }
                }
            }
        }
    }
    return 0;
}