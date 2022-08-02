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
    int N, K;
    cin >> N >> K;

    vector<vector<int>> V(K);

    for (int i = 0; i < N; i++) {
        int a;
        cin >> a;
        V[i % K].push_back(a);
    }

    for (int i = 0; i < K; i++) {
        sort(V[i].begin(), V[i].end());
    }

    vector<int> start(K, 0);

    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        a[i] = V[i % K][start[i % K]];
        start[i % K]++;
    }

    if (is_sorted(a.begin(), a.end())) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}