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

typedef pair<int, int> pp;
typedef pair<long long, pp> ppp;
const int maxn = 1e5 + 5;
int A[maxn], popular[maxn];
vector<pp> V[maxn];
long long d1[maxn], d2[maxn];
int belong1[maxn], belong2[maxn];

int main() {
#ifdef LOCAL
    // freopen("./data.in", "r", stdin);
#endif
    int N, M, K, L;
    cin >> N >> M >> K >> L;

    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    for (int i = 1; i <= L; i++) {
        int p;
        cin >> p;
        popular[i - 1] = p;
    }
    for (int i = 1; i <= M; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        V[u].emplace_back(make_pair(v, c));
        V[v].emplace_back(make_pair(u, c));
    }

    priority_queue<ppp, vector<ppp>, greater<ppp>> Q;

    const long long inf = numeric_limits<long long>::max() / 2;
    vector<vector<int>> vis = vector(N + 1, vector(2, 0));

    for (int i = 1; i <= N; i++) {
        d1[i] = d2[i] = inf;
        belong1[i] = belong2[i] = -1;
    }

    for (int i = 0; i < L; i++) {
        int p = popular[i];
        Q.push({0, {p, A[p]}});
        // d1[p] = 0;
        // belong1[p] = A[p];
    }

    while (!Q.empty()) {
        auto it = Q.top();
        long long ct = it.first;
        int u = it.second.first;
        int belong = it.second.second;
        Q.pop();

        if (d1[u] == inf) {
            d1[u] = ct;
            belong1[u] = belong;
        } else if (d2[u] == inf && belong != belong1[u]) {
            d2[u] = ct;
            belong2[u] = belong;
        } else {
            continue;
        }

        for (auto it2 : V[u]) {
            int v = it2.first;
            long long c = it2.second;
            long long d = c + ct;
            int bel = belong;
            Q.push({d, {v, bel}});
        }
    }
    for (int i = 1; i <= N; i++) {
        int a = A[i];
        long long ans = (belong1[i] == a) ? d2[i] : d1[i];
        if (ans == inf) ans = -1;
        cout << ans << ' ';
    }
    cout << endl;
    return 0;
}