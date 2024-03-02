#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;
typedef pair<int, int> pii;
typedef pair<pii, int> piii;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n;
    cin >> n;

    vector<int> a(n * 2);
    vector<piii> V;
    for (int i = 0; i < n * 2; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        V.push_back({{a[i], a[i + n]}, i});
    }
    sort(V.begin(), V.end());

    int now = 0;
    vector<int> choose;

    if (V[now].first.first >= V[now].first.second) {
        cout << V[now].first.first << ' ' << V[now].first.second << endl;
        return 0;
    }
    int go = now;
    while (go < n && V[now].first.first == V[go].first.first) go++;
    int mx = 0;
    int mi = n + 1;
    for (int i = now; i < go; i++) {
        choose.push_back(V[i].second);
        mx = max(mx, V[i].second);
        mi = min(mi, V[i].second);
    }
    debug(choose);
    int limit = a[mi + n];

    now = go;
    int r = mx;
    while (now < n) {
        if (V[now].first.first >= limit) break;
        go = now;
        while (go < n && V[now].first.first == V[go].first.first) go++;
        int tmpmx = -1;
        for (int i = now; i < go; i++) {
            if (V[i].second < r) continue;
            choose.push_back(V[i].second);
            tmpmx = max(tmpmx, V[i].second);
        }
        if (tmpmx != -1) {
            r = tmpmx;
        }
        now = go;
    }
    sort(choose.begin(), choose.end());
    for (auto it : choose) {
        cout << a[it] << ' ';
    }
    for (auto it : choose) {
        cout << a[it + n] << ' ';
    }
    cout << endl;
}