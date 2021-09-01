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

vector< int > v1, v2;
vector< vector< vector< long long > > > dp;

long long dfs(int d, bool limit1, bool limit2) {
	if (d == -1) {
		return 1;
	}
	if (dp[d][limit1][limit2] != -1) return dp[d][limit1][limit2];
	int LIMIT1 = limit1 ? v1[d] : 1;
	int LIMIT2 = limit2 ? v2[d] : 1;
	long long res = 0;
	for (int i = 0; i <= LIMIT1; i++) {
		for (int j = 0; j <= LIMIT2; j++) {
			if (i == 1 && j == 1) continue;
			res += dfs(d - 1, limit1 && i == LIMIT1, limit2 && j == LIMIT2);
		}
	}
	dp[d][limit1][limit2] = res;
	return res;
}

long long work(int l, int r) {
	v1.clear(), v2.clear();
	for (int i = 0; i < 30; i++) {
		v1.push_back(l % 2);
		l /= 2;
	}
	for (int i = 0; i < 30; i++) {
		v2.push_back(r % 2);
		r /= 2;
	}
	dp.clear();
	dp.resize(30, vector< vector< long long > >(2, vector< long long >(2, -1)));
	// debug(dp[0][0][0]);

	return dfs(29, true, true);
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	// dp.resize(30, -1);
	int T;
	cin >> T;
	while (T--) {
		int l, r;
		cin >> l >> r;
		// debug(work(r, r));
		// debug(work(l - 1, r));
		cout << work(r, r) - work(l - 1, r) * 2 + work(l - 1, l - 1) << '\n';
	}
	return 0;
}