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
const int maxn = 1005;
int dp[maxn][maxn][2];
int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    string x, y;
    cin >> x >> y;
    int xlen = x.size();
    int ylen = y.size();
    x = " " + x;
    y = " " + y;

    int ans = 0;
    int x_lst_eq = 1, y_lst_eq = 1;
    for (int i = 1; i <= xlen; i++) {
        if (x[i] == x[i - 1]) {
            x_lst_eq = i;
        }
        y_lst_eq = 1;
        for (int j = 1; j <= ylen; j++) {
            if (y[j] == y[j - 1]) {
                y_lst_eq = j;
            }
            // dp[i][j][0]
            if (i - 1 > 0 && x[i] != x[i - 1]) {
                dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j][0]) % mod;
            }
            if (i - 1 > 0 && x[i] != y[j]) {
                dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j][1]) % mod;
            }
            // dp[i][j][1]
            if (j - 1 > 0 && y[j] != y[j - 1]) {
                dp[i][j][1] = (dp[i][j][1] + dp[i][j - 1][1]) % mod;
            }
            if (j - 1 > 0 && y[j] != x[i]) {
                dp[i][j][1] = (dp[i][j][1] + dp[i][j - 1][0]) % mod;
            }

            if (x[i] != y[j]) {
                dp[i][j][0] = (dp[i][j][0] + (j - y_lst_eq + 1)) % mod;
                dp[i][j][1] = (dp[i][j][1] + (i - x_lst_eq + 1)) % mod;
            }
            debug(i, j, dp[i][j][0], dp[i][j][1]);
            ans = (ans + dp[i][j][0]) % mod;
            ans = (ans + dp[i][j][1]) % mod;
        }
    }
    cout << ans << endl;
    return 0;
}