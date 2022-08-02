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
int n, k;
vector<vector<int>> dp, sum;

int quick(int a, int b) {
    int res = 1;
    while (b) {
        if (b % 2) res = 1LL * res * a % mod;
        b /= 2;
        a = 1LL * a * a % mod;
    }
    return res;
}

void dfs(int u, int pre) {
    for (auto v : V[u]) {
        if (v == pre) continue;
        dfs(v, u);
    }

    int res = 1;
    for (auto v : V[u]) {
        if (v == pre) continue;
        res = 1LL * res * sum[v][k] % mod;
    }
    dp[u][0] = res;

    for (int i = 1; i <= k; i++) {
        if (i * 2 <= k) {
            int tmp1 = 1, tmp2 = 1;
            for (auto v : V[u]) {
                if (v == pre) continue;
                tmp1 = 1LL * tmp1 * ((sum[v][i - 1] + sum[v][k]) % mod) % mod;
                if (i == 1) {
                    tmp2 = 1LL * tmp2 * sum[v][k] % mod;
                } else {
                    tmp2 = 1LL * tmp2 * ((sum[v][i - 2] + sum[v][k]) % mod) % mod;
                }
            }
            tmp1 = (tmp1 - tmp2) % mod;
            dp[u][i] = tmp1;
        } else {
            int other = k - i;
            int tmp1 = 1;
            if (other) {
                vector<int> tmpv, tmpv2;
                for (auto v : V[u]) {
                    if (v == pre) continue;
                    tmp1 = 1LL * tmp1 * ((sum[v][other - 1] + sum[v][k]) % mod) % mod;
                    tmpv.push_back(tmp1);
                }

                tmp1 = 1;
                for (int j = V[u].size() - 1; j >= 0; j--) {
                    if (V[u][j] == pre) continue;
                    int v = V[u][j];
                    tmp1 = 1LL * tmp1 * ((sum[v][other - 1] + sum[v][k]) % mod) % mod;
                    tmpv2.push_back(tmp1);
                }

                int tmp2 = 0;
                int real_idx = 0;
                int sz = tmpv.size();
                debug("zz", sz);
                for (int j = 0; j < V[u].size(); j++) {
                    int v = V[u][j];
                    if (v == pre) continue;
                    int tmp = dp[v][i - 1];
                    debug(real_idx);
                    if (real_idx != 0) {
                        tmp = 1LL * tmp * tmpv[real_idx - 1] % mod;
                    }
                    if (real_idx != sz - 1) {
                        tmp = 1LL * tmp * tmpv2[sz - 2 - real_idx] % mod;
                    }
                    tmp2 = (tmp2 + tmp) % mod;
                    real_idx++;
                }
                dp[u][i] = tmp2;
            } else {
                vector<int> tmpv, tmpv2;
                int tmp1 = 1;
                for (auto v : V[u]) {
                    if (v == pre) continue;
                    tmp1 = 1LL * tmp1 * sum[v][k] % mod;
                    tmpv.push_back(tmp1);
                }
                tmp1 = 1;
                for (int j = V[u].size() - 1; j >= 0; j--) {
                    int v = V[u][j];
                    if (v == pre) continue;
                    tmp1 = 1LL * tmp1 * sum[v][k] % mod;
                    tmpv2.push_back(tmp1);
                }
                int real_idx = 0;
                int sz = tmpv.size();
                debug(sz);
                tmp1 = 0;
                for (int j = 0; j < V[u].size(); j++) {
                    int v = V[u][j];
                    if (v == pre) continue;
                    int tmp = dp[v][i - 1];
                    if (real_idx != 0) {
                        tmp = 1LL * tmp * tmpv[real_idx - 1] % mod;
                    }
                    if (real_idx != sz - 1) {
                        tmp = 1LL * tmp * tmpv2[sz - 2 - real_idx] % mod;
                    }
                    debug(tmp);
                    tmp1 = (tmp1 + tmp) % mod;
                    real_idx++;
                }
                dp[u][i] = tmp1;
            }
        }
    }
    for (int i = 0; i <= k; i++) {
        sum[u][i] = dp[u][i];
        if (i != 0) {
            sum[u][i] = (sum[u][i] + sum[u][i - 1]) % mod;
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> k;
    V.resize(n + 1);
    dp.resize(n + 1, vector<int>(k + 1, 0));
    sum.resize(n + 1, vector<int>(k + 1, 0));
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }
    if (k == 0) {
        cout << 1 << endl;
        return 0;
    }
    dfs(1, 0);
    int res = 0;
    for (int i = 0; i <= k; i++) {
        res = (res + dp[1][i]) % mod;
    }
    debug(dp);
    res = (res + mod) % mod;
    cout << res << endl;
    return 0;
}