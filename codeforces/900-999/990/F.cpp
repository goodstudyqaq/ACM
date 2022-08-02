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
int n;
vector<int> s;
vector<pii> edges;
vector<int> f;
int find(int u) {
    return u == f[u] ? u : f[u] = find(f[u]);
}
typedef array<int, 3> a3;
vector<vector<a3>> V;
vector<int> ans;
vector<int> vis;

bool flag;
void dfs(int u, int pre, int pre_edge_idx, int pre_edge_flag) {
    vis[u] = 1;
    for (auto it : V[u]) {
        int v = it[0];
        if (v == pre) continue;
        dfs(v, u, it[1], it[2]);
    }
    int tmp = s[u];
    debug(u, tmp);
    if (pre == 0 && tmp != 0) {
        flag = false;
        return;
    }
    if (tmp == 0) {
        ans[pre_edge_idx] = 0;
    } else {
        ans[pre_edge_idx] = pre_edge_flag * tmp;
        s[pre] += tmp;
    }
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    s.resize(n + 1);
    f.resize(n + 1);
    V.resize(n + 1);
    vis.resize(n + 1);
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        sum += s[i];
    }

    if (sum != 0) {
        cout << "Impossible" << endl;
        return 0;
    }

    int m;
    cin >> m;

    edges.resize(m + 1);
    ans.resize(m + 1);

    int u, v;
    for (int i = 1; i <= m; i++) {
        cin >> u >> v;
        edges[i] = {u, v};
    }

    for (int i = 1; i <= n; i++) {
        f[i] = i;
    }
    for (int i = 1; i <= m; i++) {
        int u = edges[i].first, v = edges[i].second;
        int fu = find(u), fv = find(v);
        if (fu == fv) {
            ans[i] = 0;
        } else {
            V[u].push_back({v, i, 1});
            V[v].push_back({u, i, -1});
            f[fu] = fv;
        }
    }
    debug(V);

    flag = true;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        dfs(i, 0, 0, 0);
        if (!flag) {
            cout << "Impossible" << endl;
            return 0;
        }
    }
    cout << "Possible" << endl;
    for (int i = 1; i <= m; i++) {
        cout << ans[i] << '\n';
    }
    return 0;
}