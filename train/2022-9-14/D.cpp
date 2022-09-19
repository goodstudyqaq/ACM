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
    int n, m;
    cin >> n >> m;
    vector<int> x(n);
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    // vector<int> res_score = {3, 1, 4, 5, 2, 6};

    // int tmp_res = 0;
    // for (int i = 0; i < n; i++) {
    //     int tmp = 0;
    //     for (int j = 0; j < m; j++) {
    //         if (s[i][j] == '1') {
    //             tmp += res_score[j];
    //         }
    //     }
    //     tmp_res += abs(x[i] - tmp);
    // }
    // debug(tmp_res);

    int ans = -1;
    vector<int> ans_score(m);
    int LIMIT = 1 << n;
    for (int i = 0; i < LIMIT; i++) {
        vector<int> num(m);
        int res = 0;
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                // r[i] > x[i]
                res -= x[j];
                for (int k = 0; k < m; k++) {
                    if (s[j][k] == '1') {
                        num[k]++;
                    }
                }
            } else {
                // x[i] >= r[i]
                res += x[j];
                for (int k = 0; k < m; k++) {
                    if (s[j][k] == '1') {
                        num[k]--;
                    }
                }
            }
        }

        vector<int> idx(m);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](int a, int b) {
            return num[a] > num[b];
        });

        vector<int> score(m);
        int now_score = m;
        for (int i = 0; i < m; i++) {
            int the_idx = idx[i];
            score[the_idx] = now_score;
            now_score--;
        }

        bool flag = true;
        for (int j = 0; j < n && flag; j++) {
            int tmp = 0;
            for (int k = 0; k < m; k++) {
                if (s[j][k] == '1') {
                    tmp += score[k];
                }
            }

            if ((tmp > x[j]) == ((i >> j) & 1)) {
                if ((i >> j) & 1) {
                    res += tmp;
                } else {
                    res -= tmp;
                }
            } else {
                flag = false;
                break;
            }
        }
        if (flag) {
            if (ans < res) {
                ans = res;
                ans_score = score;
            }
        }
    }
    debug(ans);
    for (int i = 0; i < m; i++) {
        cout << ans_score[i] << ' ';
    }
    cout << endl;
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
}