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

typedef pair<long long, long long> pii;
int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<pii> v(n + 1);
    long long a;
    for (int i = 0; i < n; i++) {
        cin >> a;
        long long now = a;
        pii it = {0, 0};
        while (now % 2 == 0) {
            now /= 2;
            it.first++;
        }
        it.second = now;
        v[i] = it;
    }
    v[n] = {0, 1};

    /*
    x = y 个连续的数的和的条件为
    1. y 是个奇数，那么只要 x % y = 0 即可
    2. y 是个偶数，那么和可以写成 2k + y / 2，所以 x 一定要是 y / 2 的奇数倍才可以，即 2x 是 y 的奇数倍
    设 x.b = x 的 2 的个数 x.l = 除 2 以外的因子的积那么有
    1. if y % 2 => x.l % y.l = 0
    2. else => x.l % y.l = 0 && x.b + 1 >= y.b 
    */

    auto ok = [&](int j, int i) {
        auto x = v[j], y = v[i];
        if (x.second % y.second != 0) return false;
        if (y.first == 0) return true;

        int tmp = i - j;
        if (y.first < tmp) {
            return true;
        }
        if (x.first + tmp == y.first) {
            return true;
        }
        return false;
    };

    vector<int> dp;
    dp.resize(n + 1);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        dp[i] = i;
        for (int j = 0; j < i; j++) {
            if (ok(j, i)) {
                dp[i] = min(dp[i], dp[j] + i - j - 1);
            }
        }
    }
    cout << dp[n] << endl;
    return 0;
}