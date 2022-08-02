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

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
#endif

    long long W;
    cin >> W;
    vector<long long> cnt(9);
    for (int i = 1; i <= 8; i++) {
        cin >> cnt[i];
    }

    int lcm = 840;

    int LIMIT = 8 * lcm;
    vector<vector<long long> > dp(9, vector<long long>(8 * lcm, -1));
    dp[0][0] = 0;

    for (int i = 1; i <= 8; i++) {
        int limit = min(1LL * lcm - 1, cnt[i] * i);
        for (int j = 0; j < LIMIT; j++) {
            for (int k = 0; k * i <= min(limit, j); k++) {
                if (dp[i - 1][j - k * i] == -1) continue;
                dp[i][j] = max(dp[i][j], dp[i - 1][j - k * i] + (cnt[i] - k) * i / lcm);
            }
        }
    }
    long long res = 0;
    for (int i = 0; i <= min(1LL * LIMIT - 1, W); i++) {
        if (dp[8][i] == -1) continue;
        // debug(i, dp[8][i]);
        long long tmp = dp[8][i];
        long long left = W - i;
        left = left / lcm;
        left = min(left, tmp);
        res = max(res, left * lcm + i);
    }
    cout << res << endl;
    return 0;
}