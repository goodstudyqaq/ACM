#pragma GCC optimize(3)

#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;

template < typename A, typename B >
string to_string(pair< A, B > p);

template < typename A, typename B, typename C >
string to_string(tuple< A, B, C > p);

template < typename A, typename B, typename C, typename D >
string to_string(tuple< A, B, C, D > p);

string to_string(const string& s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string)s);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

string to_string(vector< bool > v) {
    bool first = true;
    string res = "{";
    for (int i = 0; i < static_cast< int >(v.size()); i++) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(v[i]);
    }
    res += "}";
    return res;
}

template < size_t N >
string to_string(bitset< N > v) {
    string res = "";
    for (size_t i = 0; i < N; i++) {
        res += static_cast< char >('0' + v[i]);
    }
    return res;
}

template < typename A >
string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto& x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

template < typename A, typename B >
string to_string(pair< A, B > p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template < typename A, typename B, typename C >
string to_string(tuple< A, B, C > p) {
    return "(" + to_string(get< 0 >(p)) + ", " + to_string(get< 1 >(p)) + ", " + to_string(get< 2 >(p)) + ")";
}

template < typename A, typename B, typename C, typename D >
string to_string(tuple< A, B, C, D > p) {
    return "(" + to_string(get< 0 >(p)) + ", " + to_string(get< 1 >(p)) + ", " + to_string(get< 2 >(p)) + ", " + to_string(get< 3 >(p)) + ")";
}

void debug_out() {
    cerr << endl;
}

template < typename Head, typename... Tail >
void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif
typedef pair< int, int > pii;
const int maxn = 1e5 + 5;
const int maxm = 55;
const int MAXN = maxn * maxm;
struct Edge {
    int u, v, nxt;
};
Edge edges[maxn];
int ecnt;
int head[maxn];
void add_edge(int u, int v) {
    edges[ecnt] = (Edge){u, v, head[u]};
    head[u] = ecnt++;
}

string g[maxn];
//

int DFN[MAXN], LOW[MAXN], vis[MAXN], id;
int belong[MAXN], cnt;
int stk[MAXN];
int tot1;

int weight[MAXN];
int n, m, d;

inline pii get_idx(int val) {
    return {val / d, val % d};
}
inline int get_val(pii it) {
    return it.first * d + it.second;
}
int mx_dep;
void tarjan(int u) {
    DFN[u] = LOW[u] = ++id;
    stk[tot1++] = u;
    vis[u] = 1;
    pii idx = get_idx(u);
    for (int i = head[idx.first]; ~i; i = edges[i].nxt) {
        int it = edges[i].v;
        int go = (idx.second + 1) % d;
        int v = get_val({it, go});
        if (!DFN[v]) {
            tarjan(v);
            LOW[u] = min(LOW[u], LOW[v]);
        } else if (vis[v]) {
            LOW[u] = min(LOW[u], DFN[v]);
        }
    }
    if (LOW[u] == DFN[u]) {
        cnt++;
        int v;
        do {
            v = stk[tot1 - 1];
            vis[v] = 0;
            belong[v] = cnt;
            tot1--;
        } while (v != u);
    }
}
vector< vector< int > > V2;

vector< int > dp;
void dfs(int u) {
    dp[u] = weight[u];
    int tmp = 0;
    for (auto v : V2[u]) {
        dfs(v);
        tmp = max(tmp, dp[v]);
    }
    dp[u] += tmp;
}

void solve() {
    memset(DFN, 0, sizeof(DFN));
    cnt = 0;
    debug(cnt);
    tarjan(0);
    debug(cnt);
    // 重新建图
    V2.resize(cnt + 1);
    dp.resize(cnt + 1);
    for (int i = 0; i < n; i++) {
        set< int > S2;
        for (int j = 0; j < d; j++) {
            int val = get_val({i, j});
            int u = belong[val];
            if (u == 0) continue;
            if (g[i][j] == '1' && !S2.count(u)) {
                weight[u]++;
                S2.insert(u);
            }
            set< int > S;
            for (int k = head[i]; ~k; k = edges[k].nxt) {
                int it = edges[k].v;
                int go = (j + 1) % d;
                int v2 = get_val({it, go});
                int v = belong[v2];
                if (v == 0) continue;
                if (u == v) continue;
                if (!S.count(v)) {
                    V2[u].push_back(v);
                    S.insert(v);
                }
            }
        }
    }

    int rt = belong[0];
    debug(rt, weight[rt]);
    dfs(rt);
    cout << dp[rt] << endl;
}
//

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
#endif
    cin >> n >> m >> d;
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        add_edge(u, v);
    }
    for (int i = 0; i < n; i++) {
        cin >> g[i];
    }
    solve();
    return 0;
}
