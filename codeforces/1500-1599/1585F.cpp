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
vector<int> dp, dp_sum;
int get_sum(int l, int r) {
    if (l == 0) {
        return dp_sum[r];
    }
    return (dp_sum[r] - dp_sum[l - 1]) % mod;
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n + 1);
    dp.resize(n + 1, 0);
    dp_sum.resize(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    a[0] = 0;

    vector<int> st(n + 2);
    int ncnt = 0;
    st[ncnt++] = 0;
    int sum = 0;
    dp[0] = 1;
    dp_sum[0] = 1;

    for (int i = 1; i <= n; i++) {
        while (ncnt > 0 && a[st[ncnt - 1]] > a[i]) {
            sum = (sum + 1LL * a[st[ncnt - 1]] * get_sum(st[ncnt - 2], st[ncnt - 1] - 1) % mod) % mod;
            ncnt--;
        }
        sum = (sum - 1LL * a[i] * get_sum(st[ncnt - 1], i - 1) % mod) % mod;
        dp[i] = sum;
        dp_sum[i] = (dp_sum[i - 1] + dp[i]) % mod;
        st[ncnt++] = i;
        debug(sum);
    }
    debug(dp);
    int ans = n % 2 ? -dp[n] : dp[n];
    ans = (ans + mod) % mod;
    cout << ans << endl;
    return 0;
}