<<<<<<< HEAD
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
	return to_string(( string )s);
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

const int mod = 998244353;

int quick(int a, int b) {
	int res = 1;
	while (b) {
		if (b % 2) res = 1LL * res * a % mod;
		b /= 2;
		a = 1LL * a * a % mod;
	}
	return res;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	vector< int > a(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	sort(a.begin() + 1, a.begin() + 1 + n);

	int mx_cnt = 0;
	int now = 1;

	vector< vector< int > > dp(n + 1, vector< int >(n + 1, 0));
	vector< vector< int > > sum(n + 1, vector< int >(n + 1, 0));
	dp[0][0] = 1;
	for (int i = 0; i <= n; i++) {
		sum[i][0] = 1;
	}
	int lst = 0;
	int win = 0;
	while (now <= n) {
		debug(now, lst);
		int go = now;
		while (go <= n && a[go] == a[now]) go++;
		//
		for (int i = 1; i <= n; i++) {
			dp[now][i] = 1LL * sum[lst][i - 1] * (go - now) % mod * quick(n - (i - 1), mod - 2) % mod;
			sum[now][i] = (dp[now][i] + sum[lst][i]) % mod;
			win = (win + 1LL * dp[now][i] * (go - now - 1) % mod * quick(n - i, mod - 2) % mod) % mod;
		}
		lst = now;
		now = go;
	}
	cout << win << endl;
	return 0;
=======
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

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

const int mod = 998244353;

int quick(int a, int b) {
    int res = 1;
    while (b) {
        if (b % 2) res = 1LL * res * a % mod;
        b /= 2;
        a = 1LL * a * a % mod;
    }
    return res;
}
vector< int > inv;
void init_inv(int n) {
    inv.resize(n + 1);
    inv[1] = 1;
    for (int i = 2; i <= n; i++) inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod;  //加mod不改变结果
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector< int > a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    init_inv(n);

    sort(a.begin() + 1, a.begin() + 1 + n);

    int mx_cnt = 0;
    int now = 1;

    vector< vector< int > > dp(n + 1, vector< int >(n + 1, 0));
    vector< vector< int > > sum(n + 1, vector< int >(n + 1, 0));
    dp[0][0] = 1;
    for (int i = 0; i <= n; i++) {
        sum[i][0] = 1;
    }
    int lst = 0;
    int win = 0;
    while (now <= n) {
        debug(now, lst);
        int go = now;
        while (go <= n && a[go] == a[now]) go++;
        //
        for (int i = 1; i <= n; i++) {
            dp[now][i] = 1LL * sum[lst][i - 1] * (go - now) % mod * inv[n - i + 1] % mod;
            // dp[now][i] = 1LL * sum[lst][i - 1] * (go - now) % mod * quick(n - i + 1, mod - 2) % mod;
            sum[now][i] = (dp[now][i] + sum[lst][i]) % mod;
            win = (win + 1LL * dp[now][i] * (go - now - 1) % mod * inv[n - i] % mod) % mod;
            // win = (win + 1LL * dp[now][i] * (go - now - 1) % mod * quick(n - i, mod - 2) % mod) % mod;
        }
        lst = now;
        now = go;
    }
    cout << win << endl;
    return 0;
>>>>>>> a49f6de434e0579257beef237cb49708bdae008b
}