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
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, T;
    cin >> n >> T;

    vector<int> t(n + 1);
    vector<double> p(n + 1);
    for (int i = 1; i <= n; i++) {
        int the_p;
        cin >> the_p;
        cin >> t[i];
        p[i] = 1.0 * the_p / 100.0;
    }
    vector<vector<double>> dp;
    dp.resize(n + 1, vector<double>(T + 1, 0));
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = i; j - t[i] < i - 1 && j <= T; j++) {
            // 都没有
            dp[i][j] = dp[i][j - 1] * (1.0 - p[i]);
            dp[i][j] += dp[i - 1][j - 1] * p[i];
        }

        if (i - 1 + t[i] <= T) {
            int j = i - 1 + t[i];
            dp[i][j] = dp[i][j - 1] * (1.0 - p[i]);
            dp[i][j] += dp[i - 1][j - 1] * p[i];
            dp[i][j] += dp[i - 1][j - t[i]] * pow(1.0 - p[i], t[i]);
        }

        for (int j = i + t[i]; j <= T; j++) {
            double tmp = dp[i][j - 1];
            tmp -= dp[i - 1][j - t[i] - 1] * pow(1.0 - p[i], t[i] - 1);
            tmp = tmp * (1.0 - p[i]);
            tmp += dp[i - 1][j - 1] * p[i];
            tmp += dp[i - 1][j - t[i]] * pow(1.0 - p[i], t[i]);
            dp[i][j] = tmp;
        }
    }

    vector<double> dp2(n + 1);
    for (int i = 1; i <= n; i++) {
        dp2[i] = 0;
        double now = 1;
        for (int j = T; j >= 0; j--) {
            if (i != n && T - j >= t[i + 1]) break;
            dp2[i] += dp[i][j] * now;
            if (i != n) {
                now = now * (1.0 - p[i + 1]);
            }
        }
    }
    double ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += dp2[i] * i;
    }
    cout << fixed << setprecision(6);
    cout << ans << endl;
    return 0;
}