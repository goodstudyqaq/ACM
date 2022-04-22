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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<string> s(n);
        for (int i = 0; i < n; i++) {
            cin >> s[i];
        }

        vector ans = vector(n, vector(m, '.'));

        auto work = [&](int idx) {
            int now = 0;
            while (now < n) {
                int go = now;
                while (go < n && s[go][idx] == 'o') {
                    ans[go][idx] = 'o';
                    go++;
                }

                if (go == n) break;

                int go2 = go;
                int a = 0, b = 0;
                while (go2 < n && s[go2][idx] != 'o') {
                    if (s[go2][idx] == '.') {
                        a++;
                    } else {
                        b++;
                    }
                    go2++;
                }

                for (int i = 0; i < a; i++) {
                    ans[go + i][idx] = '.';
                }
                for (int i = a; i < a + b; i++) {
                    ans[go + i][idx] = '*';
                }
                now = go2;
            }
        };

        for (int i = 0; i < m; i++) {
            work(i);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << ans[i][j];
            }
            cout << endl;
        }
        // cout << endl;
    }
    return 0;
}