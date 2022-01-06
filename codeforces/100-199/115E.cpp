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

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 2e5 + 5;
long long mx[maxn << 2], lazy[maxn << 2];

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

void update(int L, int R, long long val, int l, int r, int rt) {
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

long long query(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) {
        return mx[rt];
    }
    push_down(rt);
    int m = l + r >> 1;
    long long res = 0;
    if (L <= m) {
        res = max(res, query(L, R, lson));
    }
    if (R > m) {
        res = max(res, query(L, R, rson));
    }
    return res;
}

void update2(int L, long long val, int l, int r, int rt) {
    if (l == r) {
        mx[rt] = val;
        return;
    }
    push_down(rt);
    int m = l + r >> 1;
    if (L <= m) {
        update2(L, val, lson);
    } else {
        update2(L, val, rson);
    }
    push_up(rt);
}

typedef pair<int, int> pii;
int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<long long> sum(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> sum[i];
        sum[i] += sum[i - 1];
    }
    vector<vector<pii>> V;
    V.resize(n + 1);

    for (int i = 1; i <= m; i++) {
        int lb, ub, p;
        cin >> lb >> ub >> p;
        V[ub].push_back({lb, p});
    }

    vector<long long> dp;
    dp.resize(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];

        for (auto it : V[i]) {
            update(0, it.first - 1, it.second, 0, n, 1);
        }
        long long tmp = query(0, i - 1, 0, n, 1);
        tmp = tmp - sum[i];
        dp[i] = max(dp[i], tmp);
        update2(i, dp[i] + sum[i], 0, n, 1);
        debug(i, dp[i]);
    }
    cout << dp[n] << endl;
    return 0;
}