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

void solve() {
    int n;
    cin >> n;
    vector<pii> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].first >> p[i].second;
    }
    auto check_intersect = [&](int a, int b) {
        return min(p[a].second, p[b].second) >= max(p[a].first, p[b].first);
    };
    vector<pii> V;
    set<pii> S;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (check_intersect(i, j)) {
                pii tmp = {min(p[i].first, p[j].first), max(p[i].second, p[j].second)};
                V.push_back(tmp);
                S.insert(tmp);
            }
        }
    }

    sort(V.begin(), V.end(), [&](pii &a, pii &b) {
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    });

    int res = 0;
    for (int i = 0; i < V.size(); i++) {
        if (S.count(V[i]) == 0) continue;
        int right = V[i].second;
        res += 2;
        while (S.size() && S.begin()->first <= right) {
            S.erase(S.begin());
        }
    }
    cout << n - res << endl;
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