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

const unsigned long long hashsize = 19260817;
const int maxn = 3e6 + 5;
unsigned long long p[maxn + 10], S[maxn + 10];
void init() {
    p[0] = 1;
    for (int i = 1; i <= maxn; i++) {
        p[i] = p[i - 1] * hashsize;
    }
}

void buildhash(string& s) {
    for (int i = 1; i <= s.size(); i++) {
        S[i] = S[i - 1] * hashsize + s[i - 1];
    }
}

unsigned long long HS(int l, int r, string& s) {
    if (l == r) return s[l];
    l++, r++;
    return S[r] - S[l - 1] * p[r - l + 1];
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
#endif
    init();
    int n, k;
    cin >> n >> k;
    string res;
    cin >> res;

    for (int i = 0; i < k; i++) {
        res += res[i];
    }

    int g;
    cin >> g;
    for (int i = 1; i <= g; i++) {
        string s;
        cin >> s;
        res += s;
    }
    debug(res);

    // [0, (n + 1) * k - 1] [(n + 1) * k, (n + 1 + g) * k - 1]
    buildhash(res);
    unordered_map<unsigned long long, vector<int>> M;
    for (int i = 0; i < n * k; i++) {
        int l = i, r = l + k - 1;
        unsigned long long it = HS(l, r, res);
        M[it].push_back(i % k);
    }

    vector<int> num(k, 0);
    unordered_map<unsigned long long, vector<int>> M2;
    for (int i = (n + 1) * k; i < res.size(); i += k) {
        int l = i, r = l + k - 1;
        unsigned long long it = HS(l, r, res);
        M2[it].push_back((i - (n + 1) * k) / k + 1);
        unordered_set<int> S;
        for (auto it2 : M[it]) {
            if (S.count(it2)) continue;
            num[it2]++;
            S.insert(it2);
        }
    }

    int chose = -1;
    for (int i = 0; i < k; i++) {
        debug(i, num[i]);
        if (num[i] == n) {
            chose = i;
            break;
        }
    }
    if (chose == -1) {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;

    for (int i = chose; i < n * k; i += k) {
        int l = i, r = l + k - 1;
        unsigned long long it = HS(l, r, res);
        int idx = *M2[it].rbegin();
        M2[it].pop_back();
        cout << idx << ' ';
    }
    cout << endl;
    return 0;
}