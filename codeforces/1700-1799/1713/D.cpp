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
        // ios::sync_with_stdio(false);
        // cout << fixed << setprecision(10);
    };
} fast_ios_;

int ask(int a, int b) {
    cout << "? " << a << ' ' << b << endl;
    fflush(stdout);
    int res;
    cin >> res;
    return res;
}

void out(int res) {
    cout << "! " << res << endl;
    fflush(stdout);
}

void solve() {
    int n;
    cin >> n;
    // [1, 2 ^ n]
    int N = 1 << n;

    vector<int> res(N);
    for (int i = 1; i <= N; i++) {
        res[i - 1] = i;
    }

    while (N >= 1) {
        if (N == 1) {
            out(res[0]);
            break;
        } else if (N == 2) {
            int flag = ask(res[0], res[1]);
            if (flag == 1) {
                out(res[0]);
            } else {
                out(res[1]);
            }
            break;
        } else {
            vector<int> new_res(N / 4);
            for (int i = 0; i < N; i += 4) {
                int u = res[i], v = res[i + 2];
                int flag = ask(u, v);
                if (flag == 0) {
                    u = res[i + 1], v = res[i + 3];
                    flag = ask(u, v);
                } else if (flag == 1) {
                    v = res[i + 3];
                    flag = ask(u, v);
                } else {
                    u = res[i + 1];
                    flag = ask(u, v);
                }
                if (flag == 1) {
                    new_res[i / 4] = u;
                } else {
                    new_res[i / 4] = v;
                }
            }
            res = new_res;
            N = res.size();
        }
    }
    fflush(stdout);
}

int main() {
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}