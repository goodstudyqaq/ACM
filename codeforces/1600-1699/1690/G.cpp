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

const int maxn = 1e5 + 5;
int mi[maxn];

int n, m;
#define lowbit(x) x & -x
void add(int x, int val) {
    while (x <= n) {
        mi[x] = min(mi[x], val);
        x += lowbit(x);
    }
}

int query(int x) {
    int res = 1e9;
    while (x) {
        res = min(res, mi[x]);
        x -= lowbit(x);
    }
    return res;
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        mi[i] = 1e9;
    }

    vector<int> val(n + 1);
    vector<int> a(n + 1);
    val[0] = 1e9;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        val[i] = min(val[i - 1], a[i]);
        add(i, a[i]);
    }

    set<pii> S;
    map<int, pii> M;

    int now = 1;
    while (now <= n) {
        int go = now;
        while (go <= n && val[go] == val[now]) go++;
        S.insert({val[now], go - now});
        M[val[now]] = {now, go - 1};
        now = go;
    }
    debug(S, M);

    while (m--) {
        int k, d;
        cin >> k >> d;
        a[k] -= d;
        int the_val = query(k);
        if (the_val <= a[k]) {
            cout << S.size() << ' ';
            continue;
        }
        pii bef = M[the_val];

        auto it = S.find({the_val, bef.second - bef.first + 1});

        int num = 0;
        int right = k;
        while ((*it).first >= a[k]) {
            int the_val = it->first;
            num += it->second;
            right = M[the_val].second;
            M.erase(the_val);
            it = S.erase(it);
            if (it == S.begin()) {
                break;
            }
            it--;
        }
        if (k != bef.first) {
            M[the_val] = {bef.first, k - 1};
            S.insert({the_val, k - bef.first});
        }
        add(k, a[k]);
        M[a[k]] = {k, right};
        S.insert({a[k], right - k + 1});
        cout << S.size() << ' ';
    }
    cout << endl;
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