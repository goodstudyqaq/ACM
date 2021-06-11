#include <bits/stdc++.h>

using namespace std;

template < typename A, typename B >
string to_string(pair< A, B > p);

template < typename A, typename B, typename C >
string to_string(tuple< A, B, C > p);

template < typename A, typename B, typename C, typename D >
string to_string(tuple< A, B, C, D > p);

string to_string(const string& s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string)s);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

string to_string(vector< bool > v) {
    bool first = true;
    string res = "{";
    for (int i = 0; i < static_cast< int >(v.size()); i++) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(v[i]);
    }
    res += "}";
    return res;
}

template < size_t N >
string to_string(bitset< N > v) {
    string res = "";
    for (size_t i = 0; i < N; i++) {
        res += static_cast< char >('0' + v[i]);
    }
    return res;
}

template < typename A >
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

template < typename A, typename B >
string to_string(pair< A, B > p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template < typename A, typename B, typename C >
string to_string(tuple< A, B, C > p) {
    return "(" + to_string(get< 0 >(p)) + ", " + to_string(get< 1 >(p)) + ", " + to_string(get< 2 >(p)) + ")";
}

template < typename A, typename B, typename C, typename D >
string to_string(tuple< A, B, C, D > p) {
    return "(" + to_string(get< 0 >(p)) + ", " + to_string(get< 1 >(p)) + ", " + to_string(get< 2 >(p)) + ", " + to_string(get< 3 >(p)) + ")";
}

void debug_out() {
    cerr << endl;
}

template < typename Head, typename... Tail >
void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

const int maxn = 1e5 + 5;
int a[maxn], b[maxn];
int dp1[maxn], dp2[maxn];

int n;
int mx;
void work(int* x, int* y) {
    vector< int > v;

    for (int i = 1; i <= n; i++) {
        if (v.empty() || v[v.size() - 1] < x[i]) {
            v.push_back(x[i]);
            y[i] = v.size();
            continue;
        }
        int idx = lower_bound(v.begin(), v.end(), x[i]) - v.begin();
        v[idx] = x[i];
        y[i] = idx + 1;
    }
    mx = v.size();
}
int vis[maxn], ans[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        b[i] = -a[i];
    }
    reverse(b + 1, b + 1 + n);
    work(a, dp1);
    work(b, dp2);

    for (int i = 1; i <= n; i++) {
        if (dp1[i] + dp2[n - i + 1] - 1 == mx)
            vis[dp1[i]]++;
    }

    for (int i = 1; i <= n; i++) {
        if (dp1[i] + dp2[n - i + 1] - 1 != mx) {
            ans[i] = 1;
        } else if (vis[dp1[i]] > 1) {
            ans[i] = 2;
        } else {
            ans[i] = 3;
        }
        printf("%d", ans[i]);
    }
    return 0;
}