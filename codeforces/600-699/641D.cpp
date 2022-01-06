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

typedef pair<long double, long double> pdd;

pdd work(long double a, long double b, long double c) {
    long double delta = fabs(b * b - 4 * a * c);
    long double x1 = (-b + sqrt(delta)) / (2.0 * a);
    long double x2 = (-b - sqrt(delta)) / (2.0 * a);
    if (x1 < x2) swap(x1, x2);
    return {x1, x2};
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<long double> mx, mi;
    mx.resize(n + 1);
    mi.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> mx[i];
        mx[i] += mx[i - 1];
    }
    for (int i = 1; i <= n; i++) {
        cin >> mi[i];
        mi[i] += mi[i - 1];
    }

    vector<long double> ans1, ans2;
    ans1.resize(n + 1);
    ans2.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        auto it = work(-1.0, mx[i] + mi[i], -mx[i]);
        ans1[i] = it.first;
        ans2[i] = it.second;
    }
    cout << fixed << setprecision(6);
    for (int i = 1; i <= n; i++) {
        cout << ans1[i] - ans1[i - 1] << ' ';
    }
    cout << endl;
    for (int i = 1; i <= n; i++) {
        cout << ans2[i] - ans2[i - 1] << ' ';
    }
    cout << endl;
    return 0;
}