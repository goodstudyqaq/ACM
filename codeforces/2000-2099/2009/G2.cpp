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
    int n, k, q;
    cin >> n >> k >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] -= i;
    }

    vector<int> ans(n - k + 1);

    map<int, int> cnt;
    set<pii> S;
    int r = 0;
    for (int i = 0; i <= n - k; i++) {
        while (r < i + k) {
            int before_cnt = cnt[a[r]];
            S.erase({before_cnt, a[r]});
            cnt[a[r]]++;
            S.insert({cnt[a[r]], a[r]});
            r++;
        }

        auto it = prev(S.end());
        ans[i] = k - it->first;

        S.erase({cnt[a[i]], a[i]});
        cnt[a[i]]--;
        if (cnt[a[i]]) {
            S.insert({cnt[a[i]], a[i]});
        }
    }

    vector<int> go(n - k + 1, -1);
    vector<int> stk;
    for (int i = n - k; i >= 0; i--) {
        while (stk.size() > 0 && ans[stk.back()] >= ans[i]) {
            stk.pop_back();
        }
        if (stk.size()) {
            go[i] = stk.back();
        }
        stk.push_back(i);
    }

    vector<vector<pii>> queries(n);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        r = r - k + 1;
        l--, r--;
        queries[l].push_back({r, i});
    }

    vector<long long> real_ans(q);
    for (int i = 0; i < n; i++) {
        if (queries[i].size()) {
            sort(queries[i].begin(), queries[i].end());
            int now = i;
            long long res = 0;
            for (int j = 0; j < queries[i].size(); j++) {
                int r = queries[i][j].first;
                while (true) {
                    int now_val = ans[now];
                    int _go = go[now];
                    if (_go == -1 || _go > r) {
                        long long tmp = res + 1LL * now_val * (r - now + 1);
                        real_ans[queries[i][j].second] = tmp;
                        break;
                    } else {
                        res += 1LL * now_val * (_go - now);
                        now = _go;
                    }
                }
            }
        }
    }
    for (int i = 0; i < q; i++) {
        cout << real_ans[i] << endl;
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
