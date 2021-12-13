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
vector<int> A, B;

int quick(int a, int b) {
    int res = 1;
    while (b) {
        if (b % 2) res = 1LL * res * a % mod;
        b /= 2;
        a = 1LL * a * a % mod;
    }
    return res;
}

void init(int n) {
    A.resize(n + 1);
    B.resize(n + 1);
    A[0] = 1;
    for (int i = 1; i <= n; i++) {
        A[i] = 1LL * A[i - 1] * i % mod;
    }
    B[n] = quick(A[n], mod - 2);
    for (int i = n - 1; i >= 0; i--) {
        B[i] = 1LL * B[i + 1] * (i + 1) % mod;
    }
}

int C(int n, int m) {
    return 1LL * A[n] * B[m] % mod * B[n - m] % mod;
}

int _A(int n, int m) {
    return 1LL * A[n] * B[n - m] % mod;
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, a, b;
    cin >> n >> m >> a >> b;

    if (n == 2) {
        cout << 1 << endl;
        return 0;
    }
    init(max(n - 2, m - 1));
    int res = 0;
    int ed = min(m, n - 1);

    int np = quick(n, n - 3);
    int mp = quick(m, n - 2);
    int invn = quick(n, mod - 2);
    int invm = quick(m, mod - 2);

    for (int e = 1; e <= ed; e++) {
        int val = 1LL * _A(n - 2, e - 1) * C(m - 1, e - 1) % mod * mp % mod * (e + 1) % mod * np % mod;
        res = (res + val) % mod;
        mp = 1LL * mp * invm % mod;
        np = 1LL * np * invn % mod;
    }
    cout << res << endl;
    return 0;
}