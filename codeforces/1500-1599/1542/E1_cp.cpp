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

int n, mod, mi[55];
int f[55][3000], sum[55][3000];
int dp[55];
int main() {
    freopen("data.in", "r", stdin);
    scanf("%d%d", &n, &mod);
    f[0][0] = 1;
    sum[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= i * (i - 1) / 2; j++) {
            for (int k = 0; k < i && j - k >= 0; k++)
                f[i][j] = (f[i][j] + f[i - 1][j - k]) % mod;
            if (j)
                sum[i][j] = (sum[i][j - 1] + f[i][j]) % mod;
            else
                sum[i][j] = f[i][j];
            debug(i, j, f[i][j], sum[i][j]);
        }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++)
            for (int k = j + 1; k <= i; k++)
                for (int q = k - j + 1; q <= i * (i - 1) / 2; q++)
                    dp[i] = (dp[i] + 1ll * f[i - 1][q] * sum[i - 1][q - (k - j + 1)]) % mod;
    }
    mi[0] = 1;
    for (int i = 1; i <= n; i++)
        mi[i] = 1ll * mi[i - 1] * (n - i + 1) % mod;
    int ans = dp[1];
    for (int i = 1; i <= n; i++) {
        ans = (ans + 1ll * mi[n - i] * dp[i]) % mod;
        cout << i << ' ' << dp[i] << endl;
    }
    printf("%d", ans);
}
