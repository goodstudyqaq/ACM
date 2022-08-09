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

struct Node {
    ll pre, suf;
    ll ans;
    ll sum;
};

const int maxn = (1 << 18) + 10;
vector<Node> nodes[maxn << 2];

vector<ll> a;

Node merge(Node a, Node b) {
    Node res;
    res.pre = max(a.pre, a.sum + b.pre);
    res.suf = max(b.suf, b.sum + a.suf);
    res.sum = a.sum + b.sum;
    res.ans = max({a.ans, b.ans, a.suf + b.pre});
    return res;
}

void push_up(int rt, int len) {
    int m = len / 2;
    for (int i = 0; i < m; i++) {
        nodes[rt][i] = merge(nodes[rt << 1][i], nodes[rt << 1 | 1][i]);
        nodes[rt][i + m] = merge(nodes[rt << 1 | 1][i], nodes[rt << 1][i]);
    }
}

void build(int l, int r, int rt) {
    nodes[rt].resize(r - l + 1);
    if (l == r) {
        nodes[rt][0].sum = a[l];
        nodes[rt][0].pre = nodes[rt][0].suf = nodes[rt][0].ans = max(0LL, a[l]);
        return;
    }
    int m = l + r >> 1;
    build(l, m, rt << 1);
    build(m + 1, r, rt << 1 | 1);
    push_up(rt, r - l + 1);
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    int N = 1 << n;
    a.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    build(0, N - 1, 1);
    int q;
    cin >> q;
    int now = 0;
    debug(nodes[1][0].ans);
    while (q--) {
        int k;
        cin >> k;
        now ^= (1 << k);
        cout << nodes[1][now].ans << endl;
    }
    return 0;
}