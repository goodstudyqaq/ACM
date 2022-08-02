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

typedef pair< int, int > pii;
typedef pair< long long, pii > piii;
int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	vector< int > v[4];
	for (int i = 1; i <= n; i++) {
		int w, c;
		cin >> w >> c;
		v[w].push_back(c);
	}

	for (int i = 1; i <= 3; i++) {
		sort(v[i].begin(), v[i].end());
		reverse(v[i].begin(), v[i].end());
	}

	vector< piii > dp;
	dp.resize(m + 1, { 0, { 0, 0 } });
	dp[0] = { 0, { 0, 0 } };

	for (int i = 0; i <= m; i++) {
		if (i + 1 <= m) {
			int one_cnt = dp[i].second.first;
			if (one_cnt < v[1].size()) {
				if (dp[i + 1].first < dp[i].first + v[1][one_cnt]) {
					dp[i + 1].first = dp[i].first + v[1][one_cnt];
					dp[i + 1].second.first = dp[i].second.first + 1;
					dp[i + 1].second.second = dp[i].second.second;
				}
			}
		}
		if (i + 2 <= m) {
			int two_cnt = dp[i].second.second;
			if (two_cnt < v[2].size()) {
				if (dp[i + 2].first < dp[i].first + v[2][two_cnt]) {
					dp[i + 2].first = dp[i].first + v[2][two_cnt];
					dp[i + 2].second.first = dp[i].second.first;
					dp[i + 2].second.second = dp[i].second.second + 1;
				}
			}
		}
	}

	vector< long long > mx(m + 1, 0);
	for (int i = 1; i <= m; i++) {
		mx[i] = max(mx[i - 1], dp[i].first);
	}

	long long res = 0;
	int sum_w = 0;
	long long sum_c = 0;
	for (int i = 0; i <= v[3].size(); i++) {
		if (i > 0) {
			sum_w += 3;
			sum_c += v[3][i - 1];
		}
		int left_w = m - sum_w;
		if (left_w < 0) break;
		res = max(res, sum_c + mx[left_w]);
	}
	cout << res << endl;
	return 0;
}