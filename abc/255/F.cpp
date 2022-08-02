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
vector<pii> V;

vector<int> P, I;
vector<int> Loc;
bool flag;
int dfs(int l1, int r1, int l2, int r2) {
    if (l1 == r1) {
        return P[l1];
    }
    int rt = P[l1];
    int idx = Loc[rt];
    if (idx < l2 || idx > r2) {
        flag = false;
        return 0;
    }
    int num = idx - l2 + 1;
    int the_r = l1 + num - 1;
    int left_node = 0, right_node = 0;
    if (the_r != l1) {
        left_node = dfs(l1 + 1, the_r, l2, idx - 1);
    }
    if (idx != r2) {
        right_node = dfs(the_r + 1, r1, idx + 1, r2);
    }

    V[rt].first = left_node;
    V[rt].second = right_node;
    return rt;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n;
    cin >> n;
    // P: 根左右 I：左根右
    P.resize(n + 1);
    I.resize(n + 1);
    Loc.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> P[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> I[i];
        Loc[I[i]] = i;
    }

    if (P[1] != 1) {
        cout << -1 << endl;
        return 0;
    }

    flag = true;
    V.resize(n + 1);
    dfs(1, n, 1, n);
    if (!flag) {
        cout << -1 << endl;
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        cout << V[i].first << ' ' << V[i].second << endl;
    }

    return 0;
}