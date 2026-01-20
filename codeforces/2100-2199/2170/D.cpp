#include <bits/stdc++.h>

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

void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<int> vis(n);

    auto check1 = [&](char it) {
        if (it == 'X' || it == 'V') return true;
        return false;
    };

    int cnt1 = 0;
    // I?X 的个数
    for (int i = 0; i < n - 2; i++) {
        if (s[i] == 'I' && s[i + 1] == '?' && check1(s[i + 2])) {
            cnt1++;
            vis[i + 1] = 1;
        }
    }

    // ?X or ?V 的个数
    int cnt2 = 0;
    for (int i = 0; i < n - 1; i++) {
        if (vis[i] == 0 && s[i] == '?' && check1(s[i + 1])) {
            cnt2++;
            vis[i] = 1;
        }
    }

    // I? 的个数
    int cnt3 = 0;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == 'I' && vis[i + 1] == 0 && s[i + 1] == '?') {
            cnt3++;
            vis[i + 1] = 1;
        }
    }

    // ?? 有多少对
    int cnt4 = 0;
    for (int i = 0; i < n - 1; i++) {
        if (vis[i] == 0 && vis[i + 1] == 0 && s[i] == '?' && s[i + 1] == '?') {
            vis[i] = 1;
            vis[i + 1] = 1;
            cnt4++;
        }
    }
    // IX or IV
    int cnt5 = 0;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == 'I' && check1(s[i + 1])) {
            cnt5++;
        }
    }

    // ?
    int cnt6 = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '?') cnt6++;
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'X') {
            ans += 10;
        } else if (s[i] == 'V') {
            ans += 5;
        } else if (s[i] == 'I') {
            ans += 1;
        }
    }
    ans -= cnt5 * 2;

    while (q--) {
        int cx, cv, ci;
        cin >> cx >> cv >> ci;
        int tot = cnt6;
        int use_ci = min(ci, tot);
        tot -= use_ci;
        int use_cv = min(cv, tot);
        tot -= use_cv;
        int use_cx = tot;

        int use_cx_cv = use_cx + use_cv;

        int now_ans = ans;

        now_ans += use_cx * 10 + use_cv * 5 + use_ci;

        // ?X cnt2
        int tmp = min(cnt2, use_ci);
        now_ans -= 2 * tmp;
        use_ci -= tmp;

        // I? 的个数 cnt3
        tmp = min(cnt3, use_cx_cv);
        now_ans -= 2 * tmp;
        use_cx_cv -= tmp;

        // I?X 的个数 cnt1
        // use_ci use_cx_cv 谁多先用谁

        int now_cnt1 = cnt1;
        if (use_ci > use_cx_cv) {
            tmp = min(use_ci - use_cx_cv, now_cnt1);
            now_ans -= 2 * tmp;
            use_ci -= tmp;
            now_cnt1 -= tmp;
        } else if (use_ci < use_cx_cv) {
            tmp = min(use_cx_cv - use_ci, now_cnt1);
            now_ans -= 2 * tmp;
            use_cx_cv -= tmp;
            now_cnt1 -= tmp;
        }

        tmp = min(now_cnt1, use_ci + use_cx_cv);
        now_ans -= 2 * tmp;
        use_ci -= tmp / 2;
        use_cx_cv -= tmp / 2;
        if (tmp % 2) {
            use_ci -= 1;
        }

        // ?? cnt4
        tmp = min({cnt4, use_ci, use_cx_cv});
        now_ans -= 2 * tmp;
        cout << now_ans << '\n';
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