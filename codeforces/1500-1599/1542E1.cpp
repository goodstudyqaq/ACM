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

vector<vector<int>> A;
void init(int n, int mod) {
    A.resize(n + 1, vector<int>(n + 1, 0));
    A[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        A[i][0] = 1;
        for (int j = 1; j <= n; j++) {
            A[i][j] = 1LL * i * A[i - 1][j - 1] % mod;
        }
    }
}

vector<vector<int>> dp, sum;

int n, mod;
int get_sum(int idx, int l, int r) {
    if (l > r) return 0;
    int res = sum[idx][r];
    if (l != 0) {
        return (res - sum[idx][l - 1]) % mod;
    }
    return res;
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> mod;
    init(n, mod);
    int m = n * (n - 1) / 2;
    dp.resize(n + 1, vector<int>(m + 1, 0));
    sum.resize(n + 1, vector<int>(m + 1, 0));
    dp[1][0] = 1;
    for (int i = 0; i <= m; i++) {
        sum[1][i] = 1;
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = get_sum(i - 1, max(j - i + 1, 0), j);
            sum[i][j] = dp[i][j];
            if (j != 0) {
                sum[i][j] = (sum[i][j] + sum[i][j - 1]) % mod;
            }
        }
    }
    debug(sum);
    debug(dp);
    debug(A);

    int res = 0;
    for (int i = 0; i < n; i++) {
        // 后面还有 n - i 个数
        int tmp = 0;
        int tmp_num = n - i;
        for (int j = 1; j <= tmp_num - 1; j++) {
            int tmp2 = 0;
            int tmp_m = (tmp_num * (tmp_num - 1)) / 2;
            for (int k = 0; k + j < tmp_m; k++) {
                int tmp3 = dp[n - i - 1][k];
                tmp3 = 1LL * tmp3 * ((sum[n - i - 1][tmp_m] - sum[n - i - 1][k + j]) % mod) % mod;
                // debug(tmp2);
                tmp2 = (tmp2 + tmp3) % mod;
            }
            tmp = (tmp + 1LL * tmp2 * ((tmp_num - j) % mod) % mod) % mod;
        }
        debug(i, tmp);
        res = (res + 1LL * A[n][i] * tmp % mod) % mod;
    }
    res = (res + mod) % mod;
    cout << res << endl;
    return 0;
}