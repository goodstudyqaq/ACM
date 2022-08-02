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

vector< int > v;
vector< vector< vector< long long > > > dp;

long long b, l, r;
long long dfs(int b, int d, int status, bool limit, bool lead) {
	if (d == -1) {
		return status == 0;
	}
	if (dp[b][d][status] != -1 && !limit && !lead) return dp[b][d][status];
	int LIMIT = limit ? v[d] : b - 1;
	long long res = 0;
	for (int i = 0; i <= LIMIT; i++) {
		if (lead && i == 0) {
			res += dfs(b, d - 1, status, limit & (i == LIMIT), true);
		} else {
			res += dfs(b, d - 1, status ^ (1 << i), limit & (i == LIMIT), lead & (i == 0));
		}
	}
	if (!limit && !lead) {
		dp[b][d][status] = res;
	}
	return res;
}

long long work(long long val, int d) {
	v.clear();
	while (val) {
		v.push_back(val % d);
		val /= d;
	}
	int sz = v.size();
	debug(sz);
	return dfs(d, sz - 1, 0, true, true);
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	dp.resize(11, vector< vector< long long > >(65, vector< long long >(1024, -1)));
	// dp.resize(65, vector< long long >(1024, -1));
	int q;
	cin >> q;
	while (q--) {
		cin >> b >> l >> r;
		cout << work(r, b) - work(l - 1, b) << endl;
	}
	return 0;
}