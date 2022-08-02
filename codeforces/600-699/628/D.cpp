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
const int mod = 1e9 + 7;

int m, _d;

vector< vector< vector< long long > > > dp;

long long dfs(int d, int pre, bool flag, bool limit, bool lead, string& s) {
	if (d == s.size()) {
		return pre == 0;
	}
	if (!limit && ~dp[d][pre][flag]) return dp[d][pre][flag];
	int End = limit ? s[d] - '0' : 9;
	long long res = 0;
	if (flag == 0) {
		int chose = _d;
		if (chose > End) return 0;
		res = (res + dfs(d + 1, (pre * 10 + chose) % m, 1, limit && chose == End, false, s));
	} else {

		if (_d == 0 && lead) {
			res = (res + dfs(d + 1, 0, 1, false, true, s));
			for (int i = 1; i <= End; i++) {
				res = (res + dfs(d + 1, (pre * 10 + i) % m, 0, limit && i == End, false, s)) % mod;
			}
		} else {
			for (int i = 0; i <= End; i++) {
				if (i == _d) continue;
				if (i == 0 && lead) {
					res = (res + dfs(d + 1, 0, 1, false, true, s));
				} else {
					res = (res + dfs(d + 1, (pre * 10 + i) % m, 0, limit && i == End, lead && i == 0, s)) % mod;
				}
			}
		}
	}
	if (!limit) {
		dp[d][pre][flag] = res;
	}
	// debug(d, pre, flag, limit, lead, dp[d][pre][flag], res);
	return res;
}

long long work(string& s) {
	long long val = dfs(0, 0, 1, true, true, s);
	debug(s, val);
	return val;
}

bool check(string& s) {
	int now = 0;
	for (int i = 0; i < s.size(); i++) {

		if (i % 2 && s[i] - '0' != _d) return false;
		if (i % 2 == 0 && s[i] - '0' == _d) return false;
		now = (now * 10 + s[i] - '0') % m;
	}
	return now == 0;
}

bool check2(int val) {
	vector< int > v;
	while (val) {
		v.push_back(val % 10);
		val /= 10;
	}
	reverse(v.begin(), v.end());
	for (int i = 0; i < v.size(); i++) {
		if (i % 2 && v[i] != _d) return false;
		if (i % 2 == 0 && v[i] == _d) return false;
	}
	return true;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> m >> _d;
	string a, b;
	cin >> a >> b;

	dp.resize(b.size(), vector< vector< long long > >(m, vector< long long >(2, -1)));

	long long val = ((work(b) - work(a)) % mod + mod) % mod;
	// long long val = work(a);

	val = (val + check(a)) % mod;
	cout << val << endl;

	// for (int i = 1; i * 19 <= 9999; i++) {
	// 	if (check2(i * 19)) {
	// 		cout << i * 19 << endl;
	// 	}
	// }

	return 0;
}