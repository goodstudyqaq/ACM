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
    fast_ios(){
        // cin.tie(nullptr);
        // ios::sync_with_stdio(false);
        // cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n, m;
    cin >> n >> m;
    auto ask = [&](int x, int y) {
        cout << "? " << x << " " << y << endl;
        fflush(stdout);
        int res;
        cin >> res;
        return res;
    };
    auto out = [&](int x, int y) {
        cout << "! " << x << " " << y << endl;
        fflush(stdout);
    };

    int dis1 = ask(1, 1);

    // 得到一个 x - 1 + y - 1 = dis1 的线段 -> x + y = dis1 + 2

    int x2, y2;
    if (dis1 + 1 <= n) {
        x2 = dis1 + 1, y2 = 1;
    } else {
        x2 = n, y2 = dis1 + 2 - x2;
    }

    int x3, y3;
    if (dis1 + 1 <= m) {
        x3 = 1, y3 = dis1 + 1;
    } else {
        y3 = m, x3 = dis1 + 2 - y3;
    }

    int dis2 = ask(x2, y2);
    // 得到 abs(x - x2) + abs(y - y2) = dis2 的多个线段

    // 判断相交的点是否是答案
    int tmp = dis1 + dis2 + 2 + y2 - x2;
    if (tmp % 2 == 0) {
        int ansy = tmp / 2;
        int ansx = dis1 + 2 - ansy;
        if (ansx >= 1 && ansx <= n && ansy >= 1 && ansy <= m) {
            int the_dis = ask(ansx, ansy);
            if (the_dis == 0) {
                out(ansx, ansy);
                return;
            }
        }
    }

    int dis3 = ask(x3, y3);
    tmp = dis1 + dis3 + 2 + x3 - y3;
    int ansx = tmp / 2;
    int ansy = dis1 + 2 - ansx;
    out(ansx, ansy);
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
    return 0;
}