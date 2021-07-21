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
const long long inf = 1e18;
const int inf2 = 1000 * 5000 + 1;
struct node {
	vector< int > V;
	int max_pre_sum, last_pre_sum;
	int mx, mx_pre_sum;

	void work() {
		int now = 0;
		max_pre_sum = -inf2;
		for (auto v : V) {
			now += v;
			max_pre_sum = max(max_pre_sum, now);
		}
		last_pre_sum = now;

		vector< int > dp(V.size(), 0);
		mx = -inf2;
		for (int i = 0; i < V.size(); i++) {
			dp[i] = V[i];
			if (i != 0 && dp[i - 1] > 0) {
				dp[i] += dp[i - 1];
			}
			mx = max(mx, dp[i]);
		}
		mx_pre_sum = dp[V.size() - 1];
	}
};

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector< node > nodes(n + 1);
	for (int i = 1; i <= n; i++) {
		int l;
		cin >> l;
		nodes[i].V.resize(l);
		for (int j = 0; j < l; j++) {
			cin >> nodes[i].V[j];
		}
		nodes[i].work();
		debug(i, nodes[i].max_pre_sum, nodes[i].last_pre_sum, nodes[i].mx, nodes[i].mx_pre_sum);
	}
	vector< long long > dp1(m + 1), dp2(m + 1);
	long long ans = -inf;
	for (int i = 1; i <= m; i++) {
		int idx;
		cin >> idx;
		if (i == 0) {
			dp1[i] = nodes[idx].mx;
			dp2[i] = nodes[idx].mx_pre_sum;
		} else {
			dp1[i] = nodes[idx].mx;
			dp1[i] = max(dp1[i], 1LL * nodes[idx].max_pre_sum + dp2[i - 1]);
			dp2[i] = max(1LL * nodes[idx].mx_pre_sum, 1LL * nodes[idx].last_pre_sum + dp2[i - 1]);
		}
		debug(i, dp1[i], dp2[i]);
		ans = max(ans, dp1[i]);
	}
	cout << ans << endl;
}