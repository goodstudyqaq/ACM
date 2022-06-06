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
    fast_ios(){
        // cin.tie(nullptr);
        // ios::sync_with_stdio(false);
        // cout << fixed << setprecision(10);
    };
} fast_ios_;

int ask(string s) {
    cout << "? " << s << endl;
    fflush(stdout);
    int res;
    cin >> res;
    return res;
}

int main() {
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif
    int n, m;
    cin >> n >> m;

    string s(m, '0');
    typedef pair<int, int> pii;
    vector<pii> V;
    for (int i = 0; i < m; i++) {
        string a = s;
        a[i] = '1';
        int w = ask(a);
        V.push_back({w, i});
    }

    vector<int> f(n);
    iota(f.begin(), f.end(), 0);

    function<int(int)> find = [&](int u) -> int {
        return u == f[u] ? u : f[u] = find(f[u]);
    };

    sort(V.begin(), V.end());

    string now = s;
    int sum = 0;
    for (int i = 0; i < m; i++) {
        auto it = V[i];
        now[it.second] = '1';
        int tmp = ask(now);
        if (tmp == sum + it.first) {
            sum = tmp;
        } else {
            now[it.second] = '0';
        }
    }
    cout << "! " << sum << endl;
    return 0;
}