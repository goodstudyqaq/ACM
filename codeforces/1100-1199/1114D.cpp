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
const int maxn = 5005;
int a[maxn];
int dp[2][maxn][maxn];

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    const int inf = 0x3f3f3f3f;
    memset(dp, inf, sizeof(dp));
    for (int l = 1; l <= n; l++) {
        for (int i = 1; i + l - 1 <= n; i++) {
            if (l == 1) {
                dp[0][i][i] = 0;
                dp[1][i][i] = 0;
            } else {
                int beg = i, ed = i + l - 1;
                dp[0][beg][ed] = min(dp[0][beg][ed], dp[0][beg + 1][ed] + (a[beg + 1] != a[beg]));
                dp[0][beg][ed] = min(dp[0][beg][ed], dp[1][beg + 1][ed] + (a[ed] != a[beg]));
                dp[1][beg][ed] = min(dp[1][beg][ed], dp[0][beg][ed - 1] + (a[beg] != a[ed]));
                dp[1][beg][ed] = min(dp[1][beg][ed], dp[1][beg][ed - 1] + (a[ed - 1] != a[ed]));
                debug(beg, ed, dp[0][beg][ed], dp[1][beg][ed]);
            }
        }
    }
    cout << min(dp[0][1][n], dp[1][1][n]) << endl;
    return 0;
}