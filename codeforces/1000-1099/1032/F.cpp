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
const int mod = 998244353;

vector<vector<int>> V;

vector<vector<int>> dp;
int tmp[3];
void dfs(int u, int pre) {
    dp[u][2] = 1;
    for (auto v : V[u]) {
        if (v == pre) continue;
        dfs(v, u);
        tmp[0] = (1LL * dp[u][0] * ((dp[v][0] * 2 % mod + dp[v][2]) % mod)) % mod;
        tmp[0] = (tmp[0] + 1LL * (dp[u][1] + dp[u][2]) % mod * ((dp[v][1] + dp[v][2]) % mod)) % mod;
        tmp[1] = (1LL * dp[u][2] * dp[v][0] % mod + 1LL * dp[u][1] * ((1LL * dp[v][0] * 2 % mod + dp[v][2]) % mod) % mod) % mod;
        tmp[2] = (1LL * dp[u][2] * ((dp[v][0] + dp[v][2]) % mod)) % mod;
        dp[u][0] = tmp[0];
        dp[u][1] = tmp[1];
        dp[u][2] = tmp[2];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
#endif
    int n;
    cin >> n;
    V.resize(n + 1);
    dp.resize(n + 1, vector<int>(3));
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    dfs(1, 0);
    debug(dp);
    int ans = (dp[1][0] + dp[1][2]) % mod;
    cout << ans << endl;
    return 0;
}