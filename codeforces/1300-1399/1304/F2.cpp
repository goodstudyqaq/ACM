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
const int maxn = 2e4 + 5;
int mx[maxn << 2], lazy[maxn << 2];

vector<vector<int>> dp;
int f;

void push_up(int rt) {
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
}

void push_down(int rt) {
    if (lazy[rt]) {
        mx[rt << 1] += lazy[rt];
        lazy[rt << 1] += lazy[rt];
        mx[rt << 1 | 1] += lazy[rt];
        lazy[rt << 1 | 1] += lazy[rt];
        lazy[rt] = 0;
    }
}

void build(int l, int r, int rt) {
    lazy[rt] = 0;
    if (l == r) {
        mx[rt] = dp[f][l];
        return;
    }
    int m = l + r >> 1;
    build(lson);
    build(rson);
    push_up(rt);
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

    int n, m, k;
    cin >> n >> m >> k;
    dp.resize(2, vector<int>(m + 1));
    vector<vector<int>> mp;
    vector<vector<int>> sum;
    sum.resize(n + 2, vector<int>(m + 1, 0));
    mp.resize(n + 2, vector<int>(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mp[i][j];
            sum[i][j] = mp[i][j] + sum[i][j - 1];
        }
    }

    if (n == 1) {
        int ans = 0;
        for (int i = 1; i <= m; i++) {
            int r = min(m, i + k - 1);
            ans = max(ans, sum[1][r] - sum[1][i - 1]);
        }
        cout << ans << endl;
        return 0;
    }

    for (int i = 1; i <= m; i++) {
        mp[n + 1][i] = 0;
    }

    for (int i = 1; i <= m; i++) {
        int r = min(m, i + k - 1);
        dp[0][i] = sum[1][r] - sum[1][i - 1] + sum[2][r] - sum[2][i - 1];
        debug(2, i, dp[1][i]);
    }
    f = 0;
    build(1, m, 1);

    for (int i = 3; i <= n + 1; i++) {
        for (int j = 1; j <= k; j++) {
            update(1, j, -mp[i - 1][j], 1, m, 1);
        }
        for (int j = 1; j <= m; j++) {
            int r = min(m, j + k - 1);
            dp[i % 2][j] = sum[i][r] - sum[i][j - 1] + sum[i - 1][r] - sum[i - 1][j - 1];
            dp[i % 2][j] += query();
            debug(i, j, dp[i % 2][j]);
            int l = max(1, j - k + 1);
            update(l, j, mp[i - 1][j], 1, m, 1);
            if (r + 1 <= m) {
                int rr = r + 1;
                int ll = rr - k + 1;
                update(ll, rr, -mp[i - 1][rr], 1, m, 1);
            }
        }
        if (i != n + 1) {
            f = i % 2;
            build(1, m, 1);
        }
    }

    int ans = 0;
    for (int i = 1; i <= m; i++) {
        ans = max(ans, dp[(n + 1) % 2][i]);
    }
    cout << ans << endl;
    return 0;
}