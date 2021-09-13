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

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	vector< int > x(n + 1);
	int val = 0;
	for (int i = 1; i <= n; i++) {
		cin >> x[i];
		val += x[i];
	}

	if (m == 1) {
		cout << 1 << endl;
		return 0;
	}

	int LIMIT = n * m;
	vector< vector< double > > E(2, vector< double >(LIMIT + 1, 0)), sum(2, vector< double >(LIMIT + 1, 0));

	E[0][0] = m - 1;
	for (int i = 0; i <= LIMIT; i++) {
		sum[0][i] = m - 1;
	}

	for (int i = 1; i <= n; i++) {
		int now_idx = i % 2;
		int no_chose = x[i];
		fill(E[now_idx].begin(), E[now_idx].end(), 0);
		fill(sum[now_idx].begin(), sum[now_idx].end(), 0);
		for (int j = 1; j <= no_chose - 1; j++) {
			int r = j - 1;
			E[now_idx][j] = sum[now_idx ^ 1][r] / (m - 1);
			sum[now_idx][j] = E[now_idx][j] + sum[now_idx][j - 1];
			// debug(i, j, E[now_idx][j], sum[now_idx][j]);
		}

		for (int j = no_chose; j <= LIMIT; j++) {
			// [1, no_chose - 1]
			E[now_idx][j] = 0;

			int l = j - no_chose;
			int r = j - 1;
			E[now_idx][j] += (sum[now_idx ^ 1][r] - sum[now_idx ^ 1][l]) / (m - 1);
			// [no_chose + 1, m]
			r = j - no_chose - 1;
			if (r >= 0) {
				l = j - m - 1;
				if (l >= 0) {
					E[now_idx][j] += (sum[now_idx ^ 1][r] - sum[now_idx ^ 1][l]) / (m - 1);
				} else {
					E[now_idx][j] += sum[now_idx ^ 1][r] / (m - 1);
				}
			}

			sum[now_idx][j] = E[now_idx][j] + sum[now_idx][j - 1];
			// debug(i, j, E[now_idx][j], sum[now_idx][j]);
		}
	}

	double ans = sum[n % 2][val - 1] + 1;

	cout << fixed << setprecision(9);

	cout << ans << endl;
	return 0;
}