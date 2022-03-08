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
    ios::sync_with_stdio(false);
    cin.tie(0);
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
#endif
    int n1, n2, n3;
    cin >> n1 >> n2 >> n3;
    vector<vector<long long>> a;
    a.resize(4);
    a[1].resize(n1 + 1);
    long long sum[4] = {0};
    long long mi[4];
    const int inf = 0x3f3f3f3f;
    memset(mi, inf, sizeof(mi));
    for (int i = 1; i <= n1; i++) {
        cin >> a[1][i];
        sum[1] += a[1][i];
        mi[1] = min(mi[1], a[1][i]);
    }
    a[2].resize(n2 + 1);
    for (int i = 1; i <= n2; i++) {
        cin >> a[2][i];
        sum[2] += a[2][i];
        mi[2] = min(mi[2], a[2][i]);
    }
    a[3].resize(n3 + 1);
    for (int i = 1; i <= n3; i++) {
        cin >> a[3][i];
        sum[3] += a[3][i];
        mi[3] = min(mi[3], a[3][i]);
    }
    long long sum_mi = mi[1] + mi[2] + mi[3];
    long long all = sum[1] + sum[2] + sum[3];

    long long res = 0;
    for (int i = 1; i <= 3; i++) {
        // 选两个最小的
        res = max(res, all - (sum_mi - mi[i]) * 2);
        // 删掉一个数组
        res = max(res, all - sum[i] * 2);
    }
    cout << res << endl;
    return 0;
}
