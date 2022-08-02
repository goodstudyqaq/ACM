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

typedef array<int, 3> a3;
vector<vector<a3> > V;

struct Edge {
    int u, v, w, idx, dep;
    bool operator<(const Edge& e) const {
        if (w != e.w) {
            return w < e.w;
        }
        return dep > e.dep;
    }
};
vector<Edge> edges;
vector<int> fa;
void dfs(int u, int pre, int d) {
    fa[u] = pre;
    for (auto it : V[u]) {
        int v = it[0];
        if (v == pre) continue;
        int idx = it[2];
        edges[idx].dep = d;
        dfs(v, u, d + 1);
    }
}

vector<int> f, f_num;
int find(int u) {
    return u == f[u] ? u : f[u] = find(f[u]);
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    V.resize(n + 1);
    fa.resize(n + 1);
    f.resize(n + 1);
    f_num.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        f[i] = i;
        f_num[i] = 1;
    }
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        V[u].push_back({v, w, i - 1});
        V[v].push_back({u, w, i - 1});
        edges.push_back((Edge){u, v, w, i});
    }

    dfs(1, -1, 1);
    sort(edges.begin(), edges.end());

    int now = 0;

    long long mx = 0;
    vector<long long> ans;
    ans.resize(n);
    vector<int> temp(n + 1);
    while (now < edges.size()) {
        int go = now;
        while (go < edges.size() && edges[go].w == edges[now].w) go++;

        for (int i = now; i < go; i++) {
            int u = edges[i].u, v = edges[i].v;
            if (fa[u] == v) swap(u, v);
            int fv = find(v);
            temp[v] = f_num[fv];
            int fu = find(u);
            f[fu] = fv;
            f_num[fv] += f_num[fu];
        }

        for (int i = now; i < go; i++) {
            int u = edges[i].u, v = edges[i].v;
            if (fa[u] == v) swap(u, v);
            long long val = 1LL * temp[v] * (f_num[find(u)] - temp[v]);
            int idx = edges[i].idx;
            ans[idx] = val;
            mx = max(mx, ans[idx]);
        }
        now = go;
    }

    vector<long long> real_ans;
    for (int i = 1; i < n; i++) {
        if (ans[i] == mx) {
            real_ans.push_back(i);
        }
    }
    cout << mx * 2 << ' ' << real_ans.size() << endl;

    for (auto it : real_ans) {
        cout << it << ' ';
    }
    cout << endl;
    return 0;
}