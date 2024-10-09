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

struct Info {
    // 默认值
    int eq;
    Info(int eq = 1) : eq(eq) {
    }
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        return Info(left_info.eq & right_info.eq);
    }
    string to_string() {
        return "";
    }
};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(n + 1), b(m + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> real_next(n + 1);
    for (int i = 0; i < n; i++) {
        real_next[a[i]] = a[i + 1];
    }

    vector<set<int>> loc(n + 1);
    set<pii> S;
    S.insert({0, 0});

    for (int i = 1; i <= m; i++) {
        cin >> b[i];
        loc[b[i]].insert(i);
        if (loc[b[i]].size() == 1) {
            S.insert({i, b[i]});
        }
    }

    map<int, int> cnt;

    for (auto it = S.begin(); it != S.end(); it++) {
        auto it2 = next(it);
        if (it2 != S.end()) {
            cnt[real_next[it->second] == it2->second]++;
        }
    }
    debug(cnt);

    if (cnt[0]) {
        cout << "TIDAK" << endl;
    } else {
        cout << "YA" << endl;
    }

    auto remove = [&](int x, int val) {
        auto it = S.find({x, val});
        auto it2 = prev(it);
        cnt[real_next[it2->second] == val]--;
        auto it3 = next(it);
        if (it3 != S.end()) {
            cnt[real_next[it->second] == it3->second]--;
            cnt[real_next[it2->second] == it3->second]++;
        }
        S.erase({x, val});
    };

    auto add = [&](int x, int val) {
        // S.insert({x, val});
        auto it = S.lower_bound({x, val});
        auto it2 = prev(it);

        if (it != S.end()) {
            debug(cnt, it2->second);
            cnt[real_next[it2->second] == it->second]--;
            cnt[real_next[val] == it->second]++;
        }
        cnt[real_next[it2->second] == val]++;
        S.insert({x, val});
    };

    for (int i = 0; i < q; i++) {
        debug(S, loc, cnt);
        int x, val;
        cin >> x >> val;

        if (b[x] != val) {
            int before = b[x];
            loc[before].erase(x);
            b[x] = val;

            if (S.count({x, before})) {
                remove(x, before);
                if (loc[before].size()) {
                    add(*loc[before].begin(), before);
                }
            }
            if (loc[val].size() == 0) {
                add(x, val);
            } else if (*loc[val].begin() > x) {
                remove(*loc[val].begin(), val);
                add(x, val);
                debug(cnt);
            }
            loc[val].insert(x);
        }

        if (cnt[0]) {
            cout << "TIDAK" << endl;
        } else {
            cout << "YA" << endl;
        }
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