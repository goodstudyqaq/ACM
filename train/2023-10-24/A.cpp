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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    const int maxm = 30;
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    if (sum % n) {
        cout << "No" << endl;
        return;
    }
    int need = sum / n;
    debug(need);
    vector<int> two(maxm);
    two[0] = 1;
    map<int, int> two_set;
    two_set[1] = 0;
    for (int i = 1; i < maxm; i++) {
        two[i] = two[i - 1] * 2;
        two_set[two[i]] = i;
    }

    vector<int> magic1(maxm), magic2(maxm);
    vector<int> have1(maxm), have2(maxm);

    for (int i = 0; i < n; i++) {
        int val = a[i];
        if (val == need) continue;
        if (two_set.count(abs(val - need))) {
            if (val > need) {
                magic2[two_set[val - need]]++;
            } else {
                magic1[two_set[need - val]]++;
            }
        } else {
            bool flag = false;
            for (int j = 0; j < maxm; j++) {
                if (two_set.count((val + (1 << j)) - need)) {
                    have1[j]++;
                    have2[two_set[(val + (1 << j)) - need]]++;
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                debug(i);
                cout << "No" << endl;
                return;
            }
        }
    }
    debug(magic1, magic2, have1, have2);

    for (int i = 0; i < maxm - 1; i++) {
        int tmp = have1[i] - have2[i] + magic1[i] - magic2[i];
        if (abs(tmp) % 2) {
            cout << "No" << endl;
            return;
        }
        if (tmp > 0) {
            int half = tmp / 2;
            magic1[i] -= half;
            have1[i + 1] += half;
            if (magic1[i] < 0) {
                cout << "No" << endl;
                return;
            }
        } else if (tmp < 0) {
            int half = abs(tmp) / 2;
            magic2[i] -= half;
            have2[i + 1] += half;
            if (magic2[i] < 0) {
                cout << "No" << endl;
                return;
            }
        }
    }
    int tmp = have1[maxm - 1] - have2[maxm - 1] + magic1[maxm - 1] - magic2[maxm - 1];
    // for (int i = maxm - 1; i > 0; i--) {
    //     int tmp = have1[i] - have2[i] + magic1[i] - magic2[i];
    //     if (tmp > 0) {
    //         magic2[i - 1] -= tmp;
    //         have1[i - 1] += tmp;
    //         if (magic2[i - 1] < 0) {
    //             cout << "No" << endl;
    //             return;
    //         }
    //     } else if (tmp < 0) {
    //         tmp = abs(tmp);
    //         magic1[i - 1] -= tmp;
    //         have2[i - 1] += tmp;
    //         if (magic1[i - 1] < 0) {
    //             cout << "No" << endl;
    //             return;
    //         }
    //     }
    // }

    // int tmp = have1[0] - have2[0] + magic1[0] - magic2[0];
    if (tmp == 0) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
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