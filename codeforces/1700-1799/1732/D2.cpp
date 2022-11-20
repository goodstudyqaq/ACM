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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int q;
    cin >> q;

    typedef pair<char, ll> pcl;
    vector<pcl> query(q);

    set<ll> S;
    map<ll, ll> M;
    S.insert(0);

    for (int i = 0; i < q; i++) {
        cin >> query[i].first >> query[i].second;
        if (query[i].first == '+') {
            S.insert(query[i].second);
        } else if (query[i].first == '-') {
            continue;
        } else {
            ll x = query[i].second;
            while (S.count(M[x] * x)) {
                M[x]++;
            }
        }
    }

    map<ll, set<ll>> M2;
    map<ll, set<int>> M3;
    for (auto it : M) {
        for (int i = 1; i <= it.second; i++) {
            ll val = it.first * i;
            M2[val].insert(it.first);
            M3[it.first].insert(i);
        }
    }
    // debug(M3);
    for (int i = 0; i < q; i++) {
        // debug(i);
        ll x = query[i].second;
        if (query[i].first == '+') {
            for (auto it : M2[x]) {
                M3[it].erase(x / it);
            }

        } else if (query[i].first == '-') {
            for (auto it : M2[x]) {
                M3[it].insert(x / it);
            }
        } else {
            // debug(M3[x]);
            cout << x * (*M3[x].begin()) << endl;
        }
    }
    return 0;
}