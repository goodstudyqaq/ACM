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
typedef pair<pii, int> piii;
typedef pair<ll, ll> pll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

struct Intervals {
    set<pii> S;
    Intervals() {
        S.clear();
    }

    void add(int left, int right) {
        auto it = S.lower_bound({left + 1, -1});
        if (it != S.begin()) {
            if (prev(it)->second >= left) {
                it--;
            }
        }
        int L = left, R = right;
        while (it != S.end()) {
            if (it->first > right) break;
            L = min(L, it->first);
            R = max(R, it->second);
            it = S.erase(it);
        }
        S.insert({L, R});
    }

    pii get_interval(int idx) {
        debug(idx, S);
        auto it = S.lower_bound({idx + 1, -1});
        if (it == S.begin()) {
            return {-1, -1};
        }
        it--;
        if (it->second < idx) {
            return {-1, -1};
        }
        return *it;
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, m, q;
    cin >> n >> m >> q;
    vector<Intervals> V(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        V[a].add(b, c);
    }

    vector<pii> V2_temp;
    for (int i = 1; i <= n; i++) {
        for (auto it : V[i].S) {
            V2_temp.push_back(it);
        }
    }
    sort(V2_temp.begin(), V2_temp.end());
    vector<pii> V2;
    for (auto it : V2_temp) {
        if (V2.size() && it.second <= V2.back().second) {
            continue;
        }
        if (V2.size() && it.first == V2.back().first) {
            V2.pop_back();
        }
        V2.push_back(it);
    }
    //ok
    int sz = V2.size();
    int lg = __lg(sz);

    vector<vector<int>> jump = vector(sz, vector(lg + 1, 0));
    for (int i = 0, j = 0; i < sz; i++) {
        while (j + 1 < sz && V2[j + 1].first <= V2[i].second) {
            j++;
        }
        jump[i][0] = j;
    }
    for (int i = 1; i <= lg; i++) {
        for (int j = 0; j < sz; j++) {
            jump[j][i] = jump[jump[j][i - 1]][i - 1];
        }
    }
    //ok
    while (q--) {
        int x, y, z, w;
        cin >> x >> y >> z >> w;
        // x 大楼的 y 层走到 z 大楼的 w 层
        if (y > w) {
            swap(x, z);
            swap(y, w);
        }
        pii interval1 = V[x].get_interval(y);
        pii interval2 = V[z].get_interval(w);
        int ans = w - y;
        if (interval1.first != -1) {
            y = max(y, interval1.second);
        }
        if (interval2.first != -1) {
            w = min(w, interval2.first);
        }
        if (y >= w) {
            ans += (x != z);
        } else {
            // y < w
            auto it = lower_bound(V2.begin(), V2.end(), make_pair(y + 1, -1));
            if (it == V2.begin()) {
                ans = -1;
            } else {
                it--;
                if (y > it->second) {
                    ans = -1;
                } else {
                    int idx = it - V2.begin();
                    if (V2[idx].second >= w) {
                        ans += 2;
                    } else {
                        ans += 3;
                        for (int k = lg; k >= 0; k--) {
                            if (V2[jump[idx][k]].second < w) {
                                idx = jump[idx][k];
                                ans += (1 << k);
                            }
                        }
                        idx = jump[idx][0];
                        if (V2[idx].second < w) {
                            ans = -1;
                        }
                    }
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}