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

const int maxm = 5e4;
vector<pii> v1(maxm), v2(maxm);
void init() {
    int nowx = 1, nowy = 1;
    for (int i = 0; i < maxm; i++) {
        v1[i] = {nowx, nowy};
        if (nowy != 1) {
            nowx += 3;
            nowy -= 3;
        } else {
            int sum = nowx + nowy;
            nowx = 1;
            nowy = sum + 2;
        }
    }

    nowx = 1, nowy = 2;
    for (int i = 0; i < maxm; i++) {
        v2[i] = {nowx, nowy};
        if (nowy == 1) {
            int sum = nowx + nowy;
            nowx = 1;
            nowy = sum + 2;
        } else {
            if (nowx % 3 == 1) {
                if (nowy == 2) {
                    nowx++;
                    nowy--;
                } else {
                    nowx++;
                    nowy -= 3;
                }
            } else {
                if (nowy % 3 == 2) {
                    nowy += 2;
                } else {
                    nowx += 2;
                    nowy -= 2;
                }
            }
        }
    }
}
void solve() {
    int n;
    cin >> n;

    debug(v1);
    debug(v2);
    int l1 = 0, l2 = 0;
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            cout << v1[l1].first << ' ' << v1[l1].second << '\n';
            l1++;
        } else {
            int val1 = v1[l1].first + v1[l1].second;
            int val2 = v2[l2].first + v2[l2].second;
            if (val1 < val2) {
                cout << v1[l1].first << ' ' << v1[l1].second << '\n';
                l1++;
            } else {
                cout << v2[l2].first << ' ' << v2[l2].second << '\n';
                l2++;
            }
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    init();
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}