#include <bits/stdc++.h>

using namespace std;

template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

string to_string(const string& s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string)s);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
    bool first = true;
    string res = "{";
    for (int i = 0; i < static_cast<int>(v.size()); i++) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(v[i]);
    }
    res += "}";
    return res;
}

template <size_t N>
string to_string(bitset<N> v) {
    string res = "";
    for (size_t i = 0; i < N; i++) {
        res += static_cast<char>('0' + v[i]);
    }
    return res;
}

template <typename A>
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

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}

void debug_out() {
    cerr << endl;
}

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

typedef pair<int, int> pii;
vector<vector<pii>> V;

vector<bool> vis;
vector<int> dis1, dis2, fa;
int mx_idx;
void dfs(int u, int pre) {
    fa[u] = pre;
    for (auto it : V[u]) {
        int v = it.first, w = it.second;
        if (v == pre || vis[v]) continue;
        dis1[v] = dis1[u] + w;
        if (dis1[mx_idx] < dis1[v]) {
            mx_idx = v;
        }
        dfs(v, u);
    }
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    V.resize(n + 1);
    vis.resize(n + 1);
    dis1.resize(n + 1);
    dis2.resize(n + 1);
    fa.resize(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        V[u].push_back({v, w});
        V[v].push_back({u, w});
    }

    if (n == 1) {
        cout << 0 << endl;
        return 0;
    }

    mx_idx = 1;
    dfs(1, 0);

    int start_idx = mx_idx;
    dis1[mx_idx] = 0;
    dfs(mx_idx, 0);
    int end_idx = mx_idx;

    int distance = dis1[end_idx];
    int now = end_idx;

    vector<int> V2;
    while (now != start_idx) {
        debug(now);
        V2.push_back(now);
        dis2[now] = distance - dis1[now];
        vis[now] = 1;
        now = fa[now];
    }
    debug("zz");
    V2.push_back(start_idx);
    dis2[start_idx] = distance;
    vis[start_idx] = 1;
    debug(V2);
    for (auto u : V2) {
        dis1[u] = 0;
        mx_idx = u;
        dfs(u, 0);
        int val = dis1[mx_idx];
        dis1[u] = val;
    }

    int m = V2.size();
    int j = 0;
    deque<pii> Q;
    int res = 1e9 + 1;

    k = min(k, m);

    for (int i = 0; i <= m - k; i++) {
        debug(i);
        while (j <= i + k - 1) {
            while (Q.size() && Q.back().second < dis1[V2[j]]) {
                Q.pop_back();
            }
            Q.push_back({j, dis1[V2[j]]});
            j++;
        }
        while (Q.size() && Q.front().first < i) {
            Q.pop_front();
        }
        int mx = Q.front().second;
        mx = max(mx, dis2[V2[i]]);
        mx = max(mx, distance - dis2[V2[j - 1]]);
        res = min(res, mx);
    }
    cout << res << endl;
    return 0;
}