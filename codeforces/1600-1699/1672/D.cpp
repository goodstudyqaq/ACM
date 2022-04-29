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

bool solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    map<int, int> M;
    int now = n;
    int nowb = n;
    while (now >= 1) {
        // debug(now, nowb, b[nowb], a[now]);
        if (b[nowb] == a[now]) {
            now--;
            nowb--;
            continue;
        }
        if (now == n) {
            return false;
        } else {
            while (nowb >= 1 && b[nowb] == b[nowb + 1]) {
                M[b[nowb]]++;
                nowb--;
            }
            if (b[nowb] == a[now]) {
                now--;
                nowb--;
            } else {
                if (M[a[now]] > 0) {
                    M[a[now]]--;
                    now--;
                } else {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int T;
    cin >> T;
    while (T--) {
        bool res = solve();
        if (res) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}