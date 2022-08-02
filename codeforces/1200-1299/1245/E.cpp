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

// x [0, 9] y [0, 9]
int get_idx(int x, int y) {
    if (x % 2) {
        // 从右边开始
        return 10 * x + (9 - y);
    } else {
        // 从左边开始
        return 10 * x + y;
    }
}
typedef pair<int, int> pii;
pii get_loc(int idx) {
    int x = idx / 10;
    if (x % 2) {
        int y = idx % 10;
        return {x, 9 - y};
    } else {
        int y = idx % 10;
        return {x, y};
    }
}
vector<vector<int>> mp;
int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    mp.resize(10, vector<int>(10));
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cin >> mp[i][j];
        }
    }
    int LIMIT = 10 * 10;
    vector<double> dp(LIMIT);
    dp[0] = 0;
    for (int i = 1; i <= 6; i++) {
        dp[i] = 6;
    }

    for (int i = 7; i < LIMIT; i++) {
        double res = 6;
        for (int j = 1; j <= 6; j++) {
            int go = i - j;
            pii loc = get_loc(go);
            int val = mp[loc.first][loc.second];
            // if (val == 0) {
            //     debug(loc.first, loc.second, go, get_idx(loc.first, loc.second));
            // }
            int go2 = get_idx(loc.first - val, loc.second);
            double tmp = min(dp[go], dp[go2]);
            res += tmp;
        }
        res /= 6.0;
        dp[i] = res;
    }
    cout << fixed << setprecision(10);
    cout << dp[LIMIT - 1] << endl;
}