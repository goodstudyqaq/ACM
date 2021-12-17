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

typedef array<double, 3> a3;
vector<double> d;
vector<a3> V;
vector<double> res;
vector<double> c1, d1;

int N, M;
void tridiagonal_matrix_algorithm() {
    for (int i = 1; i <= M; i++) {
        double a, b, c, _d;
        a = V[i][0], b = V[i][1], c = V[i][2], _d = d[i];
        if (i == 1) {
            c1[i] = c / b;
            d1[i] = _d / b;
        } else {
            c1[i] = c / (b - a * c1[i - 1]);
            d1[i] = (_d - a * d1[i - 1]) / (b - a * c1[i - 1]);
        }
    }
    for (int i = M; i >= 1; i--) {
        if (i == M) {
            res[i] = d1[i];
        } else {
            res[i] = d1[i] - c1[i] * res[i + 1];
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;
    int x, y;
    cin >> x >> y;
    if (x == N) {
        cout << 0 << '\n';
        return 0;
    }
    if (M == 1) {
        cout << 2 * (N - x) << endl;
        return 0;
    }

    vector<double> ans(M + 1, 0);
    d.resize(M + 1);
    V.resize(M + 1);
    res.resize(M + 1);
    c1.resize(M + 1);
    d1.resize(M + 1);

    for (int j = 1; j <= M; j++) {
        if (j == 1) {
            V[j] = {0, 2.0 / 3.0, -1.0 / 3.0};
        } else if (j == M) {
            V[j] = {-1.0 / 3.0, 2.0 / 3.0, 0};
        } else {
            V[j] = {-0.25, 0.75, -0.25};
        }
    }

    for (int i = N - 1; i >= x; i--) {
        for (int j = 1; j <= M; j++) {
            if (j == 1) {
                d[j] = 1.0 + 1.0 / 3.0 * ans[j];
            } else if (j == M) {
                d[j] = 1.0 + 1.0 / 3.0 * ans[j];
            } else {
                d[j] = 1.0 + 0.25 * ans[j];
            }
        }
        tridiagonal_matrix_algorithm();
        for (int j = 1; j <= M; j++) {
            ans[j] = res[j];
        }
    }
    cout << fixed << setprecision(10);
    cout << ans[y] << endl;
    return 0;
}