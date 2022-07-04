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

int get_val(char it) {
    if (it == '(')
        return 1;
    else
        return -1;
}

void solve() {
    int n;
    string s;
    cin >> n >> s;
    int N = n * 2;
    int now = 0;

    int val = 0;
    vector<pii> ans;

    auto get_right = [&](int left) -> pii {
        int now_score = 0;
        int mx = 0;
        pii res = {-1, -1};
        for (int i = left; i < N; i++) {
            now_score += get_val(s[i]);
            if (now_score - mx < -val) continue;
            res = {i, now_score};
            mx = max(mx, now_score);
        }
        return res;
    };

    while (now < N) {
        int go = now;
        int mx_idx = now - 1;
        int mx_val = val;
        while (go < N && get_val(s[go]) + val >= 0) {
            val += get_val(s[go]);
            if (mx_val < val) {
                mx_val = val;
                mx_idx = go;
            }
            go++;
        }
        if (go == N) break;
        // [now, go] 是 ok 的
        debug(mx_idx, now);
        val = mx_val;
        int left = mx_idx + 1;
        pii info = get_right(left);
        debug(info);
        ans.push_back({left, info.first});
        now = info.first + 1;
        val += info.second;
    }

    cout << ans.size() << endl;
    for (auto it : ans) {
        cout << it.first + 1 << ' ' << it.second + 1 << endl;
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
}