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

#define lowbit(x) x & -x

const int mod = 1e9 + 7;
vector< int > V;
int k;
bool check(int val) {
	if (k == 0) return false;
	if (k == 1) {
		return V[0] == val;
	}
	return V[0] == val || V[1] == val;
}
int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	vector< int > a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	int LIMIT = 1 << n;

	vector< int > sum(LIMIT, 0);
	int one = 1 << (n + 1) - 1;
	int num = 0;

	for (int i = 1; i < LIMIT; i++) {
		int val = lowbit(i);
		if (val == i) {
			sum[i] = a[num++];
		} else {
			sum[i] = sum[i - val] + sum[val];
			if (sum[i] > 1e9 + 1) sum[i] = 1e9 + 1;
		}
	}

	cin >> k;
	for (int i = 0; i < k; i++) {
		int val;
		cin >> val;
		V.push_back(val);
	}

	vector< int > dp(LIMIT, 0);
	dp[0] = 1;
	for (int i = 1; i < LIMIT; i++) {
		if (check(sum[i])) {
			continue;
		}
		int now = i;
		while (now != 0) {
			int s = lowbit(now);
			int s2 = i - s;
			if (check(sum[s2]) == 0) {
				dp[i] = dp[i] + dp[s2];
				if (dp[i] > mod) dp[i] -= mod;
			}
			now -= s;
		}
	}
	cout << dp[LIMIT - 1] << endl;
	return 0;
}