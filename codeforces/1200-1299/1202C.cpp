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

pair< int, int > work2(vector< int >& v) {
	if (v.empty()) {
		return { 1, 1 };
	}
	int now = 0;
	vector< int > dp(v.size() + 1);
	dp[0] = 0;
	int mi = 0, mx = 0;
	for (int i = 0; i < v.size(); i++) {
		now += v[i];
		dp[i + 1] = now;
		mi = min(mi, now);
		mx = max(mx, now);
	}

	vector< int > v1, v2;
	for (int i = 0; i <= v.size(); i++) {
		if (dp[i] == mi) {
			v1.push_back(i);
		}
		if (dp[i] == mx) {
			v2.push_back(i);
		}
	}

	if (v2[0] - v1[v1.size() - 1] > 1 || v1[0] - v2[v2.size() - 1] > 1) {
		return { mx - mi + 1, mx - mi };
	} else {
		return { mx - mi + 1, mx - mi + 1 };
	}
}

long long work(string s) {
	vector< int > v1, v2;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == 'W') {
			v1.push_back(1);
		} else if (s[i] == 'S') {
			v1.push_back(-1);
		} else if (s[i] == 'A') {
			v2.push_back(-1);
		} else {
			v2.push_back(1);
		}
	}
	pair< int, int > res1 = work2(v1);

	pair< int, int > res2 = work2(v2);

	return min({ 1LL * res1.first * res2.first, 1LL * res1.first * res2.second, 1LL * res1.second * res2.first });
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--) {
		string s;
		cin >> s;
		cout << work(s) << endl;
	}
	return 0;
}