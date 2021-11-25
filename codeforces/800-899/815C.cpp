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

const int maxn = 5001;
int c[maxn], d[maxn];
vector<int> V[maxn];
long long dp[maxn][maxn][2];
int sz[maxn];

// vector<int> c, d;
// vector<vector<int>> V;
// vector<vector<vector<long long>>> dp;
// vector<int> sz;

void dfs(int u, long long val) {
    dp[u][0][0] = 0;
    dp[u][1][0] = c[u];
    dp[u][1][1] = val + c[u] - d[u];

    sz[u] = 1;
    for (auto it : V[u]) {
        dfs(it, val + c[u] - d[u]);
        for (int i = sz[u]; i >= 0; i--) {
            for (int j = sz[it]; j >= 0; j--) {
                dp[u][i + j][0] = min(dp[u][i + j][0], dp[u][i][0] + dp[it][j][0]);
                dp[u][i + j][1] = min(dp[u][i + j][1], dp[u][i][1] + dp[it][j][0]);
                dp[u][i + j][1] = min(dp[u][i + j][1], dp[u][i][1] + dp[it][j][1] - val - (c[u] - d[u]));
            }
        }
        sz[u] += sz[it];
    }
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, b;
    cin >> n >> b;
    // c.resize(n + 1);
    // d.resize(n + 1);
    // V.resize(n + 1);
    // sz.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> c[i] >> d[i];
        if (i != 1) {
            int fa;
            cin >> fa;
            V[fa].push_back(i);
        }
    }

    // dp.resize(n + 1, vector<vector<long long>>(n + 1, vector<long long>(2, 1e13)));
    // fill(dp, dp[0] + maxn * maxn * 2, 1e13);

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j][0] = dp[i][j][1] = 1e13;
        }
    }

    dfs(1, 0);

    for (int i = n; i >= 0; i--) {
        debug(i, dp[1][i][0], dp[1][i][1]);
        if (dp[1][i][0] <= b || dp[1][i][1] <= b) {
            cout << i << endl;
            return 0;
        }
    }
    return 0;
}