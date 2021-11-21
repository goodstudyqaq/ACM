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
vector<int> c;
vector<vector<int>> V;
vector<int> cnt;

vector<int> L, R, Node, big, sz;
vector<long long> ans;
int totdfn;

void dfs1(int u, int pre) {
    L[u] = ++totdfn;
    Node[totdfn] = u;
    sz[u] = 1;
    for (auto v : V[u]) {
        if (v == pre) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if (!big[u] || sz[big[u]] < sz[v]) big[u] = v;
    }
    R[u] = totdfn;
}

int mx_num;
long long res;

void add(int u) {
    cnt[c[u]]++;
    if (cnt[c[u]] > mx_num) {
        mx_num = cnt[c[u]];
        res = c[u];
    } else if (cnt[c[u]] == mx_num) {
        res += c[u];
    }
}

void del(int u) {
    if (cnt[c[u]] == mx_num) {
        res -= c[u];
    }
    cnt[c[u]]--;
}

long long get_ans() {
    return res;
}

void dfs2(int u, int pre, bool keep) {
    for (auto v : V[u]) {
        if (v == pre || v == big[u]) continue;
        dfs2(v, u, false);
    }

    if (big[u]) {
        dfs2(big[u], u, true);
    }

    add(u);
    for (auto v : V[u]) {
        if (v == pre || v == big[u]) continue;
        for (int i = L[v]; i <= R[v]; i++) {
            add(Node[i]);
        }
    }

    ans[u] = get_ans();
    if (keep == false) {
        for (int i = L[u]; i <= R[u]; i++) {
            del(Node[i]);
        }
        mx_num = 0;
    }
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    c.resize(n + 1);
    V.resize(n + 1);
    L.resize(n + 1);
    R.resize(n + 1);
    Node.resize(n + 1);
    big.resize(n + 1);
    sz.resize(n + 1);
    ans.resize(n + 1);
    cnt.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 0, false);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
    return 0;
}