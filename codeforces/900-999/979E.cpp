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

const int mod = 1e9 + 7;

int quick(int a, int b) {
    int res = 1;
    while (b) {
        if (b % 2) res = 1LL * res * a % mod;
        b /= 2;
        a = 1LL * a * a % mod;
    }
    return res;
}

vector<int> A, B;

vector<vector<int>> sum;

int C(int a, int b) {
    return 1LL * A[a] * B[b] % mod * B[a - b] % mod;
}

void init(int n) {
    A.resize(n + 1);
    B.resize(n + 1);
    sum.resize(2, vector<int>(n + 1));

    A[0] = 1;
    for (int i = 1; i <= n; i++) {
        A[i] = 1LL * A[i - 1] * i % mod;
    }
    B[n] = quick(A[n], mod - 2);
    for (int i = n - 1; i >= 0; i--) {
        B[i] = 1LL * B[i + 1] * (i + 1) % mod;
    }
    sum[0][0] = 1, sum[0][1] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            (sum[j % 2][i] += C(i, j)) %= mod;
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, p;
    cin >> n >> p;
    init(n);

    vector<int> c;
    c.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }

    vector<int> two(n + 1);
    two[0] = 1;
    for (int i = 1; i <= n; i++) {
        two[i] = 1LL * two[i - 1] * 2 % mod;
    }

    vector<vector<vector<vector<int>>>> dp;
    // dp[i][ew][ow][eb] 前 i 个 结尾是白的路径偶数个点有 ew 个，结尾的白的路径奇数个的点有 ow 个，结尾是黑的路径偶数个点有 eb 个的方案数
    dp.resize(n + 1, vector<vector<vector<int>>>(n + 1, vector<vector<int>>(n + 1, vector<int>(n + 1, 0))));
    dp[0][0][0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int ew = 0; ew <= i; ew++) {
            for (int ow = 0; ow + ew <= i; ow++) {
                for (int eb = 0; ow + ew + eb <= i; eb++) {
                    if (dp[i][ew][ow][eb]) {
                        int ob = i - ew - ow - eb;
                        debug(i, ew, ow, eb, ob, dp[i][ew][ow][eb]);
                        if (c[i + 1] == 1) {
                            (dp[i + 1][ew][ow][eb + 1] += 1LL * two[eb + ob + ew] * dp[i][ew][ow][eb] % mod * sum[1][ow] % mod) %= mod;
                            (dp[i + 1][ew][ow][eb] += 1LL * two[eb + ob + ew] * dp[i][ew][ow][eb] % mod * sum[0][ow] % mod) %= mod;
                        } else if (c[i + 1] == 0) {
                            (dp[i + 1][ew + 1][ow][eb] += 1LL * two[ew + ow + eb] * dp[i][ew][ow][eb] % mod * sum[1][ob] % mod) %= mod;
                            (dp[i + 1][ew][ow + 1][eb] += 1LL * two[ew + ow + eb] * dp[i][ew][ow][eb] % mod * sum[0][ob] % mod) %= mod;
                        } else {
                            (dp[i + 1][ew][ow][eb + 1] += 1LL * two[eb + ob + ew] * dp[i][ew][ow][eb] % mod * sum[1][ow] % mod) %= mod;
                            (dp[i + 1][ew][ow][eb] += 1LL * two[eb + ob + ew] * dp[i][ew][ow][eb] % mod * sum[0][ow] % mod) %= mod;

                            (dp[i + 1][ew + 1][ow][eb] += 1LL * two[ew + ow + eb] * dp[i][ew][ow][eb] % mod * sum[1][ob] % mod) %= mod;
                            (dp[i + 1][ew][ow + 1][eb] += 1LL * two[ew + ow + eb] * dp[i][ew][ow][eb] % mod * sum[0][ob] % mod) %= mod;
                        }
                    }
                }
            }
        }
    }
    int res = 0;
    for (int ew = 0; ew <= n; ew++) {
        for (int ow = 0; ow + ew <= n; ow++) {
            for (int eb = 0; ow + ew + eb <= n; eb++) {
                int ob = n - ew - ow - eb;
                if ((ow + ob) % 2 == p) {
                    (res += dp[n][ew][ow][eb]) %= mod;
                }
            }
        }
    }
    cout << res << endl;
}