#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;
typedef pair<int, int> pii;

void solve() {
    auto dist = [&](pii a, pii b) {
        return abs(a.first - b.first) + abs(a.second - b.second);
    };
    int n, k;
    cin >> n >> k;
    int mx = n * n - 1;
    pii dest = {(n + 1) / 2, (n + 1) / 2};
    if (k % 2 || k > mx || k < dist({1, 1}, dest)) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    if (k == n * n - 1) {
        cout << 0 << endl;
        return;
    }

    auto get_idx = [&](pii now) -> int {
        int depth = min({now.first, now.second, n - now.first + 1, n - now.second + 1});
        int length = n - (depth - 1) * 2 - 1;
        int ct = n * n - (length + 1) * (length + 1);
        // debug(ct);
        int idx = ct + 1;
        if (now.first == depth) {
            return idx + now.second - depth;
        } else if (n - now.second + 1 == depth) {
            idx += length;
            return idx + now.first - depth;
        } else if (n - now.first + 1 == depth) {
            idx += 2 * length;
            return idx + n - depth + 1 - now.second;
        } else {
            idx += 3 * length;
            return idx + n - depth + 1 - now.first;
        }
    };

    auto get_pii = [&](int idx) -> pii {
        pii now = {1, 1};
        while (idx >= get_idx(now)) {
            now.first++, now.second++;
        }
        now.first--;
        now.second--;
        int depth = now.first;
        vector<pii> V;
        V.push_back(now);
        V.push_back({depth, n - depth + 1});
        V.push_back({n - depth + 1, n - depth + 1});
        V.push_back({n - depth + 1, depth});
        int idx2 = 0;
        while (idx2 < 4 && idx >= get_idx(V[idx2])) {
            idx2++;
        }
        idx2--;
        if (idx2 == 0) {
            return {V[0].first, V[0].second + idx - get_idx(V[0])};
        } else if (idx2 == 1) {
            return {V[1].first + idx - get_idx(V[1]), V[1].second};
        } else if (idx2 == 2) {
            return {V[2].first, V[2].second - (idx - get_idx(V[2]))};
        } else {
            return {V[3].first - (idx - get_idx(V[3])), V[3].second};
        }
    };

    int idx = 1;

    int L = 1, R = n * n;  // 下标
    while (L <= R) {
        int mid = L + R >> 1;
        if (mid - 1 + dist(get_pii(mid), dest) <= k) {
            idx = mid;
            L = mid + 1;
        } else {
            R = mid - 1;
        }
    }
    int now_idx = idx;
    pii now = get_pii(idx);
    vector<pii> ans;
    while (now != dest) {
        while (now.first != dest.first) {
            pii go = now;
            if (now.first < dest.first) {
                go.first++;
            } else {
                go.first--;
            }
            int go_idx2 = get_idx(go);
            if (go_idx2 < idx) break;
            ans.push_back({idx, go_idx2});
            idx = go_idx2;
            now = go;
        }

        while (now.second != dest.second) {
            pii go = now;
            if (now.second < dest.second) {
                go.second++;
            } else {
                go.second--;
            }
            int go_idx2 = get_idx(go);
            if (go_idx2 < idx) break;
            ans.push_back({idx, go_idx2});
            idx = go_idx2;
            now = go;
        }
    }

    int real_ans = 0;
    for (auto v : ans) {
        if (v.second != v.first + 1) {
            real_ans++;
        }
    }

    cout << real_ans << endl;
    for (auto v : ans) {
        if (v.second != v.first + 1)
            cout << v.first << ' ' << v.second << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
}