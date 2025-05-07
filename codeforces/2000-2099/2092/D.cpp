#include <bits/stdc++.h>

#include <algorithm>

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
    int n;
    string s;
    cin >> n >> s;

    map<char, int> M;
    M['T'] = 0;
    M['I'] = 1;
    M['L'] = 2;

    vector<int> cnt(3);
    list<int> L;
    for (int i = 0; i < n; i++) {
        cnt[M[s[i]]]++;
        L.push_back(M[s[i]]);
    }

    int times = 2 * n;
    vector<int> ans;

    auto check = [&]() {
        if (cnt[0] != cnt[1] || cnt[0] != cnt[2]) return false;
        return true;
    };

    while (!check() && times > 0) {
        int mi_idx = min_element(cnt.begin(), cnt.end()) - cnt.begin();
        auto now = L.begin();
        debug(mi_idx);
        int idx = 0;
        bool ok = false;
        debug(L);
        while (next(now) != L.end()) {
            int v1 = *now;
            int v2 = *next(now);
            if (v1 != v2 && v1 != mi_idx && v2 != mi_idx) {
                ans.push_back(idx);
                L.insert(next(now), mi_idx);
                ok = true;
                cnt[mi_idx]++;
                break;
            }
            now = next(now);
            idx++;
        }
        if (!ok) {
            int mi_idx2 = -1;
            for (int j = 0; j < 3; j++) {
                if (j != mi_idx) {
                    if (mi_idx2 == -1 || cnt[mi_idx2] > cnt[j]) {
                        mi_idx2 = j;
                    }
                }
            }

            now = L.begin();
            idx = 0;
            ok = false;
            while (next(now) != L.end()) {
                int v1 = *now;
                int v2 = *next(now);
                if (v1 != v2 && v1 != mi_idx2 && v2 != mi_idx2) {
                    ans.push_back(idx);
                    L.insert(next(now), mi_idx2);
                    ok = true;
                    cnt[mi_idx2]++;
                    break;
                }
                now = next(now);
                idx++;
            }
            if (!ok) break;
        }
        times--;
    }
    if (check()) {
        cout << ans.size() << '\n';
        for (auto it : ans) {
            cout << it + 1 << '\n';
        }
    } else {
        cout << -1 << '\n';
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