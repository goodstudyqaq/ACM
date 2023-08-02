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
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int now = 1;
    int score = 0;
    while (now <= n) {
        int go = now;
        int zero_num = 0;
        while (go <= n && a[go] == 0) {
            zero_num++;
            go++;
        }
        if (go == n + 1) {
            score += zero_num;
            break;
        }
        int go2 = go;
        bool have_two = false;

        while (go2 <= n && a[go2] != 0) {
            if (a[go2] == 2) have_two = true;
            go2++;
        }

        if (have_two == true) {
            // both side can be saved
            if (zero_num == 0) {
                score++;
                now = go2 + 1;
            } else {
                score += zero_num;
                now = go2 + 1;
            }
        } else {
            if (zero_num == 0) {
                score++;
                now = go2 + 1;
            } else {
                score += zero_num;
                now = go2;
            }
        }
    }
    cout << score << endl;
}