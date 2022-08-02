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

vector<int> tin, tout;
int T;
vector<vector<int>> V;
void dfs(int u) {
    T++;
    tin[u] = T;
    for (auto v : V[u]) {
        dfs(v);
    }
    tout[u] = T;
}

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

const int maxn = 1e6 + 5;
int mx[maxn << 2], lazy[maxn << 2];

void push_down(int rt) {
    if (lazy[rt]) {
        mx[rt << 1] += lazy[rt];
        lazy[rt << 1] += lazy[rt];
        mx[rt << 1 | 1] += lazy[rt];
        lazy[rt << 1 | 1] += lazy[rt];
        lazy[rt] = 0;
    }
}

void push_up(int rt) {
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
}

void update(int L, int R, int val, int l, int r, int rt) {
    if (L <= l && r <= R) {
        mx[rt] += val;
        lazy[rt] += val;
        return;
    }
    push_down(rt);
    int m = l + r >> 1;
    if (L <= m) {
        update(L, R, val, lson);
    }
    if (R > m) {
        update(L, R, val, rson);
    }
    push_up(rt);
}

int query() {
    return mx[1];
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);

    V.resize(n + 2);
    tin.resize(n + 2);
    tout.resize(n + 2);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> stk(n + 1);
    int scnt = 0;

    for (int i = n; i >= 1; i--) {
        while (scnt > 0 && a[stk[scnt - 1]] <= a[i]) {
            scnt--;
        }
        int u;
        if (scnt == 0) {
            u = n + 1;
        } else {
            u = stk[scnt - 1];
        }
        V[u].push_back(i);
        stk[scnt++] = i;
    }
    dfs(n + 1);

    for (int i = 1; i < k; i++) {
        int l = tin[i];
        int r = tout[i];
        update(l, r, 1, 1, n + 1, 1);
    }

    vector<int> ans(n - k + 2);
    for (int i = k; i <= n; i++) {
        int l = tin[i];
        int r = tout[i];
        update(l, r, 1, 1, n + 1, 1);
        ans[i - k + 1] = query();
        l = tin[i - k + 1];
        r = tout[i - k + 1];
        update(l, r, -1, 1, n + 1, 1);
    }
    for (int i = 1; i <= n - k + 1; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
    return 0;
}