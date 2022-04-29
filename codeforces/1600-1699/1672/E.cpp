#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios(){
        // cin.tie(nullptr);
        // ios::sync_with_stdio(false);
        // cout << fixed << setprecision(10);
    };
} fast_ios_;

int ask(int w) {
    cout << "? " << w << endl;
    fflush(stdout);
    int height;
    cin >> height;
    return height;
}

int get_all_w(int n) {
    int l = n, r = 2001 * n;
    int ans = n;
    while (l <= r) {
        int mid = l + r >> 1;
        int height = ask(mid);
        if (height == 1) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

void out(int ans) {
    cout << "! " << ans << endl;
    fflush(stdout);
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    int all_w = get_all_w(n);
    int ans = all_w;

    for (int i = 2; i <= n; i++) {
        int tmp = all_w / i;
        int tmp2 = ask(tmp);
        if (tmp2 != 0) {
            ans = min(ans, tmp * tmp2);
        }
    }
    out(ans);
}