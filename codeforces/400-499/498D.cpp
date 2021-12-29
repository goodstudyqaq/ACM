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

vector<int> a;

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

const int maxn = 1e5 + 5;
const int M = 60;
int sum[M][maxn << 2];

void push_up(int rt) {
    for (int i = 0; i < M; i++) {
        sum[i][rt] = sum[i][rt << 1] + sum[(i + sum[i][rt << 1]) % M][rt << 1 | 1];
    }
}

void build(int l, int r, int rt) {
    if (l == r) {
        for (int i = 0; i < M; i++) {
            sum[i][rt] = 1 + ((i % a[l]) == 0);
        }
        return;
    }
    int m = l + r >> 1;
    build(lson);
    build(rson);
    push_up(rt);
}

int query(int L, int R, int t, int l, int r, int rt) {
    if (L <= l && r <= R) {
        // debug(L, R, t, l, r, rt, sum[t][rt]);
        return sum[t][rt];
    }
    int m = l + r >> 1;
    int res = 0;
    if (L <= m) {
        res += query(L, R, (t + res) % M, lson);
    }
    if (R > m) {
        res += query(L, R, (t + res) % M, rson);
    }
    // debug(L, R, t, l, r, rt, res);
    return res;
}

void update(int L, int val, int l, int r, int rt) {
    if (l == r) {
        for (int i = 0; i < M; i++) {
            sum[i][rt] = 1 + ((i % val) == 0);
        }
        return;
    }
    int m = l + r >> 1;
    if (L <= m) {
        update(L, val, lson);
    } else {
        update(L, val, rson);
    }
    push_up(rt);
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build(1, n, 1);
    int q;
    cin >> q;
    while (q--) {
        char c;
        int x, y;
        cin >> c >> x >> y;
        if (c == 'A') {
            cout << query(x, y - 1, 0, 1, n, 1) << '\n';
        } else {
            update(x, y, 1, n, 1);
        }
    }
    return 0;
}