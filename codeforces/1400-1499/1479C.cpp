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

    int L, R;
    cin >> L >> R;
    cout << "YES" << endl;
    int num = R - L;

    int one = 0;
    while (num) {
        one += num % 2;
        num /= 2;
    }

    int m = 30 * 29 / 2 + 30 + one + 1;

    cout << 32 << ' ' << m << endl;
    int tmp = 0;

    for (int i = 2; i <= 31; i++) {
        for (int j = i + 1; j <= 31; j++) {
            int w = 1 << (31 - j);
            if (w > 1e6) w = 1;

            cout << i << ' ' << j << ' ' << w << '\n';
            tmp++;
        }
        cout << i << ' ' << 32 << ' ' << 1 << '\n';
        tmp++;
    }

    cout << 1 << ' ' << 32 << ' ' << L << '\n';
    tmp++;
    int node = 31;
    num = R - L;
    int have = 1;
    while (num) {
        if (num % 2) {
            cout << 1 << ' ' << node << ' ' << L + have - 1 << '\n';
            tmp++;
            int w = 1 << (31 - node);
            have += w;
        }
        num /= 2;
        node--;
    }
    debug(tmp, m);
    return 0;
}