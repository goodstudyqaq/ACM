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
const int X = 15, Y = 51, Z = 85;
const int maxn = 256;
string E[maxn], T[maxn], F[maxn];

bool f;
void update(string& a, const string& b) {
    if (a.size() == 0 || a.size() > b.size()) {
        a = b;
        f = true;
        return;
    } else if (a.size() == b.size()) {
        if (a > b) {
            a = b;
            f = true;
        }
    }
}

void init() {
    F[X] = 'x';
    F[Y] = 'y';
    F[Z] = 'z';

    while (true) {
        f = false;
        for (int i = 0; i < maxn; i++) {
            if (F[i] != "") {
                update(T[i], F[i]);
                for (int j = 0; j < maxn; j++) {
                    if (T[j] != "") {
                        update(T[i & j], T[j] + '&' + F[i]);
                    }
                }
            }
        }

        for (int i = 0; i < maxn; i++) {
            if (T[i] != "") {
                update(E[i], T[i]);
                for (int j = 0; j < maxn; j++) {
                    if (E[j] != "") {
                        update(E[i | j], E[j] + '|' + T[i]);
                    }
                }
            }
        }

        for (int i = 0; i < maxn; i++) {
            if (F[i] != "") {
                update(F[255 ^ i], '!' + F[i]);
            }
            if (E[i] != "") {
                update(F[i], '(' + E[i] + ')');
            }
        }
        if (!f) break;
    }
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    init();
    debug("zz");
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;

        int num = 0;
        for (int j = 0; j < 8; j++) {
            num = num * 2 + s[j] - '0';
        }
        cout << E[num] << '\n';
    }
    return 0;
}